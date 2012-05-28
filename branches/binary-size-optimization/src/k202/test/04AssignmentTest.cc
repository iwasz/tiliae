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
#include <cassert>
#include "../../beanWrapper/beanWrapper/BeanWrapper.h"

BOOST_AUTO_TEST_SUITE (AssignmentTest04);
using namespace k202;
using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testAssignment)
{
        Ptr <K202> k202 = K202::create (Wrapper::BeanWrapper::create ());

        VariantMap argsMap;
        Variant vv = Core::Variant (&argsMap);

        assert (argsMap.size () == 0);
        TestRuntime <bool>::test (k202, "$prop = true", true, vv);
        assert (argsMap.size () == 1);
        assert (vcast <bool> (argsMap["prop"]) == true);
        TestRuntime <bool>::test (k202, "$prop", true, vv);

        TestRuntime <std::string>::test (k202, "$a = 'test'", "test", vv);
        TestRuntime <std::string>::test (k202, "$a", "test", vv);

        TestRuntime <Core::String>::test (k202, "$a = u'test'", "test", vv);
        TestRuntime <Core::String>::test (k202, "$a", "test", vv);

        TestRuntime <std::string>::test (k202, "$a = 'test2'", "test2", vv);
        TestRuntime <std::string>::test (k202, "$a", "test2", vv);

        TestRuntime <int>::test (k202, "$b = 89643", 89643, vv);
        TestRuntime <int>::test (k202, "$b", 89643, vv);

        TestRuntime <bool>::test (k202, "$c = true", true, vv);
        TestRuntime <bool>::test (k202, "$c", true, vv);

        TestRuntime <double>::test (k202, "$d = 78932.43", 78932.43, vv);
        TestRuntime <double>::test (k202, "$d", 78932.43, vv);

//        Zabroniłem jednak tego
//        TestRuntime <int>::test (k202, "${} = 324", 324, vv);
//        assert (vcast <int> (vv) == 324);

        argsMap.clear ();
        assert (argsMap.size () == 0);
        vv = Core::Variant (&argsMap);
        TestRuntime <std::string>::test (k202, "$a = $b = $c = 'test'", "test", vv);
        assert (argsMap.size () == 3);
        TestRuntime <bool>::test (k202, "$a == 'test'", true, vv);
        TestRuntime <bool>::test (k202, "$b == 'test'", true, vv);
        TestRuntime <bool>::test (k202, "$c == 'test'", true, vv);

        argsMap.clear ();
        TestRuntime <std::string>::test (k202, "$a = 'test1'; $b = 'test2'; $c = 'test3'", "test3", vv);
        assert (argsMap.size () == 3);
        TestRuntime <bool>::test (k202, "$a == 'test1'", true, vv);
        TestRuntime <bool>::test (k202, "$b == 'test2'", true, vv);
        TestRuntime <bool>::test (k202, "$c == 'test3'", true, vv);
}

BOOST_AUTO_TEST_SUITE_END ();
