/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cassert>
#include "core/variant/Cast.h"
#include "k202/K202.h"
#include "TestHelpers.h"
#include "core/string/String.h"
#include "core/Pointer.h"
#include "beanWrapper/beanWrapper/BeanWrapper.h"

BOOST_AUTO_TEST_SUITE (RuntimeLiteralsTest02);
using namespace k202;
using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testStringLiteral)
{
        Ptr <K202> k202 = K202::create (Ptr <Wrapper::BeanWrapper> (Ptr <Wrapper::BeanWrapper> (Wrapper::BeanWrapper::create ())));

        TestRuntime <std::string>::test (k202, "'test'", "test");
        TestRuntime <std::string>::test (k202, "'t e s  t'", "t e s  t");
        TestRuntime <std::string>::test (k202, "'   bbb    '", "   bbb    ");
        TestRuntime <std::string>::test (k202, "''", "");
        TestRuntime <std::string>::test (k202, "'\"\"'", "\"\"");
        TestRuntime <std::string>::test (k202, "'${p}'", "${p}");
        TestRuntime <std::string>::test (k202, "'(())'", "(())");
        TestRuntime <std::string>::test (k202, "'true'", "true");
        TestRuntime <std::string>::test (k202, "'false'", "false");
        TestRuntime <std::string>::test (k202, "'12343.132'", "12343.132");
        TestRuntime <std::string>::test (k202, "' 1 '", " 1 ");
        TestRuntime <std::string>::test (k202, "'some-string-wo-spaces'", "some-string-wo-spaces");
        TestRuntime <std::string>::test (k202, "((('a')))", "a");
//        TODO wywala się, zmienic iterator na Core::String::iterator
//        TestRuntime <String>::test (k202, "'ó'", "ó");
//        TestRuntime <String>::test (k202, "'zażółć gęślą jaźń'", "zażółć gęślą jaźń");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testIntLiteral)
{
        Ptr <K202> k202 = K202::create (Ptr <Wrapper::BeanWrapper> (Ptr <Wrapper::BeanWrapper> (Wrapper::BeanWrapper::create ())));

        TestRuntime <int>::test (k202, "1", 1);
        TestRuntime <int>::test (k202, " 2", 2);
        TestRuntime <int>::test (k202, "3 ", 3);
        TestRuntime <int>::test (k202, "895437543", 895437543);
        TestRuntime <int>::test (k202, "0", 0);
        TestRuntime <int>::test (k202, "-9843", -9843);
        TestRuntime <int>::test (k202, "-0", 0);
        TestRuntime <int>::test (k202, "+432", 432);
        TestRuntime <int>::test (k202, "(666)", 666);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testDoubleLiteral)
{
        Ptr <K202> k202 = K202::create (Ptr <Wrapper::BeanWrapper> (Ptr <Wrapper::BeanWrapper> (Wrapper::BeanWrapper::create ())));

        TestRuntime <double>::test (k202, "1.0", 1.0);
        TestRuntime <double>::test (k202, " 2.0", 2.0);
        TestRuntime <double>::test (k202, "3.0 ", 3.0);
        TestRuntime <double>::test (k202, "   4.0   ", 4.0);
        TestRuntime <double>::test (k202, "1241543.876", 1241543.876); // +/-
        TestRuntime <double>::test (k202, "0.0", 0);
        TestRuntime <double>::test (k202, "+4.5", 4.5);
        TestRuntime <double>::test (k202, "-5.4", -5.4);
        TestRuntime <double>::test (k202, " (890.8) ", 890.8);
        TestRuntime <double>::test (k202, "6.2e2", 6.2e2);
        TestRuntime <double>::test (k202, "-6.2e2", -6.2e2);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testBoolLiteral)
{
        Ptr <K202> k202 = K202::create (Ptr <Wrapper::BeanWrapper> (Ptr <Wrapper::BeanWrapper> (Wrapper::BeanWrapper::create ())));

        TestRuntime <bool>::test (k202, "true", true);
        TestRuntime <bool>::test (k202, "false", false);
        TestRuntime <bool>::test (k202, "   true   ", true);
        TestRuntime <bool>::test (k202, "   false", false);
}

BOOST_AUTO_TEST_SUITE_END ();
