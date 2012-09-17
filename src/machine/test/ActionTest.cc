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
//#include "core/variant/Variant.h"
//
//BOOST_AUTO_TEST_SUITE (ActionTest);
//
//using namespace Machine;
//using namespace Core;
//
///**
// * Entry actions
// */
//BOOST_AUTO_TEST_CASE (testEntryAction)
//{
//        // Stany
//        Ptr <State> state1 = State::create ("init");
//        state1->addEntryAction (K202Action::create ("$helper.inc()"));
//
//        // Kontekst
//        MachineContext ctx;
//
//        VariantMap mach;
//        VariantMap run;
//        VariantMap transition;
//
//        ctx.setMap (MachineContext::MACHINE, &mach);
//        ctx.setMap (MachineContext::RUN, &run);
//        ctx.setMap (MachineContext::TRANSITION, &transition);
//
//        // Maszyna
//        Machine machine;
//        machine.addState (state1);
//        machine.setInitialStateName ("init");
//
///*-- odpalamy maszynę ------------------------------------------------------*/
//
//        // Helper będzie w kontekście w zakresie "MACHINE"
//        HelperAT helper;
//        mach["helper"] = Core::Variant (&helper);
//
//        BOOST_CHECK (!ctx.get ("helper").isNone ());
//        BOOST_REQUIRE (Reflection::Manager::classForType (ctx.get ("helper").getTypeInfo ()));
//
//        machine.run (&ctx);
//
///*--------------------------------------------------------------------------*/
//
//        BOOST_CHECK (helper.cnt == 1);
//}
//
///**
// * Input actions, a więc i test conditionsów.
// */
//BOOST_AUTO_TEST_CASE (testInputActionK202Condition)
//{
////        try {
//                // Stany
//                Ptr <State> state1 = State::create ("init");
//                state1->addEntryAction (K202Action::create ("$helper.inc ()"));
//
//                state1->addInputAction (InputActions::create (
//                                K202Condition::create ("$!clicked == true"),
//                                K202Action::create ("$helper.set (667)")));
//
//                // Kontekst
//                MachineContext ctx;
//
//                VariantMap mach;
//                VariantMap run;
//                VariantMap transition;
//
//                ctx.setMap (MachineContext::MACHINE, &mach);
//                ctx.setMap (MachineContext::RUN, &run);
//                ctx.setMap (MachineContext::TRANSITION, &transition);
//
//                // Maszyna
//                Machine machine;
//                machine.addState (state1);
//                machine.setInitialStateName ("init");
//
//        /*-- odpalamy maszynę ------------------------------------------------------*/
//
//                // Helper będzie w kontekście w zakresie "MACHINE"
//                HelperAT helper;
//                mach["helper"] = Core::Variant (&helper);
//
//                BOOST_CHECK (!ctx.get ("helper").isNone ());
//
//                machine.run (&ctx);
//                BOOST_CHECK (helper.cnt == 1);
//
//                // Uruchamiamy 2gi raz
//                run["clicked"] = Core::Variant (true);
//                machine.run (&ctx);
//                BOOST_CHECK (helper.cnt == 667);
//
//        /*--------------------------------------------------------------------------*/
//
//
////        }
////        catch (const Core::Exception &e) {
////                std::cerr << e.getMessage() << std::endl;
////        }
////        catch (...) {
////                std::cerr << "Error" << std::endl;
////        }
//
//}
//
///**
// * Test simple condition.
// */
//BOOST_AUTO_TEST_CASE (testInputActionSimpleCondition)
//{
////        try {
//                // Stany
//                Ptr <State> state1 = State::create ("init");
//                state1->addEntryAction (K202Action::create ("$helper.inc ()"));
//
//                state1->addInputAction (InputActions::create (
//                                SimpleCondition::create ("clicked"),
//                                K202Action::create ("$helper.set (991)")));
//
//                // Kontekst
//                MachineContext ctx;
//
//                VariantMap mach;
//                VariantMap run;
//                VariantMap transition;
//
//                ctx.setMap (MachineContext::MACHINE, &mach);
//                ctx.setMap (MachineContext::RUN, &run);
//                ctx.setMap (MachineContext::TRANSITION, &transition);
//
//                // Maszyna
//                Machine machine;
//                machine.addState (state1);
//                machine.setInitialStateName ("init");
//
//        /*-- odpalamy maszynę ------------------------------------------------------*/
//
//                // Helper będzie w kontekście w zakresie "MACHINE"
//                HelperAT helper;
//                mach["helper"] = Core::Variant (&helper);
//
//                BOOST_CHECK (!ctx.get ("helper").isNone ());
//
//                machine.run (&ctx);
//                BOOST_CHECK (helper.cnt == 1);
//
//                // Uruchamiamy 2gi raz
//                run["clicked"] = Core::Variant (112);
//                machine.run (&ctx);
//                BOOST_CHECK (helper.cnt == 991);
//
//        /*--------------------------------------------------------------------------*/
//
//
////        }
////        catch (const Core::Exception &e) {
////                std::cerr << e.getMessage() << std::endl;
////        }
////        catch (...) {
////                std::cerr << "Error" << std::endl;
////        }
//
//}
//
//BOOST_AUTO_TEST_SUITE_END ();
