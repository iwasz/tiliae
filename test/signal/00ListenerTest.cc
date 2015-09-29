/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <k202/K202.h>
#include "reflection/Reflection.h"
#include <signal/Signal.h>
#include <cassert>

using namespace Core;
using namespace Signal;

BOOST_AUTO_TEST_SUITE (ListenerTest);

/**
 * Testuje wysyłanie, ale trochę omijając API.
 */
BOOST_AUTO_TEST_CASE (testBasic)
{
        Receiver2 recv;

        Ptr <Scope> scope = Signal::findScope ("/scope/sig3");
        BOOST_CHECK (scope);

        scope->emit (VariantVector (), VariantMap ());
        BOOST_CHECK_EQUAL (recv.iValue, 3);

        recv.iValue = 0;

        scope = findScope ("/sig4");
        assert (scope);

        scope->emit (VariantVector (), VariantMap ());
        BOOST_CHECK_EQUAL (recv.iValue, 4);

        // Testuje globalną funkcję, której podajemy nazwę sygnału
        recv.iValue = 0;
        Signal::emit ("/sig4");
        BOOST_CHECK_EQUAL (recv.iValue, 4);

        // Testuje globalną funkcję, której podajemy wskaźnik do scope
        recv.iValue = 0;
        Signal::emit (scope);
        BOOST_CHECK_EQUAL (recv.iValue, 4);
}

/****************************************************************************/

/**
 * Listenery z relatywnym sygnałem można podpiąć do wielu scopów,
 * a te z absolutnym tylko do jednego. Ten test sprawdza, czy
 * implementacja działa prawidłowo, czyli tak jak napisałem.
 */
BOOST_AUTO_TEST_CASE (testAddReativeListener)
{
        Receiver3 recv;

        Ptr <Scope> scpe = findScope ("/scpe/clck2");
        BOOST_CHECK (scpe);
        BOOST_CHECK (!scpe->isEmpty());

        // Tu jest listener clkc2
        BOOST_CHECK_EQUAL (scpe->countListeners (), 1);

        // Teraz clck1 i clck2 dodane są do /scpe10
        bind ("/scpe10", &recv);

        Ptr <Scope> scpe10 = findScope ("/scpe10");
        BOOST_REQUIRE (scpe10);

        // clck1 i clck2 - do zastanowienia się...
        BOOST_CHECK_EQUAL (scpe10->countListeners (), 2);

        // Jednak w tym pierwszym nadal jest tylko jeden, bo jego nie ruszałem
        BOOST_CHECK_EQUAL (scpe->countListeners (), 1);

        Variant ret = emit ("/scpe/clck2");
        BOOST_CHECK_EQUAL (vcast <int> (ret), 2);

        // Tu uruchamiają się 2 sygnały i zwracana jest wartość tylko ostatniego z nich (najwyraźniej 2!)
        ret = emit ("/scpe10");
        BOOST_CHECK_EQUAL (vcast <int> (ret), 2);

        ret = emit ("sygnal-ktorego-nie-ma");
}

BOOST_AUTO_TEST_SUITE_END ();
