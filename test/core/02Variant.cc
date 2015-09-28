/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>

#include "core/variant/Cast.h"
#include "core/string/String.h"

BOOST_AUTO_TEST_SUITE (Variant02);

using namespace boost;
using namespace Core;

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testInt)
{
        {
                int d = 667;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <int const &> (v), 667);
        }

        {
                int const d = 667;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <int const &> (v), 667);
        }

//        {
//                int d = 667;
//                int *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE_EQUAL (vcast <int> (v), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <int *> (v)), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <int const *>) (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <int &> (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <int const &> (v), 667);
//        }
//
//        {
//                int d = 667;
//                int const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE_EQUAL (vcast <int> (v), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <int *> (v)), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <int const *>) (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <int &> (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <int const &> (v), 667);
//        }

        {
                int d = 667;
                int &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <int const &> (v), 667);
        }

        {
                int d = 667;
                int const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <int const &> (v), 667);
        }
}

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testUInt)
{
        {
                unsigned int d = 667;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <unsigned int> (v), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned int *> (v)), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned int const *>) (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned int &> (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned int const &> (v), 667U);
        }

        {
                unsigned int const d = 667;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <unsigned int> (v), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned int *> (v)), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned int const *>) (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned int &> (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned int const &> (v), 667U);
        }

//        {
//                unsigned int d = 667;
//                unsigned int *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned int> (v), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned int *> (v)), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned int const *>) (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned int &> (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned int const &> (v), 667);
//        }
//
//        {
//                unsigned int d = 667;
//                unsigned int const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned int> (v), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned int *> (v)), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned int const *>) (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned int &> (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned int const &> (v), 667);
//        }

        {
                unsigned int d = 667;
                unsigned int &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <unsigned int> (v), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned int *> (v)), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned int const *>) (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned int &> (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned int const &> (v), 667U);
        }

        {
                unsigned int d = 667U;
                unsigned int const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <unsigned int> (v), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned int *> (v)), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned int const *>) (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned int &> (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned int const &> (v), 667U);
        }
}

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testLong)
{
        {
                long int d = 667;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <long int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <long int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <long int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <long int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <long int const &> (v), 667);
        }

        {
                long int const d = 667;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <long int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <long int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <long int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <long int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <long int const &> (v), 667);
        }

//        {
//                long int d = 667;
//                long int *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE_EQUAL (vcast <long int> (v), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <long int *> (v)), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <long int const *>) (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <long int &> (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <long int const &> (v), 667);
//        }
//
//        {
//                long int d = 667;
//                long int const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE_EQUAL (vcast <long int> (v), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <long int *> (v)), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <long int const *>) (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <long int &> (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <long int const &> (v), 667);
//        }

        {
                long int d = 667;
                long int &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <long int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <long int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <long int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <long int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <long int const &> (v), 667);
        }

        {
                long int d = 667;
                long int const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <long int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <long int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <long int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <long int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <long int const &> (v), 667);
        }
}

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testULong)
{
        {
                unsigned long int d = 667;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <unsigned long int> (v), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned long int *> (v)), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned long int const *>) (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned long int &> (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned long int const &> (v), 667U);
        }

        {
                unsigned long int const d = 667U;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <unsigned long int> (v), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned long int *> (v)), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned long int const *>) (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned long int &> (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned long int const &> (v), 667U);
        }

//        {
//                unsigned long int d = 667;
//                unsigned long int *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned long int> (v), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned long int *> (v)), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned long int const *>) (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned long int &> (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned long int const &> (v), 667);
//        }
//
//        {
//                unsigned long int d = 667;
//                unsigned long int const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned long int> (v), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned long int *> (v)), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned long int const *>) (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned long int &> (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned long int const &> (v), 667);
//        }

        {
                unsigned long int d = 667;
                unsigned long int &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <unsigned long int> (v), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned long int *> (v)), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned long int const *>) (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned long int &> (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned long int const &> (v), 667U);
        }

        {
                unsigned long int d = 667U;
                unsigned long int const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <unsigned long int> (v), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned long int *> (v)), 667U);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned long int const *>) (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned long int &> (v), 667U);
                BOOST_REQUIRE_EQUAL (vcast <unsigned long int const &> (v), 667U);
        }
}

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testShort)
{
        {
                short int d = 667;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <short int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <short int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <short int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <short int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <short int const &> (v), 667);
        }

        {
                short int const d = 667;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <short int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <short int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <short int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <short int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <short int const &> (v), 667);
        }

//        {
//                short int d = 667;
//                short int *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE_EQUAL (vcast <short int> (v), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <short int *> (v)), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <short int const *>) (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <short int &> (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <short int const &> (v), 667);
//        }
//
//        {
//                short int d = 667;
//                short int const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE_EQUAL (vcast <short int> (v), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <short int *> (v)), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <short int const *>) (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <short int &> (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <short int const &> (v), 667);
//        }

        {
                short int d = 667;
                short int &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <short int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <short int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <short int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <short int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <short int const &> (v), 667);
        }

        {
                short int d = 667;
                short int const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <short int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <short int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <short int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <short int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <short int const &> (v), 667);
        }
}

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testUShort)
{
        {
                unsigned short int d = 667;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <unsigned short int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned short int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned short int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <unsigned short int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <unsigned short int const &> (v), 667);
        }

        {
                unsigned short int const d = 667;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <unsigned short int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned short int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned short int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <unsigned short int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <unsigned short int const &> (v), 667);
        }

//        {
//                unsigned short int d = 667;
//                unsigned short int *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned short int> (v), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned short int *> (v)), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned short int const *>) (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned short int &> (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned short int const &> (v), 667);
//        }
//
//        {
//                unsigned short int d = 667;
//                unsigned short int const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned short int> (v), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned short int *> (v)), 667);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned short int const *>) (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned short int &> (v), 667);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned short int const &> (v), 667);
//        }

        {
                unsigned short int d = 667;
                unsigned short int &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <unsigned short int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned short int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned short int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <unsigned short int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <unsigned short int const &> (v), 667);
        }

        {
                unsigned short int d = 667;
                unsigned short int const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <unsigned short int> (v), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned short int *> (v)), 667);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned short int const *>) (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <unsigned short int &> (v), 667);
                BOOST_REQUIRE_EQUAL (vcast <unsigned short int const &> (v), 667);
        }
}

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testStdString)
{
        {
                std::string d = "alakot";
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <std::string> (v), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <std::string *> (v)), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <std::string const *>) (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <std::string &> (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <std::string const &> (v), "alakot");
        }

        {
                std::string const d = "alakot";
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <std::string> (v), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <std::string *> (v)), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <std::string const *>) (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <std::string &> (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <std::string const &> (v), "alakot");
        }

        {
                std::string d = "alakot";
                std::string *pd = &d;
                Variant v (pd);
                BOOST_REQUIRE_EQUAL (vcast <std::string> (v), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <std::string *> (v)), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <std::string const *>) (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <std::string &> (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <std::string const &> (v), "alakot");
        }

        {
                std::string d = "alakot";
                std::string const *cpd = &d;
                Variant v (cpd);
                BOOST_REQUIRE_EQUAL (vcast <std::string> (v), "alakot");
//                BOOST_REQUIRE_EQUAL (*(vcast <std::string *> (v)), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <std::string const *>) (v), "alakot");
//                BOOST_REQUIRE_EQUAL (vcast <std::string &> (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <std::string const &> (v), "alakot");
        }

        {
                std::string d = "alakot";
                std::string &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <std::string> (v), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <std::string *> (v)), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <std::string const *>) (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <std::string &> (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <std::string const &> (v), "alakot");
        }

        {
                std::string d = "alakot";
                std::string const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <std::string> (v), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <std::string *> (v)), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <std::string const *>) (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <std::string &> (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <std::string const &> (v), "alakot");
        }
}

#ifdef WITH_CORE_STRING

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testCoreString)
{
        {
                Core::String d = "alakot";
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <Core::String> (v), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <Core::String *> (v)), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <Core::String const *>) (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <Core::String &> (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <Core::String const &> (v), "alakot");
        }

        {
                Core::String const d = "alakot";
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <Core::String> (v), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <Core::String *> (v)), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <Core::String const *>) (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <Core::String &> (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <Core::String const &> (v), "alakot");
        }

        {
                Core::String d = "alakot";
                Core::String *pd = &d;
                Variant v (pd);
                BOOST_REQUIRE_EQUAL (vcast <Core::String> (v), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <Core::String *> (v)), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <Core::String const *>) (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <Core::String &> (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <Core::String const &> (v), "alakot");
        }

        {
                Core::String d = "alakot";
                Core::String const *cpd = &d;
                Variant v (cpd);
                BOOST_REQUIRE_EQUAL (vcast <Core::String> (v), "alakot");
//                BOOST_REQUIRE_EQUAL (*(vcast <Core::String *> (v)), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <Core::String const *>) (v), "alakot");
//                BOOST_REQUIRE_EQUAL (vcast <Core::String &> (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <Core::String const &> (v), "alakot");
        }

        {
                Core::String d = "alakot";
                Core::String &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <Core::String> (v), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <Core::String *> (v)), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <Core::String const *>) (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <Core::String &> (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <Core::String const &> (v), "alakot");
        }

        {
                Core::String d = "alakot";
                Core::String const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <Core::String> (v), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <Core::String *> (v)), "alakot");
                BOOST_REQUIRE_EQUAL (*(vcast <Core::String const *>) (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <Core::String &> (v), "alakot");
                BOOST_REQUIRE_EQUAL (vcast <Core::String const &> (v), "alakot");
        }
}
#endif

BOOST_AUTO_TEST_SUITE_END ();
