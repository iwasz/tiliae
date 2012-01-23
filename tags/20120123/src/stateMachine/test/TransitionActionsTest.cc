/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include "../../core/Typedefs.h"
#include "State.h"
#include "Machine.h"
#include "Helper.h"
#include "../context/Context.h"
#include "../action/K202Action.h"
#include "../condition/Condition.h"
#include "extension/StackStateExtension.h"

BOOST_AUTO_TEST_SUITE (TransitionActionsTest);
 
using namespace StateMachine;
using namespace Core;

/**
 * Test z akcją dodawaną do tranzycji (w create).
 */
BOOST_AUTO_TEST_CASE (testTransitionAction1)
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
                                  K202Condition::create ("$!clicked"),
                                  K202Action::create ("$helper.inc ()"));

        // Helper będzie w kontekście w zakresie "MACHINE"
        HelperAT helper;
        VariantMap mach;
        mach["helper"] = Core::Variant (&helper);

        // Maszyna
        Machine machine (mach);
        machine.addState (state1);
        machine.addState (state2);
        state1->addTransition (transition);
        machine.setInitialStateName ("state1");

        MachineExtensionList extList;
        Ptr <StackStateExtension> ext (new StackStateExtension);
        extList.push_back (ext);
        machine.setExtensionList (extList);

/*-- odpalamy maszynę ------------------------------------------------------*/

        VariantMap trans;

        // 1.
        machine.run ();
        BOOST_CHECK (machine.getCurrentStateName () == "state1");
        BOOST_CHECK (helper.cnt == 1);

        // 2.
        trans["clicked"] = Core::Variant (true);
        machine.run (Core::VariantMap (), trans);
        BOOST_CHECK (machine.getCurrentStateName () == "state2");
        BOOST_CHECK (helper.cnt == 4);
}

/**
 * Test z nowym rodzajem transition actions.
 */
BOOST_AUTO_TEST_CASE (testTransitionAction2)
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

        Ptr <TransitionAction> traa = TransitionAction::create ("state1", "state2",
                                                K202Action::create ("$helper.inc ()"));

        // Helper będzie w kontekście w zakresie "MACHINE"
        HelperAT helper;
        VariantMap mach;
        mach["helper"] = Core::Variant (&helper);

        // Maszyna
        Machine machine (mach);
        machine.addState (state1);
        machine.addState (state2);
        state1->addTransition (transition);
        machine.addTransitionAction (traa);
        machine.setInitialStateName ("state1");

        MachineExtensionList extList;
        Ptr <StackStateExtension> ext (new StackStateExtension);
        extList.push_back (ext);
        machine.setExtensionList (extList);

/*-- odpalamy maszynę ------------------------------------------------------*/

        VariantMap trans;

        // 1.
        machine.run ();
        BOOST_CHECK (machine.getCurrentStateName () == "state1");
        BOOST_CHECK (helper.cnt == 1);

        // 2.
        trans["clicked"] = Core::Variant (true);
        machine.run (Core::VariantMap (), trans);
        BOOST_CHECK (machine.getCurrentStateName () == "state2");
        BOOST_CHECK (helper.cnt == 4);
}

/**
 * Test z nowym rodzajem transition actions + do tego po
 * placeholdereze.
 */
BOOST_AUTO_TEST_CASE (testTransitionAction3)
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

        Ptr <Transition> transition2 = Transition::create ("state2", "@back",
                                  K202Condition::create ("$!clicked"));

        Ptr <TransitionAction> traa = TransitionAction::create ("state1", "state2",
                                                K202Action::create ("$helper.inc ()"));

        Ptr <TransitionAction> traa2 = TransitionAction::create ("state2", "@back",
                                                K202Action::create ("$helper.inc ()"));

        // Helper będzie w kontekście w zakresie "MACHINE"
        HelperAT helper;
        VariantMap mach;
        mach["helper"] = Core::Variant (&helper);

        // Maszyna
        Machine machine (mach);
        machine.addState (state1);
        machine.addState (state2);
        state1->addTransition (transition);
        state2->addTransition (transition2);
        machine.addTransitionAction (traa);
        machine.addTransitionAction (traa2);
        machine.setInitialStateName ("state1");

        MachineExtensionList extList;
        Ptr <StackStateExtension> ext (new StackStateExtension);
        extList.push_back (ext);
        machine.setExtensionList (extList);

/*-- odpalamy maszynę ------------------------------------------------------*/

        VariantMap trans;

        // 1.
        machine.run ();
        BOOST_CHECK (machine.getCurrentStateName () == "state1");
        BOOST_CHECK (helper.cnt == 1);

        // 2.
        trans["clicked"] = Core::Variant (true);
        machine.run (Core::VariantMap (), trans);
        BOOST_CHECK (machine.getCurrentStateName () == "state2");
        BOOST_CHECK (helper.cnt == 4);

        // 3. Tu będzie powrót.
        trans["clicked"] = Core::Variant (true);
        machine.run (Core::VariantMap (), trans);
        BOOST_CHECK (machine.getCurrentStateName () == "state1");
        BOOST_CHECK (helper.cnt == 7);
}

BOOST_AUTO_TEST_SUITE_END ();
