/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#define BOOST_TEST_MODULE LightCoreTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <iostream>

#include "core/variant/Cast.h"

BOOST_AUTO_TEST_SUITE (Variant01);

using namespace boost;
using namespace Core;

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testBool)
{
        {
                bool d = true;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <bool> (v), true);
                BOOST_REQUIRE_EQUAL (*(vcast <bool *> (v)), true);
                BOOST_REQUIRE_EQUAL (*(vcast <bool const *>) (v), true);
                BOOST_REQUIRE_EQUAL (vcast <bool &> (v), true);
                BOOST_REQUIRE_EQUAL (vcast <bool const &> (v), true);
        }

        {
                bool const d = true;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <bool> (v), true);
                BOOST_REQUIRE_EQUAL (*(vcast <bool *> (v)), true);
                BOOST_REQUIRE_EQUAL (*(vcast <bool const *>) (v), true);
                BOOST_REQUIRE_EQUAL (vcast <bool &> (v), true);
                BOOST_REQUIRE_EQUAL (vcast <bool const &> (v), true);
        }

//        {
//                bool d = true;
//                bool *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE_EQUAL (vcast <bool> (v), true);
//                BOOST_REQUIRE_EQUAL (*(vcast <bool *> (v)), true);
//                BOOST_REQUIRE_EQUAL (*(vcast <bool const *>) (v), true);
//                BOOST_REQUIRE_EQUAL (vcast <bool &> (v), true);
//                BOOST_REQUIRE_EQUAL (vcast <bool const &> (v), true);
//        }
//
//        {
//                bool d = true;
//                bool const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE_EQUAL (vcast <bool> (v), true);
//                BOOST_REQUIRE_EQUAL (*(vcast <bool *> (v)), true);
//                BOOST_REQUIRE_EQUAL (*(vcast <bool const *>) (v), true);
//                BOOST_REQUIRE_EQUAL (vcast <bool &> (v), true);
//                BOOST_REQUIRE_EQUAL (vcast <bool const &> (v), true);
//        }

        {
                bool d = true;
                bool &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <bool> (v), true);
                BOOST_REQUIRE_EQUAL (*(vcast <bool *> (v)), true);
                BOOST_REQUIRE_EQUAL (*(vcast <bool const *>) (v), true);
                BOOST_REQUIRE_EQUAL (vcast <bool &> (v), true);
                BOOST_REQUIRE_EQUAL (vcast <bool const &> (v), true);
        }

        {
                bool d = true;
                bool const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <bool> (v), true);
                BOOST_REQUIRE_EQUAL (*(vcast <bool *> (v)), true);
                BOOST_REQUIRE_EQUAL (*(vcast <bool const *>) (v), true);
                BOOST_REQUIRE_EQUAL (vcast <bool &> (v), true);
                BOOST_REQUIRE_EQUAL (vcast <bool const &> (v), true);
        }
}

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testChar)
{
        {
                char d = 'a';
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <char> (v), 'a');
                BOOST_REQUIRE_EQUAL (*(vcast <char *> (v)), 'a');
                BOOST_REQUIRE_EQUAL (*(vcast <char const *>) (v), 'a');
                BOOST_REQUIRE_EQUAL (vcast <char &> (v), 'a');
                BOOST_REQUIRE_EQUAL (vcast <char const &> (v), 'a');
        }

        {
                char const d = 'a';
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <char> (v), 'a');
                BOOST_REQUIRE_EQUAL (*(vcast <char *> (v)), 'a');
                BOOST_REQUIRE_EQUAL (*(vcast <char const *>) (v), 'a');
                BOOST_REQUIRE_EQUAL (vcast <char &> (v), 'a');
                BOOST_REQUIRE_EQUAL (vcast <char const &> (v), 'a');
        }

//        {
//                char d = 'a';
//                char *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE_EQUAL (vcast <char> (v), 'a');
//                BOOST_REQUIRE_EQUAL (*(vcast <char *> (v)), 'a');
//                BOOST_REQUIRE_EQUAL (*(vcast <char const *>) (v), 'a');
//                BOOST_REQUIRE_EQUAL (vcast <char &> (v), 'a');
//                BOOST_REQUIRE_EQUAL (vcast <char const &> (v), 'a');
//        }
//
//        {
//                char d = 'a';
//                char const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE_EQUAL (vcast <char> (v), 'a');
//                BOOST_REQUIRE_EQUAL (*(vcast <char *> (v)), 'a');
//                BOOST_REQUIRE_EQUAL (*(vcast <char const *>) (v), 'a');
//                BOOST_REQUIRE_EQUAL (vcast <char &> (v), 'a');
//                BOOST_REQUIRE_EQUAL (vcast <char const &> (v), 'a');
//        }

        {
                char d = 'a';
                char &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <char> (v), 'a');
                BOOST_REQUIRE_EQUAL (*(vcast <char *> (v)), 'a');
                BOOST_REQUIRE_EQUAL (*(vcast <char const *>) (v), 'a');
                BOOST_REQUIRE_EQUAL (vcast <char &> (v), 'a');
                BOOST_REQUIRE_EQUAL (vcast <char const &> (v), 'a');
        }

        {
                char d = 'a';
                char const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <char> (v), 'a');
                BOOST_REQUIRE_EQUAL (*(vcast <char *> (v)), 'a');
                BOOST_REQUIRE_EQUAL (*(vcast <char const *>) (v), 'a');
                BOOST_REQUIRE_EQUAL (vcast <char &> (v), 'a');
                BOOST_REQUIRE_EQUAL (vcast <char const &> (v), 'a');
        }
}

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testUnsignedChar)
{
        {
                unsigned char d = 129;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <unsigned char> (v), 129);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned char *> (v)), 129);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned char const *>) (v), 129);
                BOOST_REQUIRE_EQUAL (vcast <unsigned char &> (v), 129);
                BOOST_REQUIRE_EQUAL (vcast <unsigned char const &> (v), 129);
        }

        {
                unsigned char const d = 129;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <unsigned char> (v), 129);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned char *> (v)), 129);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned char const *>) (v), 129);
                BOOST_REQUIRE_EQUAL (vcast <unsigned char &> (v), 129);
                BOOST_REQUIRE_EQUAL (vcast <unsigned char const &> (v), 129);
        }

//        {
//                unsigned char d = 129;
//                unsigned char *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned char> (v), 129);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned char *> (v)), 129);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned char const *>) (v), 129);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned char &> (v), 129);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned char const &> (v), 129);
//        }
//
//        {
//                unsigned char d = 129;
//                unsigned char const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned char> (v), 129);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned char *> (v)), 129);
//                BOOST_REQUIRE_EQUAL (*(vcast <unsigned char const *>) (v), 129);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned char &> (v), 129);
//                BOOST_REQUIRE_EQUAL (vcast <unsigned char const &> (v), 129);
//        }

        {
                unsigned char d = 129;
                unsigned char &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <unsigned char> (v), 129);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned char *> (v)), 129);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned char const *>) (v), 129);
                BOOST_REQUIRE_EQUAL (vcast <unsigned char &> (v), 129);
                BOOST_REQUIRE_EQUAL (vcast <unsigned char const &> (v), 129);
        }

        {
                unsigned char d = 129;
                unsigned char const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <unsigned char> (v), 129);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned char *> (v)), 129);
                BOOST_REQUIRE_EQUAL (*(vcast <unsigned char const *>) (v), 129);
                BOOST_REQUIRE_EQUAL (vcast <unsigned char &> (v), 129);
                BOOST_REQUIRE_EQUAL (vcast <unsigned char const &> (v), 129);
        }
}

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testDouble)
{
        {
                double d = 666.0;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <double> (v), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <double *> (v)), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <double const *>) (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <double &> (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <double const &> (v), 666.0);
        }

        {
                double const d = 666.0;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <double> (v), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <double *> (v)), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <double const *>) (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <double &> (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <double const &> (v), 666.0);
        }

//        {
//                double d = 666.0;
//                double *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE_EQUAL (vcast <double> (v), 666.0);
//                BOOST_REQUIRE_EQUAL (*(vcast <double *> (v)), 666.0);
//                BOOST_REQUIRE_EQUAL (*(vcast <double const *>) (v), 666.0);
//                BOOST_REQUIRE_EQUAL (vcast <double &> (v), 666.0);
//                BOOST_REQUIRE_EQUAL (vcast <double const &> (v), 666.0);
//        }
//
//        {
//                double d = 666.0;
//                double const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE_EQUAL (vcast <double> (v), 666.0);
//                BOOST_REQUIRE_EQUAL (*(vcast <double *> (v)), 666.0);
//                BOOST_REQUIRE_EQUAL (*(vcast <double const *>) (v), 666.0);
//                BOOST_REQUIRE_EQUAL (vcast <double &> (v), 666.0);
//                BOOST_REQUIRE_EQUAL (vcast <double const &> (v), 666.0);
//        }

        {
                double d = 666.0;
                double &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <double> (v), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <double *> (v)), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <double const *>) (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <double &> (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <double const &> (v), 666.0);
        }

        {
                double d = 666.0;
                double const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <double> (v), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <double *> (v)), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <double const *>) (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <double &> (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <double const &> (v), 666.0);
        }
}

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testLongDouble)
{
        {
                long double d = 666.0;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <long double> (v), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <long double *> (v)), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <long double const *>) (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <long double &> (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <long double const &> (v), 666.0);
        }

        {
                long double const d = 666.0;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <long double> (v), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <long double *> (v)), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <long double const *>) (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <long double &> (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <long double const &> (v), 666.0);
        }

//        {
//                long double d = 666.0;
//                long double *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE_EQUAL (vcast <long double> (v), 666.0);
//                BOOST_REQUIRE_EQUAL (*(vcast <long double *> (v)), 666.0);
//                BOOST_REQUIRE_EQUAL (*(vcast <long double const *>) (v), 666.0);
//                BOOST_REQUIRE_EQUAL (vcast <long double &> (v), 666.0);
//                BOOST_REQUIRE_EQUAL (vcast <long double const &> (v), 666.0);
//        }
//
//        {
//                long double d = 666.0;
//                long double const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE_EQUAL (vcast <long double> (v), 666.0);
//                BOOST_REQUIRE_EQUAL (*(vcast <long double *> (v)), 666.0);
//                BOOST_REQUIRE_EQUAL (*(vcast <long double const *>) (v), 666.0);
//                BOOST_REQUIRE_EQUAL (vcast <long double &> (v), 666.0);
//                BOOST_REQUIRE_EQUAL (vcast <long double const &> (v), 666.0);
//        }

        {
                long double d = 666.0;
                long double &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <long double> (v), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <long double *> (v)), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <long double const *>) (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <long double &> (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <long double const &> (v), 666.0);
        }

        {
                long double d = 666.0;
                long double const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <long double> (v), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <long double *> (v)), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <long double const *>) (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <long double &> (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <long double const &> (v), 666.0);
        }
}

/**
 * Testuje wszystkie możliwe przypadki kastowania warianta z i na typ.
 */
BOOST_AUTO_TEST_CASE (testFloat)
{
        {
                float d = 666.0;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <float> (v), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <float *> (v)), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <float const *>) (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <float &> (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <float const &> (v), 666.0);
        }

        {
                float const d = 666.0;
                Variant v (d);
                BOOST_REQUIRE_EQUAL (vcast <float> (v), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <float *> (v)), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <float const *>) (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <float &> (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <float const &> (v), 666.0);
        }

//        {
//                float d = 666.0;
//                float *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE_EQUAL (vcast <float> (v), 666.0);
//                BOOST_REQUIRE_EQUAL (*(vcast <float *> (v)), 666.0);
//                BOOST_REQUIRE_EQUAL (*(vcast <float const *>) (v), 666.0);
//                BOOST_REQUIRE_EQUAL (vcast <float &> (v), 666.0);
//                BOOST_REQUIRE_EQUAL (vcast <float const &> (v), 666.0);
//        }
//
//        {
//                float d = 666.0;
//                float const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE_EQUAL (vcast <float> (v), 666.0);
//                BOOST_REQUIRE_EQUAL (*(vcast <float *> (v)), 666.0);
//                BOOST_REQUIRE_EQUAL (*(vcast <float const *>) (v), 666.0);
//                BOOST_REQUIRE_EQUAL (vcast <float &> (v), 666.0);
//                BOOST_REQUIRE_EQUAL (vcast <float const &> (v), 666.0);
//        }

        {
                float d = 666.0;
                float &rd = d;
                Variant v (rd);
                BOOST_REQUIRE_EQUAL (vcast <float> (v), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <float *> (v)), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <float const *>) (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <float &> (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <float const &> (v), 666.0);
        }

        {
                float d = 666.0;
                float const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE_EQUAL (vcast <float> (v), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <float *> (v)), 666.0);
                BOOST_REQUIRE_EQUAL (*(vcast <float const *>) (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <float &> (v), 666.0);
                BOOST_REQUIRE_EQUAL (vcast <float const &> (v), 666.0);
        }
}

BOOST_AUTO_TEST_SUITE_END ();
