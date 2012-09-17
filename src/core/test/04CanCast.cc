/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>

#include "core/variant/Cast.h"

BOOST_AUTO_TEST_SUITE (CanCast);

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
                BOOST_REQUIRE (ccast <bool> (v));
                BOOST_REQUIRE (ccast <bool *> (v));
                BOOST_REQUIRE (ccast <bool const *> (v));
                BOOST_REQUIRE (ccast <bool &> (v));
                BOOST_REQUIRE (ccast <bool const &> (v));
        }

        {
                bool const d = true;
                Variant v (d);
                BOOST_REQUIRE (ccast <bool> (v));
                BOOST_REQUIRE (ccast <bool *> (v));
                BOOST_REQUIRE (ccast <bool const *> (v));
                BOOST_REQUIRE (ccast <bool &> (v));
                BOOST_REQUIRE (ccast <bool const &> (v));
        }

//        {
//                bool d = true;
//                bool *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <bool> (v));
//                BOOST_REQUIRE (ccast <bool *> (v));
//                BOOST_REQUIRE (ccast <bool const *> (v));
//                BOOST_REQUIRE (ccast <bool &> (v));
//                BOOST_REQUIRE (ccast <bool const &> (v));
//        }

//        {
//                bool d = true;
//                bool const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <bool> (v));
//                BOOST_REQUIRE (ccast <bool *> (v));
//                BOOST_REQUIRE (ccast <bool const *> (v));
//                BOOST_REQUIRE (ccast <bool &> (v));
//                BOOST_REQUIRE (ccast <bool const &> (v));
//        }

        {
                bool d = true;
                bool &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <bool> (v));
                BOOST_REQUIRE (ccast <bool *> (v));
                BOOST_REQUIRE (ccast <bool const *> (v));
                BOOST_REQUIRE (ccast <bool &> (v));
                BOOST_REQUIRE (ccast <bool const &> (v));
        }

        {
                bool d = true;
                bool const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <bool> (v));
                BOOST_REQUIRE (ccast <bool *> (v));
                BOOST_REQUIRE (ccast <bool const *> (v));
                BOOST_REQUIRE (ccast <bool &> (v));
                BOOST_REQUIRE (ccast <bool const &> (v));
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
                BOOST_REQUIRE (ccast <char> (v));
                BOOST_REQUIRE (ccast <char *> (v));
                BOOST_REQUIRE (ccast <char const *> (v));
                BOOST_REQUIRE (ccast <char &> (v));
                BOOST_REQUIRE (ccast <char const &> (v));
        }

        {
                char const d = 'a';
                Variant v (d);
                BOOST_REQUIRE (ccast <char> (v));
                BOOST_REQUIRE (ccast <char *> (v));
                BOOST_REQUIRE (ccast <char const *> (v));
                BOOST_REQUIRE (ccast <char &> (v));
                BOOST_REQUIRE (ccast <char const &> (v));
        }

//        {
//                char d = 'a';
//                char *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <char> (v));
//                BOOST_REQUIRE (ccast <char *> (v));
//                BOOST_REQUIRE (ccast <char const *> (v));
//                BOOST_REQUIRE (ccast <char &> (v));
//                BOOST_REQUIRE (ccast <char const &> (v));
//        }
//
//        {
//                char d = 'a';
//                char const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <char> (v));
//                BOOST_REQUIRE (ccast <char *> (v));
//                BOOST_REQUIRE (ccast <char const *> (v));
//                BOOST_REQUIRE (ccast <char &> (v));
//                BOOST_REQUIRE (ccast <char const &> (v));
//        }

        {
                char d = 'a';
                char &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <char> (v));
                BOOST_REQUIRE (ccast <char *> (v));
                BOOST_REQUIRE (ccast <char const *> (v));
                BOOST_REQUIRE (ccast <char &> (v));
                BOOST_REQUIRE (ccast <char const &> (v));
        }

        {
                char d = 'a';
                char const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <char> (v));
                BOOST_REQUIRE (ccast <char *> (v));
                BOOST_REQUIRE (ccast <char const *> (v));
                BOOST_REQUIRE (ccast <char &> (v));
                BOOST_REQUIRE (ccast <char const &> (v));
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
                BOOST_REQUIRE (ccast <unsigned char> (v));
                BOOST_REQUIRE (ccast <unsigned char *> (v));
                BOOST_REQUIRE (ccast <unsigned char const *> (v));
                BOOST_REQUIRE (ccast <unsigned char &> (v));
                BOOST_REQUIRE (ccast <unsigned char const &> (v));
        }

        {
                unsigned char const d = 129;
                Variant v (d);
                BOOST_REQUIRE (ccast <unsigned char> (v));
                BOOST_REQUIRE (ccast <unsigned char *> (v));
                BOOST_REQUIRE (ccast <unsigned char const *> (v));
                BOOST_REQUIRE (ccast <unsigned char &> (v));
                BOOST_REQUIRE (ccast <unsigned char const &> (v));
        }

//        {
//                unsigned char d = 129;
//                unsigned char *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <unsigned char> (v));
//                BOOST_REQUIRE (ccast <unsigned char *> (v));
//                BOOST_REQUIRE (ccast <unsigned char const *> (v));
//                BOOST_REQUIRE (ccast <unsigned char &> (v));
//                BOOST_REQUIRE (ccast <unsigned char const &> (v));
//        }
//
//        {
//                unsigned char d = 129;
//                unsigned char const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <unsigned char> (v));
//                BOOST_REQUIRE (ccast <unsigned char *> (v));
//                BOOST_REQUIRE (ccast <unsigned char const *> (v));
//                BOOST_REQUIRE (ccast <unsigned char &> (v));
//                BOOST_REQUIRE (ccast <unsigned char const &> (v));
//        }

        {
                unsigned char d = 129;
                unsigned char &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <unsigned char> (v));
                BOOST_REQUIRE (ccast <unsigned char *> (v));
                BOOST_REQUIRE (ccast <unsigned char const *> (v));
                BOOST_REQUIRE (ccast <unsigned char &> (v));
                BOOST_REQUIRE (ccast <unsigned char const &> (v));
        }

        {
                unsigned char d = 129;
                unsigned char const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <unsigned char> (v));
                BOOST_REQUIRE (ccast <unsigned char *> (v));
                BOOST_REQUIRE (ccast <unsigned char const *> (v));
                BOOST_REQUIRE (ccast <unsigned char &> (v));
                BOOST_REQUIRE (ccast <unsigned char const &> (v));
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
                BOOST_REQUIRE (ccast <double> (v));
                BOOST_REQUIRE (ccast <double *> (v));
                BOOST_REQUIRE (ccast <double const *> (v));
                BOOST_REQUIRE (ccast <double &> (v));
                BOOST_REQUIRE (ccast <double const &> (v));
        }

        {
                double const d = 666.0;
                Variant v (d);
                BOOST_REQUIRE (ccast <double> (v));
                BOOST_REQUIRE (ccast <double *> (v));
                BOOST_REQUIRE (ccast <double const *> (v));
                BOOST_REQUIRE (ccast <double &> (v));
                BOOST_REQUIRE (ccast <double const &> (v));
        }

//        {
//                double d = 666.0;
//                double *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <double> (v));
//                BOOST_REQUIRE (ccast <double *> (v));
//                BOOST_REQUIRE (ccast <double const *> (v));
//                BOOST_REQUIRE (ccast <double &> (v));
//                BOOST_REQUIRE (ccast <double const &> (v));
//        }
//
//        {
//                double d = 666.0;
//                double const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <double> (v));
//                BOOST_REQUIRE (ccast <double *> (v));
//                BOOST_REQUIRE (ccast <double const *> (v));
//                BOOST_REQUIRE (ccast <double &> (v));
//                BOOST_REQUIRE (ccast <double const &> (v));
//        }

        {
                double d = 666.0;
                double &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <double> (v));
                BOOST_REQUIRE (ccast <double *> (v));
                BOOST_REQUIRE (ccast <double const *> (v));
                BOOST_REQUIRE (ccast <double &> (v));
                BOOST_REQUIRE (ccast <double const &> (v));
        }

        {
                double d = 666.0;
                double const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <double> (v));
                BOOST_REQUIRE (ccast <double *> (v));
                BOOST_REQUIRE (ccast <double const *> (v));
                BOOST_REQUIRE (ccast <double &> (v));
                BOOST_REQUIRE (ccast <double const &> (v));
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
                BOOST_REQUIRE (ccast <long double> (v));
                BOOST_REQUIRE (ccast <long double *> (v));
                BOOST_REQUIRE (ccast <long double const *> (v));
                BOOST_REQUIRE (ccast <long double &> (v));
                BOOST_REQUIRE (ccast <long double const &> (v));
        }

        {
                long double const d = 666.0;
                Variant v (d);
                BOOST_REQUIRE (ccast <long double> (v));
                BOOST_REQUIRE (ccast <long double *> (v));
                BOOST_REQUIRE (ccast <long double const *> (v));
                BOOST_REQUIRE (ccast <long double &> (v));
                BOOST_REQUIRE (ccast <long double const &> (v));
        }

//        {
//                long double d = 666.0;
//                long double *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <long double> (v));
//                BOOST_REQUIRE (ccast <long double *> (v));
//                BOOST_REQUIRE (ccast <long double const *> (v));
//                BOOST_REQUIRE (ccast <long double &> (v));
//                BOOST_REQUIRE (ccast <long double const &> (v));
//        }
//
//        {
//                long double d = 666.0;
//                long double const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <long double> (v));
//                BOOST_REQUIRE (ccast <long double *> (v));
//                BOOST_REQUIRE (ccast <long double const *> (v));
//                BOOST_REQUIRE (ccast <long double &> (v));
//                BOOST_REQUIRE (ccast <long double const &> (v));
//        }

        {
                long double d = 666.0;
                long double &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <long double> (v));
                BOOST_REQUIRE (ccast <long double *> (v));
                BOOST_REQUIRE (ccast <long double const *> (v));
                BOOST_REQUIRE (ccast <long double &> (v));
                BOOST_REQUIRE (ccast <long double const &> (v));
        }

        {
                long double d = 666.0;
                long double const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <long double> (v));
                BOOST_REQUIRE (ccast <long double *> (v));
                BOOST_REQUIRE (ccast <long double const *> (v));
                BOOST_REQUIRE (ccast <long double &> (v));
                BOOST_REQUIRE (ccast <long double const &> (v));
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
                BOOST_REQUIRE (ccast <float> (v));
                BOOST_REQUIRE (ccast <float *> (v));
                BOOST_REQUIRE (ccast <float const *> (v));
                BOOST_REQUIRE (ccast <float &> (v));
                BOOST_REQUIRE (ccast <float const &> (v));
        }

        {
                float const d = 666.0;
                Variant v (d);
                BOOST_REQUIRE (ccast <float> (v));
                BOOST_REQUIRE (ccast <float *> (v));
                BOOST_REQUIRE (ccast <float const *> (v));
                BOOST_REQUIRE (ccast <float &> (v));
                BOOST_REQUIRE (ccast <float const &> (v));
        }

//        {
//                float d = 666.0;
//                float *pd = &d;
//                Variant v (pd);
//                BOOST_REQUIRE (ccast <float> (v));
//                BOOST_REQUIRE (ccast <float *> (v));
//                BOOST_REQUIRE (ccast <float const *> (v));
//                BOOST_REQUIRE (ccast <float &> (v));
//                BOOST_REQUIRE (ccast <float const &> (v));
//        }
//
//        {
//                float d = 666.0;
//                float const *cpd = &d;
//                Variant v (cpd);
//                BOOST_REQUIRE (ccast <float> (v));
//                BOOST_REQUIRE (ccast <float *> (v));
//                BOOST_REQUIRE (ccast <float const *> (v));
//                BOOST_REQUIRE (ccast <float &> (v));
//                BOOST_REQUIRE (ccast <float const &> (v));
//        }

        {
                float d = 666.0;
                float &rd = d;
                Variant v (rd);
                BOOST_REQUIRE (ccast <float> (v));
                BOOST_REQUIRE (ccast <float *> (v));
                BOOST_REQUIRE (ccast <float const *> (v));
                BOOST_REQUIRE (ccast <float &> (v));
                BOOST_REQUIRE (ccast <float const &> (v));
        }

        {
                float d = 666.0;
                float const &crd = d;
                Variant v (crd);
                BOOST_REQUIRE (ccast <float> (v));
                BOOST_REQUIRE (ccast <float *> (v));
                BOOST_REQUIRE (ccast <float const *> (v));
                BOOST_REQUIRE (ccast <float &> (v));
                BOOST_REQUIRE (ccast <float const &> (v));
        }
}

BOOST_AUTO_TEST_SUITE_END ();
