/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include "K202.h"
#include "TestHelpers.h"
#include "../../testHelpers/Bar.h"
#include "../../core/variant/Variant.h"
#include "../../core/string/String.h"

BOOST_AUTO_TEST_SUITE (FunctionTest);
using namespace k202;
using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testFunction)
{
        Ptr <K202> k202 = K202::create ();

        Bar bar = Bar (Variant ());
        Variant vv = Core::Variant (&bar);

        TestRuntime <bool>::test (k202, "$funcA (667); true", true, vv);
        BOOST_REQUIRE (bar.getField0 () == "funcA 667");

        TestRuntime <Core::String>::test (k202, "$funcB (668, u'kupa-siku'); $field0", "funcB 668, kupa-siku", vv);
        TestRuntime <Core::String>::test (k202, "$funcA (667); $funcB (668, $getField0 ()); $field0", "funcB 668, funcA 667", vv);
        TestRuntime <bool>::test (k202, "$funcA (665); $funcB (666, $getField0 ()); $field0 == u'funcB 666, funcA 665'", true, vv);
        TestRuntime <bool>::test (k202, "$funcA (664); $field1 = 'funcA 664'; $field1 == 'funcA 664'", true, vv);

        TestRuntime <bool>::test (k202, "$funcD ()", false, vv);
}
/****************************************************************************/

BOOST_AUTO_TEST_CASE (testFunctionArgsMap)
{
        Ptr <K202> k202 = K202::create ();

        VariantMap argsMap;
        Bar bar = Bar (Variant ());
        argsMap["bar"] = Core::Variant (&bar);

        TestRuntime <bool>::test (k202, "$bar.funcA (667); true", true, Variant (), VariantVector (), argsMap);
        BOOST_REQUIRE_EQUAL (bar.getField0 (), "funcA 667");

        TestRuntime <String>::test (k202, "$bar.funcB (668, u'kupa-siku'); $bar.field0", "funcB 668, kupa-siku", Variant (), VariantVector (), argsMap);
        TestRuntime <String>::test (k202, "$bar.funcA (667); $bar.funcB (668, $bar.getField0 ()); $bar.field0", "funcB 668, funcA 667", Variant (), VariantVector (), argsMap);
        TestRuntime <bool>::test (k202, "$bar.funcA (665); $bar.funcB (666, $bar.getField0 ()); $bar.field0 == u'funcB 666, funcA 665'", true, Variant (), VariantVector (), argsMap);
        TestRuntime <bool>::test (k202, "$bar.funcA (664); $bar.field1 = 'funcA 664'; $bar.field1 == 'funcA 664'", true, Variant (), VariantVector (), argsMap);

        TestRuntime <bool>::test (k202, "$bar.funcD ()", false, Variant (), VariantVector (), argsMap);
}

BOOST_AUTO_TEST_SUITE_END ();
