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
//BOOST_AUTO_TEST_SUITE (ClearTransitionScopeTest);
//
//using namespace Machine;
//using namespace Core;
//
///**
// * Używając placeholdera @back wraca o 2 stany do tyłu, tylk o
// * w przeciwieństwie do testu StackExtensionTest.cc używa zakresu
// * transition, a nie run, więc za kazdym przejściem zmienne się
// * czyszczą. Ten test sprawdza, czy faktycznie.
// */
//BOOST_AUTO_TEST_CASE (testBackWClearTransitionScope)
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
//                                  K202Condition::create ("$!clicked"));
//
//        Ptr <Transition> transition2 = Transition::create ("state2", "state3",
//                                  K202Condition::create ("$!clicked"));
//
//        Ptr <Transition> transition3 = Transition::create ("state3", "@back",
//                                  K202Condition::create ("$!backClicked"));
//
//        Ptr <Transition> transition4 = Transition::create ("state2", "@back",
//                                  K202Condition::create ("$!backClicked"));
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
//        VariantMap trans;
//
//        // 1.
//        machine.run ();
//        BOOST_REQUIRE (machine.getCurrentStateName () == "state1");
//        BOOST_REQUIRE (helper.cnt == 1);
//
//        // 2.
//        trans["clicked"] = Core::Variant (true);
//        machine.run (Core::VariantMap (), trans);
//        BOOST_REQUIRE (machine.getCurrentStateName () == "state2");
//        BOOST_REQUIRE (helper.cnt == 3);
//
//        // 3.
//        machine.run (Core::VariantMap (), trans);
//        BOOST_REQUIRE (machine.getCurrentStateName () == "state3");
//        BOOST_REQUIRE (helper.cnt == 5);
//
//        // 4. I powrót!
//        trans.clear ();
//        trans["backClicked"] = Core::Variant (true);
//        machine.run (Core::VariantMap (), trans);
//        BOOST_REQUIRE (machine.getCurrentStateName () == "state2");
//        BOOST_REQUIRE (helper.cnt == 7);
//
//        // 5. I jesio raz powrót!
//        machine.run (Core::VariantMap (), trans);
//        BOOST_REQUIRE_EQUAL (helper.cnt, 9);
//        BOOST_REQUIRE_EQUAL (machine.getCurrentStateName (), "state1");
//}
//
//BOOST_AUTO_TEST_SUITE_END ();
