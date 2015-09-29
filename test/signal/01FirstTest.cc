/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#define BOOST_TEST_MODULE SignalTests
#define BOOST_TEST_DYN_LINK
 
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <k202/K202.h>
#include "reflection/Reflection.h"
#include <signal/Signal.h>

BOOST_AUTO_TEST_SUITE (FirstTest);
using namespace Core;
using namespace Signal;

/**
 * Testuje wysyłanie, ale trochę omijając API.
 * 1. Tworzy obiekt typu Receiver (klasa wyżej).
 * 2. Ten obiekt ma 4 listenery, każdy ma od razu podpięty scope (ponieważ ma podaną nazwę sygnału).
 * 3. Funkcja testBasic znajduje te scopy i wykonuje na nich metodę emit.
 */
BOOST_AUTO_TEST_CASE (testBasic)
{
        Receiver recv;

        Ptr <Scope> scope = findScope ("clicked");
        BOOST_CHECK (scope);
        BOOST_CHECK (!recv.iValue);

        scope->emit (VariantVector (), VariantMap ());
        BOOST_CHECK_EQUAL (recv.iValue, 667);

        scope = findScope ("sig0");
        scope->emit (VariantVector (), VariantMap ());
        BOOST_CHECK_EQUAL (recv.iValue, 668);

        // A teraz z paramerami:
        scope = findScope ("sig1");
        VariantVector v;
        v.push_back (Core::Variant (8876));
        scope->emit (v, VariantMap ());
        BOOST_CHECK_EQUAL (recv.iValue, 8876);

        scope = findScope ("sig2");
        recv.iValue = 0;
        v.push_back (Core::Variant (std::string ("ojojojoj!")));
        Variant ret = scope->emit (v, VariantMap ());

        BOOST_CHECK_EQUAL (recv.iValue, 8876);
        BOOST_CHECK_EQUAL (recv.sValue, "ojojojoj!");
        BOOST_CHECK_EQUAL (vcast <int> (ret), 666);
}
 
BOOST_AUTO_TEST_SUITE_END ();
