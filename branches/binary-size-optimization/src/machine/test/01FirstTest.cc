/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#define BOOST_TEST_MODULE StateMachineTest
#define BOOST_TEST_DYN_LINK
 
#include <boost/test/unit_test.hpp>
#include "Helper.h"
#include "Machine.h"

BOOST_AUTO_TEST_SUITE (FirstTest);
using namespace Machine;
using namespace boost;

BOOST_AUTO_TEST_CASE (testBasic)
{
        HelperAT helper;
        Core::VariantMap params;
        params["helper"] = Core::Variant (&helper);

//        Ptr <Machine> machine = make_shared <Machine> (params);
//        Ptr <State> state = make_shared <State> ("begin");
//        state->addEntryAction (make_shared <K202Action> ("$helper.inc ()")); // To się nie wykona, bo begin
//        state->addExitAction (make_shared <K202Action> ("$helper.inc ()"));
//        state->addTransition (make_shared <Transition> ("event", "state"));
//        state->setType (IState::BEGIN);
//        machine->addState (state);
//
//        state = make_shared <State> ("state");
//        state->addEntryAction (make_shared <K202Action> ("$helper.inc ()"));
//        state->addExitAction (make_shared <K202Action> ("$helper.inc ()"));
//        state->addTransition (make_shared <Transition> ("event2", "end"));
//        machine->addState (state);
//
//        state = make_shared <State> ("end");
//        state->addEntryAction (make_shared <K202Action> ("$helper.inc ()"));
//        state->addExitAction (make_shared <K202Action> ("$helper.inc ()")); // To się nie wykona.
//        state->setType (IState::END);
//        machine->addState (state);
//
///*--------------------------------------------------------------------------*/
//
//        BOOST_REQUIRE (!machine->getCurrentState ());
//        BOOST_REQUIRE_EQUAL (helper.cnt, 0);
//
//        machine->event (Event ("event"));
//        BOOST_REQUIRE (machine->getCurrentState ());
//        BOOST_REQUIRE_EQUAL (machine->getCurrentState ()->getName (), "state");
//        BOOST_REQUIRE_EQUAL (helper.cnt, 2);
}
 
BOOST_AUTO_TEST_SUITE_END ();
