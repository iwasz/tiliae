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
#include <K202.h>
#include <Reflection.h>
#include <Signal.h>

BOOST_AUTO_TEST_SUITE (FirstTest);
using namespace Core;
using namespace Signal;

/**
 * Odbiera. W konstruktorze, lub gdzieś indziej należy włączyć
 * nasłuch, czyli inaczej "podłączyć" sygnał.
 */
struct Receiver {

        c__(void);

        Receiver () : onClicked (this, "$onClicked1 ()", "clicked"),
                        onSig0 (this, "$handler2 (668)", "sig0"),
                        onSig1 (this, "$handler2 (%0)", "sig1"),
                        onSig2 (this, "$handler3 (%0, %1)", "sig2"),
                        iValue (0)
                        {}

        m_ (onClicked1) void onClicked1 () { iValue = 667; }
        m_ (handler2) void handler2 (int i) { iValue = i; }

        m_ (handler3) int handler3 (int i, const Core::String &nam)
        {
                iValue = i;
                sValue = nam;
                return 666;
        }

        Listener onClicked, onSig0, onSig1, onSig2;
        int iValue;
        Core::String sValue;

        e_ (Receiver);
};

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
        v.push_back (Core::Variant (String ("ojojojoj!")));
        Variant ret = scope->emit (v, VariantMap ());

        BOOST_CHECK_EQUAL (recv.iValue, 8876);
        BOOST_CHECK_EQUAL (recv.sValue, "ojojojoj!");
        BOOST_CHECK_EQUAL (vcast <int> (ret), 666);
}
 
BOOST_AUTO_TEST_SUITE_END ();
