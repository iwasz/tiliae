/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <K202.h>
#include "context/Context.h"
#include "core/Typedefs.h"

BOOST_AUTO_TEST_SUITE (ContextTest);
 
using namespace StateMachine;
using namespace Core;

/**
 * Ma się skompilować po prostu.
 */
BOOST_AUTO_TEST_CASE (testInstantiate)
{
        MachineContext ctx;
        BOOST_CHECK (true);
}

/**
 * Ustawianie map zakresów widoczności.
 */
BOOST_AUTO_TEST_CASE (testSetMapGetMap)
{
        MachineContext ctx;

        VariantMap machine;
        VariantMap run;
        VariantMap transition;

        ctx.setMap (MachineContext::MACHINE, &machine);
        ctx.setMap (MachineContext::RUN, &run);
        ctx.setMap (MachineContext::TRANSITION, &transition);

        BOOST_CHECK (ctx.getMap (MachineContext::MACHINE));
        BOOST_CHECK (ctx.getMap (MachineContext::RUN));
        BOOST_CHECK (ctx.getMap (MachineContext::TRANSITION));
}

/**
 * Pobieranie obiektów.
 */
BOOST_AUTO_TEST_CASE (testGet)
{
        MachineContext ctx;

        VariantMap machine;
        VariantMap run;
        VariantMap transition;

        ctx.setMap (MachineContext::MACHINE, &machine);
        ctx.setMap (MachineContext::RUN, &run);
        ctx.setMap (MachineContext::TRANSITION, &transition);

/*--------------------------------------------------------------------------*/

        machine["mach1"] = Core::Variant (556);
        run["run1"] = Core::Variant (667);
        transition["tran1"] = Core::Variant (778);

        BOOST_CHECK (vcast <int> (ctx.get ("mach1")) == 556);
        BOOST_CHECK (vcast <int> (ctx.get ("run1")) == 667);
        BOOST_CHECK (vcast <int> (ctx.get ("tran1")) == 778);
}

/**
 * Ustawianie obiektów.
 */
BOOST_AUTO_TEST_CASE (testSet)
{
        MachineContext ctx;

        VariantMap machine;
        VariantMap run;
        VariantMap transition;

        ctx.setMap (MachineContext::MACHINE, &machine);
        ctx.setMap (MachineContext::RUN, &run);
        ctx.setMap (MachineContext::TRANSITION, &transition);

/*--------------------------------------------------------------------------*/

        ctx.set ("tran2", Core::Variant (889));

        BOOST_CHECK_EQUAL (vcast <int> (ctx.get ("tran2")), 889);
        BOOST_CHECK_EQUAL (vcast <int> (transition["tran2"]), 889);
        BOOST_CHECK (machine.empty ());
        BOOST_CHECK (run.empty ());
}

/**
 * K202 i kontekst
 */
BOOST_AUTO_TEST_CASE (testContextK202)
{
        MachineContext ctx;

        VariantMap machine;
        VariantMap run;
        VariantMap transition;

        ctx.setMap (MachineContext::MACHINE, &machine);
        ctx.setMap (MachineContext::RUN, &run);
        ctx.setMap (MachineContext::TRANSITION, &transition);

/*--------------------------------------------------------------------------*/

        machine["mach1"] = Core::Variant (556);
        run["run1"] = Core::Variant (Core::String ("aaa"));
        transition["tran1"] = Core::Variant (778.7);

        Core::Variant vCtx = Core::Variant (&ctx);
        Core::Variant ret;

        ret = k202::K202::instance ()->run ("$TRANSITION", vCtx);
        BOOST_CHECK (ccast <Core::VariantMap *> (ret));
        BOOST_CHECK (vcast <Core::VariantMap *> (ret) == &transition);

        ret = k202::K202::instance ()->run ("$RUN", vCtx);
        BOOST_CHECK (ccast <Core::VariantMap *> (ret));
        BOOST_CHECK (vcast <Core::VariantMap *> (ret) == &run);

        ret = k202::K202::instance ()->run ("$MACHINE", vCtx);
        BOOST_CHECK (ccast <Core::VariantMap *> (ret));
        BOOST_CHECK (vcast <Core::VariantMap *> (ret) == &machine);

        ret = k202::K202::instance ()->run ("$MACHINE.mach1", vCtx);
        BOOST_CHECK (ccast <int> (ret));
        BOOST_CHECK (vcast <int> (ret) == 556);

        ret = k202::K202::instance ()->run ("$RUN.run1", vCtx);
        BOOST_CHECK (ccast <Core::String> (ret));
        BOOST_CHECK (vcast <Core::String> (ret) == "aaa");

        ret = k202::K202::instance ()->run ("$TRANSITION.tran1", vCtx);
        BOOST_CHECK (ccast <double> (ret));
        BOOST_CHECK (vcast <double> (ret) == 778.7);
}

BOOST_AUTO_TEST_SUITE_END ();
