/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

#include <Pointer.h>
#include "expression/ExpressionCollection.h"
#include "../extension/IExtension.h"
#include "../../core/ApiMacro.h"
#include "../../core/string/String.h"

namespace k202 {
class Context;
class ByteCode;
class NArryExpression;

/**
 *
 */
struct FunctionDTO {
        std::string name;
        int argCount;
};

/**
 * Kind of factory which makes "bytecode" from source code of k202
 * script.
 */
class TILIAE_API Compiler {
public:

        Compiler (/*Ptr <Wrapper::IBeanWrapper> b*/);
        virtual ~Compiler ();

        static Ptr <Compiler> create (/*Ptr <Wrapper::IBeanWrapper> b*/);

        /**
         * Ctx jest tu potrzebny, ponieważ już podczas kompilacji
         * można wyciągać hadlery do metod etc.
         */
        Ptr <ByteCode> compile (const std::string &source, Context *ctx);

        Ptr <IExtension> getExtension () { return extension; }
        void setExtension (Ptr <IExtension>e) { extension = e; }

private:

        // Semantic actions
        void onStringLiteral (const std::string &str);
        void onUStringLiteral (const Core::String &str);
        void onDoubleLiteral (double d);
        void onIntLiteral (int i);
        void onBoolLiteral (const std::string &str);
        void onNoneLiteral ();
        void onPlaceholder (unsigned int placeholder);
        void onProperty (const std::string &str);
        void onConditionalProperty (const std::string &str);
        void onFunction (const FunctionDTO &fdto);
        void onLogicEq ();
        void onLogicNe ();
        void onLogicAnd ();
        void onLogicOr ();
        void onLogicNegation ();
        void onAssign ();

        // Utility
        void popArgs (NArryExpression *expression, unsigned int argsToPop);

private:

        template <typename Iterator>
        friend struct Parser;

        /**
         * Expressions in Reverse Polish notation order.
         */
        ExpressionStack stack;
        void *parser; // void *, żeby nie inkludować nagłówka, bo to ciężkie szblony.
        Ptr <IExtension>extension;

};

}

#endif /* PARSER_H_ */
