/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <K202.h>
#include <Reflection.h>
#include <Signal.h>

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
 * Odbiera sygnał od buttona.
 */
struct Handler {

        REFLECTION_CONSTRUCTOR_(void);

        Handler () :
                onClickedListener (this, "$onClicked ()", "clicked2"),
                onClickedListener2 (this, "$onClicked3 ()", "clicked3"),
                iValue (0) {}

        REFLECTION_METHOD (onClicked) void onClicked ()
        {
                iValue = 778890;
        }

        REFLECTION_METHOD (onClicked3) void onClicked3 ()
        {
                ++iValue;
        }

        Listener onClickedListener, onClickedListener2;
        int iValue;

        REFLECTION_END (Handler);
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
