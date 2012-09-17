///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#include <boost/test/unit_test.hpp>
//#include "State.h"
//#include "Machine.h"
//#include "Helper.h"
//#include "context/Context.h"
//#include "action/K202Action.h"
//#include "condition/Condition.h"
//#include "extension/StackStateExtension.h"
//#include "core/Typedefs.h"
//
//BOOST_AUTO_TEST_SUITE (StackExtensionTest);
//
//using namespace Machine;
//using namespace Core;
//
///**
// * Testuje placeholder @back
// */
//BOOST_AUTO_TEST_CASE (testBack)
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
//        // Przejście do metastanu @back
//        Ptr <Transition> transition2 = Transition::create ("state2", "@back",
//                                  K202Condition::create ("$!kupa"));
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
//        state2->addTransition (transition2);
//        machine.setInitialStateName ("state1");
//
//        MachineExtensionList extList;
//        Ptr <StackStateExtension> ext (new StackStateExtension);
//        extList.push_back (ext);
//        machine.setExtensionList (extList);
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
//
//        // 3.
//        run.clear ();
//        run["kupa"] = Core::Variant (true);
//        machine.run (run);
//
//        BOOST_CHECK (machine.getCurrentStateName () == "state1");
//        BOOST_CHECK (helper.cnt == 9);
//}
//
///**
// * Testuje placeholder @back, ale wraca o 2 stany, a nie o 1 jak w poprzednim teście.
// */
//BOOST_AUTO_TEST_CASE (testBack2)
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
//        Ptr <State> state3 = State::create ("state3");
//        state3->addEntryAction (K202Action::create ("$helper.inc ()"));
//        state3->addExitAction (K202Action::create ("$helper.inc ()"));
//
//        // Przejścia
//        Ptr <Transition> transition = Transition::create ("state1", "state2",
//                                  K202Condition::create ("$!siuskens"));
//
//        Ptr <Transition> transition2 = Transition::create ("state2", "state3",
//                                  K202Condition::create ("$!kupkens"));
//
//        Ptr <Transition> transition3 = Transition::create ("state3", "@back",
//                                  K202Condition::create ("$!dupkens"));
//
//        Ptr <Transition> transition4 = Transition::create ("state2", "@back",
//                                  K202Condition::create ("$!fiutkens"));
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
//        machine.addState (state3);
//        state1->addTransition (transition);
//        state2->addTransition (transition2);
//        state3->addTransition (transition3);
//        state2->addTransition (transition4);
//        machine.setInitialStateName ("state1");
//
//        MachineExtensionList extList;
//        Ptr <StackStateExtension> ext (new StackStateExtension);
//        extList.push_back (ext);
//        machine.setExtensionList (extList);
//
///*-- odpalamy maszynę ------------------------------------------------------*/
//
//        VariantMap run;
//
//        // 1.
//        machine.run (run);
//        BOOST_CHECK (machine.getCurrentStateName () == "state1");
//        BOOST_CHECK (helper.cnt == 1);
//
//        // 2.
//        run.clear ();
//        run["siuskens"] = Core::Variant (true);
//        machine.run (run);
//
//        BOOST_CHECK (machine.getCurrentStateName () == "state2");
//        BOOST_CHECK (helper.cnt == 3);
//
//        // 3.
//        run.clear ();
//        run["kupkens"] = Core::Variant (true);
//        machine.run (run);
//
//        BOOST_CHECK (machine.getCurrentStateName () == "state3");
//        BOOST_CHECK (helper.cnt == 5);
//
//        // 4. I powrót!
//        run.clear ();
//        run["dupkens"] = Core::Variant (true);
//        machine.run (run);
//
//        BOOST_CHECK (machine.getCurrentStateName () == "state2");
//        BOOST_CHECK (helper.cnt == 7);
//
//        // 5. I jesio raz powrót!
//        run.clear ();
//        run["fiutkens"] = Core::Variant (true);
//        machine.run (run);
//
//        BOOST_CHECK (machine.getCurrentStateName () == "state1");
//        BOOST_CHECK (helper.cnt == 9);
//}
//
//BOOST_AUTO_TEST_SUITE_END ();
