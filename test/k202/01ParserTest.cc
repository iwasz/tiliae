/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#define BOOST_TEST_MODULE K202Test
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cassert>
#include "k202/compiler/Compiler.h"
#include "TestHelpers.h"
#include "k202/extension/CacheExtension.h"
#include "testHelpers/Reflection_output.cc.h"

BOOST_AUTO_TEST_SUITE (ParserTest01);
using namespace k202;

BOOST_AUTO_TEST_CASE (testParser)
{
        Ptr <Compiler> compiler = Ptr <Compiler> (new Compiler);

        TestHelpers::testParser (compiler, "'true'", "ByteCode (StringLiteral (true))");
        TestHelpers::testParser (compiler, "'${p}'", "ByteCode (StringLiteral (${p}))");
        TestHelpers::testParser (compiler, "'some-string-wo-spaces'", "ByteCode (StringLiteral (some-string-wo-spaces))");
        TestHelpers::testParser (compiler, "'some string'", "ByteCode (StringLiteral (some string))");
        TestHelpers::testParser (compiler, "6667", "ByteCode (IntLiteral (6667))");
        TestHelpers::testParser (compiler, "77765.0", "ByteCode (DoubleLiteral (77765))");
        TestHelpers::testParser (compiler, "true", "ByteCode (BoolLiteral (1))");
        TestHelpers::testParser (compiler, "false", "ByteCode (BoolLiteral (0))");

        TestHelpers::testParser (compiler, "none", "ByteCode (NoneLiteral ())");

        TestHelpers::testParser (compiler, "%0", "ByteCode (Placeholder (0))");
        TestHelpers::testParser (compiler, "%1", "ByteCode (Placeholder (1))");
        TestHelpers::testParser (compiler, "%12", "ByteCode (Placeholder (12))");

        TestHelpers::testParser (compiler, "${bean.prop}", "ByteCode (Property (bean.prop))");
        TestHelpers::testParser (compiler, "$bean.prop", "ByteCode (Property (bean.prop))");
        TestHelpers::testParser (compiler, "$prop", "ByteCode (Property (prop))");
        TestHelpers::testParser (compiler, "${prop}", "ByteCode (Property (prop))");
        TestHelpers::testParser (compiler, "$a.b.c", "ByteCode (Property (a.b.c))");
        TestHelpers::testParser (compiler, "${p1234}", "ByteCode (Property (p1234))");
        TestHelpers::testParser (compiler, " $ { p1.p2.p3 } ", "ByteCode (Property (p1.p2.p3))");
        TestHelpers::testParser (compiler, "${}", "ByteCode (Property ())");
        TestHelpers::testParser (compiler, "${bean.1}", "ByteCode (Property (bean.1))");
        TestHelpers::testParser (compiler, "${1.2.3}", "ByteCode (Property (1.2.3))");

        TestHelpers::testParser (compiler, "$!bean.prop", "ByteCode (Property (bean.prop))");
        TestHelpers::testParser (compiler, "$!bean", "ByteCode (Property (bean))");
        TestHelpers::testParser (compiler, "$!a.1.c.2", "ByteCode (Property (a.1.c.2))");

        TestHelpers::testParser (compiler, " $ f ()", "ByteCode (Function (f))");
        TestHelpers::testParser (compiler, "$bean.func ()", "ByteCode (Function (bean.func))");
        TestHelpers::testParser (compiler, "$bean.func ($a, $b)", "ByteCode (Function (bean.func, 2 args : Property (a), Property (b)))");
        TestHelpers::testParser (compiler, "$bean.func (%0, %1)", "ByteCode (Function (bean.func, 2 args : Placeholder (0), Placeholder (1)))");
        TestHelpers::testParser (compiler, "$funcA ($funcB (%0))", "ByteCode (Function (funcA, 1 args : Function (funcB, 1 args : Placeholder (0))))");
        TestHelpers::testParser (compiler, "$funcA ($funcB (%0), %1)", "ByteCode (Function (funcA, 2 args : Function (funcB, 1 args : Placeholder (0)), Placeholder (1)))");
        TestHelpers::testParser (compiler, "$funcA ($funcB (%0, %1))", "ByteCode (Function (funcA, 1 args : Function (funcB, 2 args : Placeholder (0), Placeholder (1))))");
        TestHelpers::testParser (compiler, "$funcA ($funcB (%0), $funcC (%1))", "ByteCode (Function (funcA, 2 args : Function (funcB, 1 args : Placeholder (0)), Function (funcC, 1 args : Placeholder (1))))");
        TestHelpers::testParser (compiler, "$funcA (667)", "ByteCode (Function (funcA, 1 args : IntLiteral (667)))");

        TestHelpers::testParser (compiler, "!%1 == !%2", "ByteCode (LogicEq (LogicNegation (Placeholder (1)), LogicNegation (Placeholder (2))))");
        TestHelpers::testParser (compiler, "%0 == %1", "ByteCode (LogicEq (Placeholder (0), Placeholder (1)))");
        TestHelpers::testParser (compiler, "%0 != %1", "ByteCode (LogicNe (Placeholder (0), Placeholder (1)))");
        TestHelpers::testParser (compiler, "%0 && %1", "ByteCode (LogicAnd (Placeholder (0), Placeholder (1)))");
        TestHelpers::testParser (compiler, "%0 || %1", "ByteCode (LogicOr (Placeholder (0), Placeholder (1)))");
        TestHelpers::testParser (compiler, "!%0", "ByteCode (LogicNegation (Placeholder (0)))");

        TestHelpers::testParser (compiler, "${prop.a.b} = 'kupa'", "ByteCode (Assignment (Property (prop.a.b), StringLiteral (kupa)))");
        TestHelpers::testParser (compiler, "$p = 1", "ByteCode (Assignment (Property (p), IntLiteral (1)))");
        TestHelpers::testParser (compiler, "$p = true", "ByteCode (Assignment (Property (p), BoolLiteral (1)))");
        TestHelpers::testParser (compiler, "$p = 1.2", "ByteCode (Assignment (Property (p), DoubleLiteral (1.2)))");
        TestHelpers::testParser (compiler, "$p = $q", "ByteCode (Assignment (Property (p), Property (q)))");
        TestHelpers::testParser (compiler, "$p = $f()", "ByteCode (Assignment (Property (p), Function (f)))");
        TestHelpers::testParser (compiler, "$p = $funcA ($funcB (%0), %1)", "ByteCode (Assignment (Property (p), Function (funcA, 2 args : Function (funcB, 1 args : Placeholder (0)), Placeholder (1))))");
        TestHelpers::testParser (compiler, "$p = 'test'", "ByteCode (Assignment (Property (p), StringLiteral (test)))");


        TestHelpers::testParser (compiler, "$a(); $b()", "ByteCode (Function (a), Function (b))");
        TestHelpers::testParser (compiler, "$funcA ($funcB (%0), %1); $funcA ($funcB (%0, %1))", "ByteCode (Function (funcA, 2 args : Function (funcB, 1 args : Placeholder (0)), Placeholder (1)), Function (funcA, 1 args : Function (funcB, 2 args : Placeholder (0), Placeholder (1))))");
}

BOOST_AUTO_TEST_CASE (testOperatorPrecedence)
{
        Ptr <Compiler> compiler = Ptr <Compiler> (new Compiler);

        /*
         * 1. ! Wiąże najmocniej
         */
        TestHelpers::testParser (compiler, "!%0 != true", "ByteCode (LogicNe (LogicNegation (Placeholder (0)), BoolLiteral (1)))");
        TestHelpers::testParser (compiler, "!%0 == true", "ByteCode (LogicEq (LogicNegation (Placeholder (0)), BoolLiteral (1)))");
        TestHelpers::testParser (compiler, "!%0 && true", "ByteCode (LogicAnd (LogicNegation (Placeholder (0)), BoolLiteral (1)))");
        TestHelpers::testParser (compiler, "!%0 || true", "ByteCode (LogicOr (LogicNegation (Placeholder (0)), BoolLiteral (1)))");
        TestHelpers::testParser (compiler, "$prop = !%1", "ByteCode (Assignment (Property (prop), LogicNegation (Placeholder (1))))");
        TestHelpers::testParser (compiler, "!(%0 != true)", "ByteCode (LogicNegation (LogicNe (Placeholder (0), BoolLiteral (1))))");

        /*
         * 2. == i != wiążą tak samo silnie i są lewostronnie łączne.
         * "%0 == %1 != %2 -> "(%0 == %1) != %2
         */
        TestHelpers::testParser (compiler, "%0 == %1 != %2", "ByteCode (LogicNe (LogicEq (Placeholder (0), Placeholder (1)), Placeholder (2)))");
        TestHelpers::testParser (compiler, "%0 != %1 == %2", "ByteCode (LogicEq (LogicNe (Placeholder (0), Placeholder (1)), Placeholder (2)))");
        TestHelpers::testParser (compiler, "%0 == (%1 != %2)", "ByteCode (LogicEq (Placeholder (0), LogicNe (Placeholder (1), Placeholder (2))))");
        TestHelpers::testParser (compiler, "%0 != (%1 == %2)", "ByteCode (LogicNe (Placeholder (0), LogicEq (Placeholder (1), Placeholder (2))))");

        /*
         * 3. == i != wiaza mocniej niz &&
         */
        TestHelpers::testParser (compiler, "%0 == %1 && %2", "ByteCode (LogicAnd (LogicEq (Placeholder (0), Placeholder (1)), Placeholder (2)))");
        TestHelpers::testParser (compiler, "%0 && %1 == %2", "ByteCode (LogicAnd (Placeholder (0), LogicEq (Placeholder (1), Placeholder (2))))");
        TestHelpers::testParser (compiler, "(%0 == %1) && %2", "ByteCode (LogicAnd (LogicEq (Placeholder (0), Placeholder (1)), Placeholder (2)))");
        TestHelpers::testParser (compiler, "%0 && (%1 == %2)", "ByteCode (LogicAnd (Placeholder (0), LogicEq (Placeholder (1), Placeholder (2))))");

        // Mocniej niz funkcja.
        TestHelpers::testParser (compiler, "$funcA (%0, %1) == $funcB (%2, %3)", "ByteCode (LogicEq (Function (funcA, 2 args : Placeholder (0), Placeholder (1)), Function (funcB, 2 args : Placeholder (2), Placeholder (3))))");

        // && Wiaze mocniej niz ||
        TestHelpers::testParser (compiler, "%0 && %1 || %2", "ByteCode (LogicOr (LogicAnd (Placeholder (0), Placeholder (1)), Placeholder (2)))");
        TestHelpers::testParser (compiler, "%0 || %1 && %2", "ByteCode (LogicOr (Placeholder (0), LogicAnd (Placeholder (1), Placeholder (2))))");
        TestHelpers::testParser (compiler, "(%0 && %1) || %2", "ByteCode (LogicOr (LogicAnd (Placeholder (0), Placeholder (1)), Placeholder (2)))");
        TestHelpers::testParser (compiler, "%0 || (%1 && %2)", "ByteCode (LogicOr (Placeholder (0), LogicAnd (Placeholder (1), Placeholder (2))))");
        TestHelpers::testParser (compiler, "%0 && (%1 || %2)", "ByteCode (LogicAnd (Placeholder (0), LogicOr (Placeholder (1), Placeholder (2))))");
        TestHelpers::testParser (compiler, "(%0 || %1) && %2", "ByteCode (LogicAnd (LogicOr (Placeholder (0), Placeholder (1)), Placeholder (2)))");

        /*
         * ! right-to-left
         */
        TestHelpers::testParser (compiler, "!!%0", "ByteCode (LogicNegation (LogicNegation (Placeholder (0))))");

        /*
         * = wiąże najsłabiej i jest parwostronnie łaczny : a = b = c -> a = (b = c)
         */
        TestHelpers::testParser (compiler, "$a = $b = 'str'", "ByteCode (Assignment (Property (a), Assignment (Property (b), StringLiteral (str))))");
        TestHelpers::testParser (compiler, "$a = ($b = 'str')", "ByteCode (Assignment (Property (a), Assignment (Property (b), StringLiteral (str))))");

        // To jest błędne.
        // TestHelpers::testParser (compiler, "($a = $b) = 'str'", "");

        compiler->setExtension (CacheExtension::create ());
        TestHelpers::testParser (compiler, "$!prop", "ByteCode (CacheExpression (Property (prop)))");
}

BOOST_AUTO_TEST_CASE (testOperatorAssociativity)
{
//        Ptr <Compiler> compiler = Ptr <Compiler> (new Compiler);
//        std::cerr << "OK ParserTest::testOperatorAssociativity" << std::endl;
}

/****************************************************************************/

//
//
//        parse (parser, "(!(true))");
//
//        std::cerr << "------- multiple instructions" << std::endl;
//
//        parse (parser, "$p=1;$q=2;$r=3");
//
//
///******* błędne *************************************************************/
//
//        std::cerr << "------- errorneus " << std::endl;
//
//        parse (parser, "'corrupted string'afds'");
//
//}

BOOST_AUTO_TEST_SUITE_END ();
