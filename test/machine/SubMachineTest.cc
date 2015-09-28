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
//#include "SubMachineState.h"
//#include "core/Typedefs.h"
//
//BOOST_AUTO_TEST_SUITE (SubMachineTest);
//
//using namespace Machine;
//using namespace Core;
//
///**
// * Test z akcją dodawaną do tranzycji (w create).
// */
//BOOST_AUTO_TEST_CASE (testSimpleSubMachine)
//{
//        // Helper będzie w kontekście w zakresie "MACHINE"
//        HelperAT helper;
//        VariantMap mach;
//        mach["helper"] = Core::Variant (&helper);
//
//        // Maszyna główna
//        Machine machine (mach);
//        machine.setInitialStateName ("state1");
//
//        // Stany
//        Ptr <State> state1 = State::create ("state1");
//        state1->addEntryAction (K202Action::create ("$helper.inc ()"));
//        state1->addExitAction (K202Action::create ("$helper.inc ()"));
//        machine.addState (state1);
//
//                // Maszyna do sub-state
//                Ptr <Machine> machine2 = Machine::create (mach);
//                machine2->setInitialStateName ("state3");
//
//                // Stany
//                Ptr <State> state3 = State::create ("state3");
//                state3->addEntryAction (K202Action::create ("$helper.inc ()"));
//                state3->addExitAction (K202Action::create ("$helper.inc ()"));
//                machine2->addState (state3);
//
//                Ptr <State> state4 = State::create ("state4");
//                state4->addEntryAction (K202Action::create ("$helper.inc ()"));
//                state4->addExitAction (K202Action::create ("$helper.inc ()"));
//                machine2->addState (state4);
//
//                // Przejścia
//                state3->addTransition (Transition::create ("state3", "state4",
//                                          K202Condition::create ("$!clicked2"),
//                                          K202Action::create ("$helper.inc ()")));
//
//                state4->addTransition (Transition::create ("state4", "@shutDown",
//                                          K202Condition::create ("$!clicked2"),
//                                          K202Action::create ("$helper.inc ()")));
//
//        // Tworzymy SubState i dodajemy do niego maszyne machine2. Ustawiamy I: E:
//        Ptr <SubMachineState> subState = SubMachineState::create ("subState", machine2);
//        subState->addEntryAction (K202Action::create ("$helper.inc ()"));
//        subState->addExitAction (K202Action::create ("$helper.inc ()"));
//        machine.addState (subState);
//
//        Ptr <State> state2 = State::create ("state2");
//        state2->addEntryAction (K202Action::create ("$helper.inc ()"));
//        state2->addExitAction (K202Action::create ("$helper.inc ()"));
//        machine.addState (state2);
//
//        // Przejścia dla głównej.
//        state1->addTransition (Transition::create ("state1", "subState",
//                                  K202Condition::create ("$!clicked"),
//                                  K202Action::create ("$helper.inc ()")));
//
//        subState->addTransition (Transition::create ("subState", "state2",
//                                  K202Condition::create ("$!clicked"),
//                                  K202Action::create ("$helper.inc ()")));
//
//        state2->addTransition (Transition::create ("state2", "@shutDown",
//                                  K202Condition::create ("$!clicked"),
//                                  K202Action::create ("$helper.inc ()")));
//
///*-- odpalamy maszynę ------------------------------------------------------*/
//
//        VariantMap trans;
//
//        // 1. Wejście do stanu początkowego state1.
//        machine.run ();
//        BOOST_CHECK (machine.getCurrentStateName () == "state1");
//        BOOST_CHECK (machine2->getCurrentStateName () == "");
//        BOOST_CHECK (helper.cnt == 1);
//
//        // 2. Wejście do stanu subState
//        trans["clicked"] = Core::Variant (true);
//        machine.run (Core::VariantMap (), trans);
//        BOOST_CHECK (machine.getCurrentStateName () == "subState");
//        BOOST_CHECK (machine2->getCurrentStateName () == "state3");
//        BOOST_CHECK (helper.cnt == 5);
//
//        // 3. Dalej jesteśmy w subState, ale teraz pracuje maszyna subState.
//        trans.clear ();
//        trans["clicked2"] = Core::Variant (true);
//        machine.run (Core::VariantMap (), trans);
//        BOOST_CHECK (machine.getCurrentStateName () == "subState");
//        BOOST_CHECK (machine2->getCurrentStateName () == "state4");
//        BOOST_CHECK (helper.cnt == 8);
//
//        // 4. Teraz już subMachine wyłączy się i trafi w @shutDown, nie będzie już nic robić
//        machine.run (Core::VariantMap (), trans);
//        BOOST_CHECK (machine.getCurrentStateName () == "subState");
//        BOOST_CHECK (machine2->getCurrentStateName () == "");
//        BOOST_CHECK (helper.cnt == 10);
//
//        // 5. Teraz znow główna maszyna przejdzie o jedną hopkę do przodu
//        trans["clicked"] = Core::Variant (true);
//        machine.run (Core::VariantMap (), trans);
//        BOOST_CHECK (machine.getCurrentStateName () == "state2");
//        BOOST_CHECK (machine2->getCurrentStateName () == "");
//        BOOST_CHECK (helper.cnt == 13);
//
//        // 6. i koniec -> @shutDown
//        machine.run (Core::VariantMap (), trans);
//        BOOST_CHECK (machine.getCurrentStateName () == "");
//        BOOST_CHECK (machine2->getCurrentStateName () == "");
//        BOOST_CHECK (helper.cnt == 15);
//}
//
//BOOST_AUTO_TEST_SUITE_END ();
