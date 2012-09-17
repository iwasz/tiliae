///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#include <boost/test/unit_test.hpp>
//#include "core/Typedefs.h"
//#include "State.h"
//#include "Machine.h"
//#include "Helper.h"
//#include "context/Context.h"
//#include "action/K202Action.h"
//#include "condition/Condition.h"
//
//BOOST_AUTO_TEST_SUITE (TransitionTest);
//
//using namespace Machine;
//using namespace Core;
//
///**
// * Test prostego przejścia bez akcji.
// */
//BOOST_AUTO_TEST_CASE (testTransition)
//{
//        // Stany
//        Ptr <State> state1 = State::create ("state1");
//        state1->addEntryAction (K202Action::create ("$helper.inc ()"));
//        state1->addExitAction (K202Action::create ("$helper.set(5)"));
//
//        Ptr <State> state2 = State::create ("state2");
//        state2->addEntryAction (K202Action::create ("$helper.inc ()"));
//        state2->addExitAction (K202Action::create ("$helper.set(8)"));
//
//        // Przejścia
//        Ptr <Transition> transition = Transition::create ("state1", "state2",
//                                  K202Condition::create ("$!clicked == true"));
//
//        // Helper będzie w kontekście w zakresie "MACHINE"
//        HelperAT helper;
//        VariantMap mach;
//        mach["helper"] = Core::Variant (&helper);
//
//        // Maszyna
//        Machine machine (mach);
//        machine.addState (state1);
//        machine.addState (state2);
//        state1->addTransition (transition);
//        machine.setInitialStateName ("state1");
//
///*-- odpalamy maszynę ------------------------------------------------------*/
//
//        VariantMap run;
//
//        // 1.
//        machine.run (run);
//        BOOST_CHECK (helper.cnt == 1);
//
//        // 2.
//        run["clicked"] = Core::Variant (true);
//        machine.run (run);
//
//        BOOST_CHECK (machine.getCurrentStateName () == "state2");
//        BOOST_CHECK (helper.cnt == 6);
//}
//
///**
// * Test przejścia z akcją.
// */
//BOOST_AUTO_TEST_CASE (testTransitionWAction)
//{
//        // Stany
//        Ptr <State> state1 = State::create ("state1");
//        state1->addEntryAction (K202Action::create ("$helper.inc ()"));
//        state1->addExitAction (K202Action::create ("$helper.inc ()"));
//
//        Ptr <State> state2 = State::create ("state2");
//        state2->addEntryAction (K202Action::create ("$helper.inc ()"));
//        state2->addExitAction (K202Action::create ("$helper.inc ()"));
//
//        // Przejścia
//        Ptr <Transition> transition = Transition::create ("state1", "state2",
//                                  K202Condition::create ("$clicked == true"),
//                                  K202Action::create ("$helper.inc ()"));
//
//        // Helper będzie w kontekście w zakresie "MACHINE"
//        HelperAT helper;
//        VariantMap mach;
//        mach["helper"] = Core::Variant (&helper);
//
//        // Maszyna
//        Machine machine (mach);
//        machine.addState (state1);
//        machine.addState (state2);
//        state1->addTransition (transition);
//        machine.setInitialStateName ("state1");
//
///*-- odpalamy maszynę ------------------------------------------------------*/
//
//        VariantMap run;
//        run["clicked"] = Core::Variant (false);
//
//        // 1.
//        machine.run (run);
//        BOOST_CHECK (helper.cnt == 1);
//
//        // 2.
//        run["clicked"] = Core::Variant (true);
//        machine.run (run);
//
//        BOOST_CHECK (machine.getCurrentStateName () == "state2");
//        BOOST_CHECK (helper.cnt == 4);
//}
//
///**
// * Test przejścia z akcją nowego typu (dodawaną do maszyny)
// */
//BOOST_AUTO_TEST_CASE (testTransitionActionInMachine)
//{
//        // Stany
//        Ptr <State> state1 = State::create ("state1");
//        state1->addEntryAction (K202Action::create ("$helper.inc ()"));
//        state1->addExitAction (K202Action::create ("$helper.inc ()"));
//
//        Ptr <State> state2 = State::create ("state2");
//        state2->addEntryAction (K202Action::create ("$helper.inc ()"));
//        state2->addExitAction (K202Action::create ("$helper.inc ()"));
//
//        // Przejścia
//        Ptr <Transition> transition = Transition::create ("state1", "state2",
//                                  K202Condition::create ("$clicked == true"),
//                                  K202Action::create ("$helper.inc ()"));
//
//        Ptr <TransitionAction> traAction = TransitionAction::create ("state1", "state2",
//                                     K202Action::create ("$helper.inc ()"));
//
//        // Helper będzie w kontekście w zakresie "MACHINE"
//        HelperAT helper;
//        VariantMap mach;
//        mach["helper"] = Core::Variant (&helper);
//
//        // Maszyna
//        Machine machine (mach);
//        machine.addState (state1);
//        machine.addState (state2);
//        state1->addTransition (transition);
//        machine.addTransitionAction (traAction);
//        machine.setInitialStateName ("state1");
//
///*-- odpalamy maszynę ------------------------------------------------------*/
//
//        VariantMap run;
//        run["clicked"] = Core::Variant (false);
//
//        // 1.
//        machine.run (run);
//        BOOST_CHECK (helper.cnt == 1);
//
//        // 2.
//        run["clicked"] = Core::Variant (true);
//        machine.run (run);
//
//        BOOST_CHECK (machine.getCurrentStateName () == "state2");
//        BOOST_CHECK (helper.cnt == 5);
//}
//
//BOOST_AUTO_TEST_SUITE_END ();
