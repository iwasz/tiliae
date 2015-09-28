/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include "State.h"
#include "Machine.h"
#include "Helper.h"
#include "context/Context.h"
#include "action/K202Action.h"
#include "condition/Condition.h"
#include "extension/StackStateExtension.h"

BOOST_AUTO_TEST_SUITE (ShutDownResetTest);
 
using namespace StateMachine;
using namespace Core;

/**
 * Przejście do stanu @shutDown
 */
BOOST_AUTO_TEST_CASE (testShutDown)
{
        // Stany
        Ptr <State> state1 = State::create ("state1");
        state1->addEntryAction (K202Action::create ("$helper.inc ()"));
        state1->addExitAction (K202Action::create ("$helper.inc ()"));

        Ptr <State> state2 = State::create ("state2");
        state2->addEntryAction (K202Action::create ("$helper.inc ()"));
        state2->addExitAction (K202Action::create ("$helper.inc ()"));

        // Przejścia
        Ptr <Transition> transition = Transition::create ("state1", "state2",
                                  K202Condition::create ("$!clicked"));

        Ptr <Transition> transition2 = Transition::create ("state1", "@shutDown",
                                  K202Condition::create ("$!backClicked"));

        // Helper będzie w kontekście w zakresie "MACHINE"
        HelperAT helper;
        VariantMap mach;
        mach["helper"] = Core::Variant (&helper);

        // Maszyna
        Machine machine (mach);
        machine.addState (state1);
        machine.addState (state2);
        state1->addTransition (transition);
        state1->addTransition (transition2);
        machine.setInitialStateName ("state1");

/*-- odpalamy maszynę ------------------------------------------------------*/

        VariantMap trans;

        // 1.
        machine.run ();
        BOOST_CHECK (machine.getCurrentStateName () == "state1");
        BOOST_CHECK (helper.cnt == 1);

        // 2.
        trans["backClicked"] = Core::Variant (true);
        machine.run (Core::VariantMap (), trans);
        BOOST_CHECK (helper.cnt == 2);
        BOOST_CHECK (machine.getCurrentStateName () == "");

        // 3. Już nic się nie dzieje, nie działa maszyna
        machine.run ();
        BOOST_CHECK (machine.getCurrentStateName () == "");
        BOOST_CHECK (helper.cnt == 2);
}

/**
 * Przejście do stanu @reset, czyli resetowanie się.
 */
BOOST_AUTO_TEST_CASE (testReset)
{
        // Stany
        Ptr <State> state1 = State::create ("state1");
        state1->addEntryAction (K202Action::create ("$helper.inc ()"));
        state1->addExitAction (K202Action::create ("$helper.inc ()"));

        Ptr <State> state2 = State::create ("state2");
        state2->addEntryAction (K202Action::create ("$helper.inc ()"));
        state2->addExitAction (K202Action::create ("$helper.inc ()"));

        // Przejścia
        Ptr <Transition> transition = Transition::create ("state1", "state2",
                                  K202Condition::create ("$!clicked"));

        Ptr <Transition> transition2 = Transition::create ("state1", "@reset",
                                  K202Condition::create ("$!backClicked"));

        // Helper będzie w kontekście w zakresie "MACHINE"
        HelperAT helper;
        VariantMap mach;
        mach["helper"] = Core::Variant (&helper);

        // Maszyna
        Machine machine (mach);
        machine.addState (state1);
        machine.addState (state2);
        state1->addTransition (transition);
        state1->addTransition (transition2);
        machine.setInitialStateName ("state1");

/*-- odpalamy maszynę ------------------------------------------------------*/

        VariantMap trans;

        // 1.
        machine.run ();
        BOOST_CHECK (machine.getCurrentStateName () == "state1");
        BOOST_CHECK (helper.cnt == 1);

        // 2.
        trans["backClicked"] = Core::Variant (true);
        machine.run (Core::VariantMap (), trans);
        BOOST_CHECK (helper.cnt == 2);
        BOOST_CHECK (machine.getCurrentStateName () == "");

        // 3. Zresetowała się, działa dalej od początku.
        machine.run ();
        BOOST_CHECK (machine.getCurrentStateName () == "state1");
        BOOST_CHECK_EQUAL (helper.cnt, 3);

        // 4.
        trans["clicked"] = Core::Variant (true);
        machine.run (Core::VariantMap (), trans);
        BOOST_CHECK (helper.cnt == 5);
        BOOST_CHECK (machine.getCurrentStateName () == "state2");
}

BOOST_AUTO_TEST_SUITE_END ();
