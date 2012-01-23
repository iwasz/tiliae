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

#include "variant/Cast.h"
#include "string/String.h"

BOOST_AUTO_TEST_SUITE (CanCast05);

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
                BOOST_REQUIRE (ccast <int> (v));
                BOOST_REQUIRE (ccast <int *> (v));
                BOOST_REQUIRE (ccast <int const *> (v));
                BOOST_REQUIRE (ccast <int &> (v));
                BOOST_REQUIRE (ccast <int const &> (v));
        }

        {
                int const d = 667;
                Variant v (d);
                BOOST_REQUIRE (ccast <int> (v));
                BOOST_REQUIRE (ccast <int *> (v));
                BOOST_REQUIRE (ccast <int const *> (v));
                BOOST_REQUIRE (ccast <int &> (v));
                BOOST_REQUIRE (ccast <int const &> (v));
        }

//        {
//                int d = 667;
//                int *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <int> (v));
//                BOOST_REQUIRE (ccast <int *> (v));
//                BOOST_REQUIRE (ccast <int const *> (v));
//                BOOST_REQUIRE (ccast <int &> (v));
//                BOOST_REQUIRE (ccast <int const &> (v));
//        }
//
//        {
//                int d = 667;
//                int const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <int> (v));
//                BOOST_REQUIRE (ccast <int *> (v));
//                BOOST_REQUIRE (ccast <int const *> (v));
//                BOOST_REQUIRE (ccast <int &> (v));
//                BOOST_REQUIRE (ccast <int const &> (v));
//        }

        {
                int d = 667;
                int &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <int> (v));
                BOOST_REQUIRE (ccast <int *> (v));
                BOOST_REQUIRE (ccast <int const *> (v));
                BOOST_REQUIRE (ccast <int &> (v));
                BOOST_REQUIRE (ccast <int const &> (v));
        }

        {
                int d = 667;
                int const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <int> (v));
                BOOST_REQUIRE (ccast <int *> (v));
                BOOST_REQUIRE (ccast <int const *> (v));
                BOOST_REQUIRE (ccast <int &> (v));
                BOOST_REQUIRE (ccast <int const &> (v));
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
                BOOST_REQUIRE (ccast <unsigned int> (v));
                BOOST_REQUIRE (ccast <unsigned int *> (v));
                BOOST_REQUIRE (ccast <unsigned int const *> (v));
                BOOST_REQUIRE (ccast <unsigned int &> (v));
                BOOST_REQUIRE (ccast <unsigned int const &> (v));
        }

        {
                unsigned int const d = 667;
                Variant v (d);
                BOOST_REQUIRE (ccast <unsigned int> (v));
                BOOST_REQUIRE (ccast <unsigned int *> (v));
                BOOST_REQUIRE (ccast <unsigned int const *> (v));
                BOOST_REQUIRE (ccast <unsigned int &> (v));
                BOOST_REQUIRE (ccast <unsigned int const &> (v));
        }

//        {
//                unsigned int d = 667;
//                unsigned int *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <unsigned int> (v));
//                BOOST_REQUIRE (ccast <unsigned int *> (v));
//                BOOST_REQUIRE (ccast <unsigned int const *> (v));
//                BOOST_REQUIRE (ccast <unsigned int &> (v));
//                BOOST_REQUIRE (ccast <unsigned int const &> (v));
//        }
//
//        {
//                unsigned int d = 667;
//                unsigned int const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <unsigned int> (v));
//                BOOST_REQUIRE (ccast <unsigned int *> (v));
//                BOOST_REQUIRE (ccast <unsigned int const *> (v));
//                BOOST_REQUIRE (ccast <unsigned int &> (v));
//                BOOST_REQUIRE (ccast <unsigned int const &> (v));
//        }

        {
                unsigned int d = 667;
                unsigned int &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <unsigned int> (v));
                BOOST_REQUIRE (ccast <unsigned int *> (v));
                BOOST_REQUIRE (ccast <unsigned int const *> (v));
                BOOST_REQUIRE (ccast <unsigned int &> (v));
                BOOST_REQUIRE (ccast <unsigned int const &> (v));
        }

        {
                unsigned int d = 667;
                unsigned int const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <unsigned int> (v));
                BOOST_REQUIRE (ccast <unsigned int *> (v));
                BOOST_REQUIRE (ccast <unsigned int const *> (v));
                BOOST_REQUIRE (ccast <unsigned int &> (v));
                BOOST_REQUIRE (ccast <unsigned int const &> (v));
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
                BOOST_REQUIRE (ccast <long int> (v));
                BOOST_REQUIRE (ccast <long int *> (v));
                BOOST_REQUIRE (ccast <long int const *> (v));
                BOOST_REQUIRE (ccast <long int &> (v));
                BOOST_REQUIRE (ccast <long int const &> (v));
        }

        {
                long int const d = 667;
                Variant v (d);
                BOOST_REQUIRE (ccast <long int> (v));
                BOOST_REQUIRE (ccast <long int *> (v));
                BOOST_REQUIRE (ccast <long int const *> (v));
                BOOST_REQUIRE (ccast <long int &> (v));
                BOOST_REQUIRE (ccast <long int const &> (v));
        }

//        {
//                long int d = 667;
//                long int *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <long int> (v));
//                BOOST_REQUIRE (ccast <long int *> (v));
//                BOOST_REQUIRE (ccast <long int const *> (v));
//                BOOST_REQUIRE (ccast <long int &> (v));
//                BOOST_REQUIRE (ccast <long int const &> (v));
//        }
//
//        {
//                long int d = 667;
//                long int const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <long int> (v));
//                BOOST_REQUIRE (ccast <long int *> (v));
//                BOOST_REQUIRE (ccast <long int const *> (v));
//                BOOST_REQUIRE (ccast <long int &> (v));
//                BOOST_REQUIRE (ccast <long int const &> (v));
//        }

        {
                long int d = 667;
                long int &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <long int> (v));
                BOOST_REQUIRE (ccast <long int *> (v));
                BOOST_REQUIRE (ccast <long int const *> (v));
                BOOST_REQUIRE (ccast <long int &> (v));
                BOOST_REQUIRE (ccast <long int const &> (v));
        }

        {
                long int d = 667;
                long int const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <long int> (v));
                BOOST_REQUIRE (ccast <long int *> (v));
                BOOST_REQUIRE (ccast <long int const *> (v));
                BOOST_REQUIRE (ccast <long int &> (v));
                BOOST_REQUIRE (ccast <long int const &> (v));
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
                BOOST_REQUIRE (ccast <unsigned long int> (v));
                BOOST_REQUIRE (ccast <unsigned long int *> (v));
                BOOST_REQUIRE (ccast <unsigned long int const *> (v));
                BOOST_REQUIRE (ccast <unsigned long int &> (v));
                BOOST_REQUIRE (ccast <unsigned long int const &> (v));
        }

        {
                unsigned long int const d = 667;
                Variant v (d);
                BOOST_REQUIRE (ccast <unsigned long int> (v));
                BOOST_REQUIRE (ccast <unsigned long int *> (v));
                BOOST_REQUIRE (ccast <unsigned long int const *> (v));
                BOOST_REQUIRE (ccast <unsigned long int &> (v));
                BOOST_REQUIRE (ccast <unsigned long int const &> (v));
        }

//        {
//                unsigned long int d = 667;
//                unsigned long int *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <unsigned long int> (v));
//                BOOST_REQUIRE (ccast <unsigned long int *> (v));
//                BOOST_REQUIRE (ccast <unsigned long int const *> (v));
//                BOOST_REQUIRE (ccast <unsigned long int &> (v));
//                BOOST_REQUIRE (ccast <unsigned long int const &> (v));
//        }
//
//        {
//                unsigned long int d = 667;
//                unsigned long int const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <unsigned long int> (v));
//                BOOST_REQUIRE (ccast <unsigned long int *> (v));
//                BOOST_REQUIRE (ccast <unsigned long int const *> (v));
//                BOOST_REQUIRE (ccast <unsigned long int &> (v));
//                BOOST_REQUIRE (ccast <unsigned long int const &> (v));
//        }

        {
                unsigned long int d = 667;
                unsigned long int &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <unsigned long int> (v));
                BOOST_REQUIRE (ccast <unsigned long int *> (v));
                BOOST_REQUIRE (ccast <unsigned long int const *> (v));
                BOOST_REQUIRE (ccast <unsigned long int &> (v));
                BOOST_REQUIRE (ccast <unsigned long int const &> (v));
        }

        {
                unsigned long int d = 667;
                unsigned long int const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <unsigned long int> (v));
                BOOST_REQUIRE (ccast <unsigned long int *> (v));
                BOOST_REQUIRE (ccast <unsigned long int const *> (v));
                BOOST_REQUIRE (ccast <unsigned long int &> (v));
                BOOST_REQUIRE (ccast <unsigned long int const &> (v));
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
                BOOST_REQUIRE (ccast <short int> (v));
                BOOST_REQUIRE (ccast <short int *> (v));
                BOOST_REQUIRE (ccast <short int const *> (v));
                BOOST_REQUIRE (ccast <short int &> (v));
                BOOST_REQUIRE (ccast <short int const &> (v));
        }

        {
                short int const d = 667;
                Variant v (d);
                BOOST_REQUIRE (ccast <short int> (v));
                BOOST_REQUIRE (ccast <short int *> (v));
                BOOST_REQUIRE (ccast <short int const *> (v));
                BOOST_REQUIRE (ccast <short int &> (v));
                BOOST_REQUIRE (ccast <short int const &> (v));
        }

//        {
//                short int d = 667;
//                short int *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <short int> (v));
//                BOOST_REQUIRE (ccast <short int *> (v));
//                BOOST_REQUIRE (ccast <short int const *> (v));
//                BOOST_REQUIRE (ccast <short int &> (v));
//                BOOST_REQUIRE (ccast <short int const &> (v));
//        }
//
//        {
//                short int d = 667;
//                short int const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <short int> (v));
//                BOOST_REQUIRE (ccast <short int *> (v));
//                BOOST_REQUIRE (ccast <short int const *> (v));
//                BOOST_REQUIRE (ccast <short int &> (v));
//                BOOST_REQUIRE (ccast <short int const &> (v));
//        }

        {
                short int d = 667;
                short int &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <short int> (v));
                BOOST_REQUIRE (ccast <short int *> (v));
                BOOST_REQUIRE (ccast <short int const *> (v));
                BOOST_REQUIRE (ccast <short int &> (v));
                BOOST_REQUIRE (ccast <short int const &> (v));
        }

        {
                short int d = 667;
                short int const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <short int> (v));
                BOOST_REQUIRE (ccast <short int *> (v));
                BOOST_REQUIRE (ccast <short int const *> (v));
                BOOST_REQUIRE (ccast <short int &> (v));
                BOOST_REQUIRE (ccast <short int const &> (v));
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
                BOOST_REQUIRE (ccast <unsigned short int> (v));
                BOOST_REQUIRE (ccast <unsigned short int *> (v));
                BOOST_REQUIRE (ccast <unsigned short int const *> (v));
                BOOST_REQUIRE (ccast <unsigned short int &> (v));
                BOOST_REQUIRE (ccast <unsigned short int const &> (v));
        }

        {
                unsigned short int const d = 667;
                Variant v (d);
                BOOST_REQUIRE (ccast <unsigned short int> (v));
                BOOST_REQUIRE (ccast <unsigned short int *> (v));
                BOOST_REQUIRE (ccast <unsigned short int const *> (v));
                BOOST_REQUIRE (ccast <unsigned short int &> (v));
                BOOST_REQUIRE (ccast <unsigned short int const &> (v));
        }

//        {
//                unsigned short int d = 667;
//                unsigned short int *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <unsigned short int> (v));
//                BOOST_REQUIRE (ccast <unsigned short int *> (v));
//                BOOST_REQUIRE (ccast <unsigned short int const *> (v));
//                BOOST_REQUIRE (ccast <unsigned short int &> (v));
//                BOOST_REQUIRE (ccast <unsigned short int const &> (v));
//        }
//
//        {
//                unsigned short int d = 667;
//                unsigned short int const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <unsigned short int> (v));
//                BOOST_REQUIRE (ccast <unsigned short int *> (v));
//                BOOST_REQUIRE (ccast <unsigned short int const *> (v));
//                BOOST_REQUIRE (ccast <unsigned short int &> (v));
//                BOOST_REQUIRE (ccast <unsigned short int const &> (v));
//        }

        {
                unsigned short int d = 667;
                unsigned short int &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <unsigned short int> (v));
                BOOST_REQUIRE (ccast <unsigned short int *> (v));
                BOOST_REQUIRE (ccast <unsigned short int const *> (v));
                BOOST_REQUIRE (ccast <unsigned short int &> (v));
                BOOST_REQUIRE (ccast <unsigned short int const &> (v));
        }

        {
                unsigned short int d = 667;
                unsigned short int const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <unsigned short int> (v));
                BOOST_REQUIRE (ccast <unsigned short int *> (v));
                BOOST_REQUIRE (ccast <unsigned short int const *> (v));
                BOOST_REQUIRE (ccast <unsigned short int &> (v));
                BOOST_REQUIRE (ccast <unsigned short int const &> (v));
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
                BOOST_REQUIRE (ccast <std::string> (v));
                BOOST_REQUIRE (ccast <std::string *> (v));
                BOOST_REQUIRE (ccast <std::string const *> (v));
                BOOST_REQUIRE (ccast <std::string &> (v));
                BOOST_REQUIRE (ccast <std::string const &> (v));
        }

        {
                std::string const d = "alakot";
                Variant v (d);
                BOOST_REQUIRE (ccast <std::string> (v));
                BOOST_REQUIRE (ccast <std::string *> (v));
                BOOST_REQUIRE (ccast <std::string const *> (v));
                BOOST_REQUIRE (ccast <std::string &> (v));
                BOOST_REQUIRE (ccast <std::string const &> (v));
        }

//        {
//                std::string d = "alakot";
//                std::string *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <std::string> (v));
//                BOOST_REQUIRE (ccast <std::string *> (v));
//                BOOST_REQUIRE (ccast <std::string const *> (v));
//                BOOST_REQUIRE (ccast <std::string &> (v));
//                BOOST_REQUIRE (ccast <std::string const &> (v));
//        }
//
//        {
//                std::string d = "alakot";
//                std::string const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <std::string> (v));
//                BOOST_REQUIRE (ccast <std::string *> (v));
//                BOOST_REQUIRE (ccast <std::string const *> (v));
//                BOOST_REQUIRE (ccast <std::string &> (v));
//                BOOST_REQUIRE (ccast <std::string const &> (v));
//        }

        {
                std::string d = "alakot";
                std::string &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <std::string> (v));
                BOOST_REQUIRE (ccast <std::string *> (v));
                BOOST_REQUIRE (ccast <std::string const *> (v));
                BOOST_REQUIRE (ccast <std::string &> (v));
                BOOST_REQUIRE (ccast <std::string const &> (v));
        }

        {
                std::string d = "alakot";
                std::string const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <std::string> (v));
                BOOST_REQUIRE (ccast <std::string *> (v));
                BOOST_REQUIRE (ccast <std::string const *> (v));
                BOOST_REQUIRE (ccast <std::string &> (v));
                BOOST_REQUIRE (ccast <std::string const &> (v));
        }
}

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testCoreString)
{
        {
                Core::String d = "alakot";
                Variant v (d);
                BOOST_REQUIRE (ccast <Core::String> (v));
                BOOST_REQUIRE (ccast <Core::String *> (v));
                BOOST_REQUIRE (ccast <Core::String const *> (v));
                BOOST_REQUIRE (ccast <Core::String &> (v));
                BOOST_REQUIRE (ccast <Core::String const &> (v));
        }

        {
                Core::String const d = "alakot";
                Variant v (d);
                BOOST_REQUIRE (ccast <Core::String> (v));
                BOOST_REQUIRE (ccast <Core::String *> (v));
                BOOST_REQUIRE (ccast <Core::String const *> (v));
                BOOST_REQUIRE (ccast <Core::String &> (v));
                BOOST_REQUIRE (ccast <Core::String const &> (v));
        }

//        {
//                Core::String d = "alakot";
//                Core::String *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <Core::String> (v));
//                BOOST_REQUIRE (ccast <Core::String *> (v));
//                BOOST_REQUIRE (ccast <Core::String const *> (v));
//                BOOST_REQUIRE (ccast <Core::String &> (v));
//                BOOST_REQUIRE (ccast <Core::String const &> (v));
//        }
//
//        {
//                Core::String d = "alakot";
//                Core::String const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <Core::String> (v));
//                BOOST_REQUIRE (ccast <Core::String *> (v));
//                BOOST_REQUIRE (ccast <Core::String const *> (v));
//                BOOST_REQUIRE (ccast <Core::String &> (v));
//                BOOST_REQUIRE (ccast <Core::String const &> (v));
//        }

        {
                Core::String d = "alakot";
                Core::String &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <Core::String> (v));
                BOOST_REQUIRE (ccast <Core::String *> (v));
                BOOST_REQUIRE (ccast <Core::String const *> (v));
                BOOST_REQUIRE (ccast <Core::String &> (v));
                BOOST_REQUIRE (ccast <Core::String const &> (v));
        }

        {
                Core::String d = "alakot";
                Core::String const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <Core::String> (v));
                BOOST_REQUIRE (ccast <Core::String *> (v));
                BOOST_REQUIRE (ccast <Core::String const *> (v));
                BOOST_REQUIRE (ccast <Core::String &> (v));
                BOOST_REQUIRE (ccast <Core::String const &> (v));
        }
}

BOOST_AUTO_TEST_SUITE_END ();
