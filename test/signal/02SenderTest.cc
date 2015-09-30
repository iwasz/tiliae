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
#include "testHelpers/TestHelpers.h"

using namespace Core;
using namespace Signal;

BOOST_AUTO_TEST_SUITE (SenderTest);

/**
 * Wysyła sygnał clicked.
 */
struct Button {

        Button () : sender ("clicked2"),
                    sender01 ("clicked3") {}

        // Emituje sygnał "clicked" w aktualnym scope.
        void click () {
                sender.emit ();
        }

        void click2 () {
                sender01.emit ();
        }

        Sender sender;
        Sender sender01;
};

/**
 * Test sendera.
 */
BOOST_AUTO_TEST_CASE (test)
{
        Handler handler;
        Button button;

        button.click ();
        BOOST_CHECK (handler.iValue == 778890);

        button.click2 ();
        BOOST_CHECK (handler.iValue == 778891);
}

BOOST_AUTO_TEST_SUITE_END ();
