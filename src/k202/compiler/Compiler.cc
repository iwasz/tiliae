/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/bind.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>

#include <iostream>
#include <sstream>

#include "Compiler.h"
#include "ByteCode.h"

#include "expression/Expression.h"
#include "expression/ExpressionCollection.h"
#include "Context.h"
#include "Exceptions.h"
#include "core/string/String.h"

#define SHOW_DEBUG_COMPILER 0

namespace k202 {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

} // nam

/****************************************************************************/

BOOST_FUSION_ADAPT_STRUCT(
        k202::FunctionDTO,
        (std::string, name)
        (int, argCount)
)

/****************************************************************************/

namespace k202 {

struct ErrorHandler
{
        template <typename, typename, typename, typename>
        struct result { typedef void type; };

        template <typename Iterator>
        void operator () (const qi::info& what, Iterator err_pos, Iterator last, Iterator first) const
        {
                std::ostringstream sout;
                sout << what;
                throw SyntaxErrorException (std::string ("SyntaxErrorException : expecting : ") +
                                        sout.str () +
                                        std::string (" here : ") + std::string (first, err_pos) + "^" +
                                        std::string (err_pos, last));
        }
};

const phoenix::function <ErrorHandler> errorHandler = ErrorHandler ();

/**
 *
 */
template <typename Iterator>
struct Parser : qi::grammar <Iterator, void(), ascii::space_type>
{
            Parser (Compiler *c) : Parser::base_type (script, "script"), cmpl (c)
            {
                    using phoenix::at_c;

                    // Identifiers
                    first_cpp_char = ascii::char_ ('_') | ascii::alpha;
                    cpp_char = qi::digit | first_cpp_char;
                    cpp_identifier = qi::lexeme [first_cpp_char > *cpp_char];
                    identifier = cpp_identifier | +qi::digit;

                    /*
                     * Używamy tu qi::_val, które pozwala nam "edytować" atrybut parsera.
                     * Dzięki temu parser zwraca to co chcę (w moim przypadku zwraca jeden
                     * string posklejany z identifierów i kropek, zamiast std::vector stringów
                     * z identyfikatorami).
                     */
                    non_empty_path = qi::eps[qi::_val = std::string ("")] >>
                                    (identifier[qi::_val += qi::_1] % qi::string (".")[qi::_val += qi::_1]);

                    // Expressiony tworzące jakiś "byte-code".
                    placeholder_expression = qi::omit[qi::char_ ('%')] > qi::uint_;

                    property_expression = (qi::lit ('$') >> non_empty_path[qi::_val = qi::_1]) |
                                    (qi::lit ('$') >> qi::lit ('{') >> non_empty_path[qi::_val = qi::_1] >> qi::lit ('}')) |
                                    (qi::lit ("${}")[qi::_val = std::string ("")]);

                    cond_property_expression = (qi::lit ("$!") >> non_empty_path[qi::_val = qi::_1]) |
                                    (qi::lit ("$!{}")[qi::_val = std::string ("")]);

                    function_expression = qi::lit ('$')[at_c <1> (qi::_val) = 0] >>
                                    non_empty_path[at_c <0> (qi::_val) = qi::_1] >>
                                    ((qi::lit ('(') >>
                                    instruction[at_c <1> (qi::_val)++] % qi::lit (',') >> qi::lit (')')) |
                                    qi::lit ("()"));

                    /*
                     * Tu jest użyty magiczny operator %=, który dostosowuje atrybuty,
                     * to sie nazywa "auto rules" i jest opisane tu : http://www.boost.org/doc/libs/1_41_0/libs/spirit/doc/html/spirit/qi/tutorials/employee___parsing_into_structs.html#spirit.qi.tutorials.employee___parsing_into_structs.auto_rules
                     * Dodatkowo jeśli parser nie ma atrybutów, to te atrybuty w ogole
                     * są olewane. Wiem, że nieskłądnie piszę, ale na przykład tu w
                     * przypadku ascii::char_ ('\''), znak apostrofa nie będzie doklejony
                     * do wynikowego atrybutu, bo lit nie posiada atrybutów. onStringLiteral
                     * dostanie tylko zawartość napisu wewnątrz apostrofów.
                     */
                    string_literal %= qi::lexeme [qi::lit ('\'') >> *(ascii::char_ - ascii::char_ ('\'')) >> qi::lit ('\'')];

                    qi::real_parser <double, qi::strict_real_policies <double> > double_literal;

                    /*
                     * Kolejność występowania reguł w poniższym wyrażeniu jest crucial.
                     * Operator | działa jak w C. Jeśli left side expression evaluates
                     * to true (I mean parses the input without problems), to następne
                     * nie są już uruchamiane. Tak samo jest w C przy wyrażemniach boolean.
                     *
                     * http://www.boost.org/doc/libs/1_40_0/libs/spirit/classic/doc/operators.html
                     * (Short-circuiting)
                     */
                    expression = (qi::lit ('!') > expression) [boost::bind (&Compiler::onLogicNegation, cmpl)] |
                                    (qi::char_ ('(') >> (instruction - qi::char_ (')')) >> qi::char_ (')')) |
                                    placeholder_expression   [boost::bind (&Compiler::onPlaceholder, cmpl, _1)] |
                                    function_expression      [boost::bind (&Compiler::onFunction, cmpl, _1)] |
                                    property_expression      [boost::bind (&Compiler::onProperty, cmpl, _1)] |
                                    cond_property_expression [boost::bind (&Compiler::onConditionalProperty, cmpl, _1)] |
                                    string_literal           [boost::bind (&Compiler::onStringLiteral, cmpl, _1)] |
                                    (qi::lit ('u') > string_literal)           [boost::bind (&Compiler::onUStringLiteral, cmpl, _1)] |
                                    double_literal           [boost::bind (&Compiler::onDoubleLiteral, cmpl, _1)] |   // Double literal
                                    qi::int_                 [boost::bind (&Compiler::onIntLiteral, cmpl, _1)] |      // Integer literal
                                    qi::string ("true")      [boost::bind (&Compiler::onBoolLiteral, cmpl, _1)] |     // Boolean literal
                                    qi::string ("false")     [boost::bind (&Compiler::onBoolLiteral, cmpl, _1)] |     // Boolean literal
                                    qi::string ("none")     [boost::bind (&Compiler::onNoneLiteral, cmpl)];      // NONE literal

                    /*
                     * Natomiast kolejność definiowania następnych reguł ma decydujący
                     * wpływ na kolejność wartościowania operatorów (na operator
                     * precedence).
                     *
                     * Dodatkowo miałem problem z podpinaniem pod te poniższe semantic
                     * actions. Na przykład, kiedy miałem taką definicję:
                     *
                     * logic_eq = (expression >> qi::lit ("==") >> expression) | expression;
                     *
                     * To matchował expression wiele razy (to była zła definicja), a jak
                     * miałe taką:
                     *
                     * logic_eq = expression >> *(qi::lit ("==") >> expression)
                     *
                     * To matchował dobrze, ale semantic action odpalała się po kilka razy dla
                     * expression.
                     */

                    logic_eq = expression > *((qi::lit ("==") > expression)[boost::bind (&Compiler::onLogicEq, cmpl)] |
                                    (qi::lit ("!=") > expression)[boost::bind (&Compiler::onLogicNe, cmpl)]);

                    logic_and = logic_eq > *(qi::lit ("&&") > logic_eq)[boost::bind (&Compiler::onLogicAnd, cmpl)];
                    logic_or = logic_and > *(qi::lit ("||") > logic_and)[boost::bind (&Compiler::onLogicOr, cmpl)];

                    assignment_expression %= (property_expression >> qi::lit ("=") >> !qi::lit ("="))[boost::bind (&Compiler::onProperty, cmpl, _1)] >
                                    (assignment_expression | logic_or)[boost::bind (&Compiler::onAssign, cmpl)];

                    instruction = assignment_expression | logic_or;

                    script = instruction % qi::char_ (';') > qi::eoi;

                    // Deal with errors. These are names of parsers, which will be shown in error messages (hopefuly).
                    placeholder_expression.name ("placeholder");
                    instruction.name ("instruction");
                    expression.name ("expression");
                    script.name ("script");
                    logic_equation.name ("logic_equation");
                    logic_and.name ("logic_and");
                    logic_or.name ("logic_or");
                    logic_eq.name ("logic_eq");
                    assignment_expression.name ("assignment_expression");
                    first_cpp_char.name ("first_cpp_char");
                    cpp_char.name ("cpp_char");
                    non_empty_path.name ("non_empty_path");
                    property_expression.name ("property_expression");
                    cond_property_expression.name ("cond_property_expression");
                    property_expression_tmp.name ("property_expression_tmp");
                    string_literal.name ("string_literal");
                    function_expression.name ("function_expression");
                    cpp_identifier.name ("cpp_identifier");
                    identifier.name ("identifier");

                    qi::on_error<qi::fail> (script, errorHandler (qi::_4, qi::_3, qi::_2, qi::_1));

            }

            void parse (const std::string &str);

            qi::rule <Iterator, unsigned int(), ascii::space_type> placeholder_expression;
            qi::rule <Iterator, void (), ascii::space_type> instruction, expression, script, logic_equation, logic_and, logic_or, logic_eq, assignment_expression;
            qi::rule <Iterator, char ()> first_cpp_char, cpp_char;
            qi::rule <Iterator, std::string(), ascii::space_type> non_empty_path, property_expression, property_expression_tmp, cond_property_expression;
            qi::rule <Iterator, std::string (), ascii::space_type> string_literal;
            qi::rule <Iterator, FunctionDTO (), ascii::space_type> function_expression;
            qi::rule <Iterator, std::string()> cpp_identifier, identifier;

            Compiler *cmpl;
};

/****************************************************************************/

typedef std::string::const_iterator iterator_type;
typedef Parser <std::string::const_iterator> MyParser;

template <typename Iterator>
void Parser <Iterator>::parse (const std::string &str)
{
        std::string::const_iterator b = str.begin ();
        std::string::const_iterator i = b;
        std::string::const_iterator e = str.end ();

        bool r = qi::phrase_parse (i, e, *this, ascii::space);

        if (!r || i != e) {
                throw SyntaxErrorException (std::string ("SyntaxErrorException : parse not complete. Here : ") +
                                std::string (b, i) + "^" + std::string (i, e));
        }
}

/****************************************************************************/

//Compiler::Compiler (Ptr <Wrapper::IBeanWrapper> b) : bwrap (b)
Compiler::Compiler ()
{
        parser = new MyParser (this);
}

Compiler::~Compiler ()
{
        MyParser *p = static_cast <MyParser *> (parser);
        delete p;
}

Ptr <Compiler> Compiler::create (/*Ptr <Wrapper::IBeanWrapper> b*/)
{
        return Ptr <Compiler> (new Compiler ());
}

Ptr <ByteCode> Compiler::compile (const std::string &source, Context *ctx)
{
        /*
         * Poprzednie wyołanie mogło zakończyć się wyjątkiem, co może oznaczać,
         * że stos nie będzie pusty.
         */
        stack.clear ();
        MyParser *p = static_cast <MyParser *> (parser);
        p->parse (source.c_str ());

        ExpressionList list;

        while (!stack.empty ()) {
                if (extension) {
                        list.push_front (extension->popStack (stack.back ()));
                }
                else {
                        list.push_front (stack.back ());
                }

                stack.pop_back ();
        }

        return ByteCode::create (list);
}

/****************************************************************************/

void Compiler::popArgs (NArryExpression *expression, unsigned int argsToPop)
{
        for (unsigned int i = 0; i < argsToPop; ++i) {

                if (stack.empty ()) {
                        throw StackEmptyException (std::string ("StackEmptyException : no more arguments on stack "
                                        "while parsing function with ") + boost::lexical_cast <std::string> (argsToPop) +
                                        " arguments.");
                }

#if SHOW_DEBUG_COMPILER != 0
                Ptr <IExpression> expr = stack.back ();
                std::cerr << "POP : " << expr->toString () << std::endl;
                expression->addArgFront (expr);
#else
                expression->addArgFront (stack.back ());
#endif
                stack.pop_back ();
        }
}

/****************************************************************************/

void Compiler::onStringLiteral (const std::string &str)
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Parser::onStringLiteral : " << str << std::endl;
#endif

        stack.push_back (Literal <std::string>::create (str, "StringLiteral"));
}

void Compiler::onUStringLiteral (const Core::String &str)
{
        stack.push_back (Literal <Core::String>::create (str, "StringLiteral"));
}

void Compiler::onDoubleLiteral (double d)
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Parser::onDoubleLiteral : " << d << std::endl;
#endif

        stack.push_back (Literal <double>::create (d, "DoubleLiteral"));
}

void Compiler::onIntLiteral (int i)
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Parser::onIntLiteral : " << i << std::endl;
#endif

        stack.push_back (Literal <int>::create (i, "IntLiteral"));
}

void Compiler::onBoolLiteral (const std::string &str)
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Parser::onBoolLiteral : " << str << std::endl;
#endif

        stack.push_back (Literal <bool>::create ((str == "true"), "BoolLiteral"));
}

void Compiler::onNoneLiteral ()
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Parser::onNoneLiteral" << std::endl;
#endif

        stack.push_back (Literal <Core::Variant>::create (Core::Variant (), "NoneLiteral"));
}

void Compiler::onPlaceholder (unsigned int placeholder)
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Parser::onPlaceholder : " << placeholder << std::endl;
#endif

        stack.push_back (boost::make_shared <Placeholder> (placeholder));
}

void Compiler::onProperty (const std::string &str)
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Compiler::onProperty : " << str << std::endl;
#endif
        Ptr <Property> prop;

//        if (extension) {
//                Ptr <IExpression> e = extension->onProperty (prop, &stack, str);
//
//                if (e) {
//                        stack.push_back (e);
//                        return;
//                }
//        }

        prop = Property::create (str);

//        if (extension) {
//                Ptr <IExpression> e = extension->onProperty (prop, &stack, str);
//
//                if (e) {
//                        stack.push_back (e);
//                        return;
//                }
//        }

        stack.push_back (prop);
}

void Compiler::onConditionalProperty (const std::string &str)
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Compiler::onConditionalProperty : " << str << std::endl;
#endif

//        stack.push_back (Property::create (str, true));
        Ptr <Property> prop;

        if (extension) {
                Ptr <IExpression> e = extension->onProperty (prop, &stack, str);

                if (e) {
                        stack.push_back (e);
                        return;
                }
        }

        prop = Property::create (str, true);

        if (extension) {
                Ptr <IExpression> e = extension->onProperty (prop, &stack, str);

                if (e) {
                        stack.push_back (e);
                        return;
                }
        }

        stack.push_back (prop);
}

/****************************************************************************/

void Compiler::onFunction (const FunctionDTO &fdto)
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Compiler::onFunction, name :  " << fdto.name << ", argCount : " << fdto.argCount << std::endl;
#endif

        Ptr <Function> function = Function::create (fdto.name, fdto.argCount);
        popArgs (function.get (), fdto.argCount);
        stack.push_back (function);
}

void Compiler::onLogicEq ()
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Compiler::onLogicEq" << std::endl;
#endif

        Ptr <LogicEq> logicEq = LogicEq::create ();
        popArgs (logicEq.get (), 2);
        stack.push_back (logicEq);
}

void Compiler::onLogicNegation ()
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Compiler::onLogicNegation" << std::endl;
#endif

        Ptr <LogicNegation> logicNeg = LogicNegation::create ();
        popArgs (logicNeg.get (), 1);
        stack.push_back (logicNeg);
}

void Compiler::onLogicNe ()
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Compiler::onLogicNe" << std::endl;
#endif

        Ptr <LogicNe> logicNe = LogicNe::create ();
        popArgs (logicNe.get (), 2);
        stack.push_back (logicNe);
}

void Compiler::onLogicAnd ()
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Compiler::onLogicAnd" << std::endl;
#endif

        Ptr <LogicAnd> logicAnd = LogicAnd::create ();
        popArgs (logicAnd.get (), 2);
        stack.push_back (logicAnd);
}

void Compiler::onLogicOr ()
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Compiler::onLogicOr" << std::endl;
#endif

        Ptr <LogicOr> logicOr = LogicOr::create ();
        popArgs (logicOr.get (), 2);
        stack.push_back (logicOr);
}

void Compiler::onAssign ()
{
#if SHOW_DEBUG_COMPILER != 0
        std::cerr << "Compiler::onAssign" << std::endl;
#endif
        Ptr <Assignment> assign;

//        if (extension) {
//            assign = extension->onAssign (assign, &stack);
//
//            if (assign) {
//                    stack.push_back (assign);
//                    return;
//            }
//        }

        assign = Assignment::create ();
        popArgs (assign.get (), 2);
        stack.push_back (assign);
}

} // nam
