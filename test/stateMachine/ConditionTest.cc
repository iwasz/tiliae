/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include "context/Context.h"
#include "State.h"
#include "Machine.h"
#include "action/K202Action.h"
#include "Helper.h"
#include "core/Pointer.h"
#include "context/MachineContext.h"
#include "core/Typedefs.h"

BOOST_AUTO_TEST_SUITE (ConditionTest);

using namespace StateMachine;
using namespace Core;

/**
 * Ma się skompilować po prostu.
 */
BOOST_AUTO_TEST_CASE (testEntryAction)
{
        // Stany
        Ptr <State> state1 = State::create ("init");
        state1->addEntryAction (K202Action::create ("$helper.inc ()"));

        // Kontekst
        MachineContext ctx;

        VariantMap mach;
        VariantMap run;
        VariantMap transition;

        ctx.setMap (MachineContext::MACHINE, &mach);
        ctx.setMap (MachineContext::RUN, &run);
        ctx.setMap (MachineContext::TRANSITION, &transition);

        // Maszyna
        Machine machine;
        machine.addState (state1);
        machine.setInitialStateName ("init");

/*-- odpalamy maszynę ------------------------------------------------------*/

        // Helper będzie w kontekście w zakresie "MACHINE"
        HelperAT helper;
        mach["helper"] = Core::Variant (&helper);

        BOOST_CHECK (!ctx.get ("helper").isNone ());

        machine.run (&ctx);

/*--------------------------------------------------------------------------*/

        BOOST_CHECK (helper.cnt == 1);
}

BOOST_AUTO_TEST_SUITE_END ();
