/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <TestHelpers.h>

#include "ScalarFactory.h"
#include "../../testHelpers/Telephone.h"
#include "../../testHelpers/City.h"
#include "../../core/variant/Variant.h"
#include "../ReflectionFactory.h"
#include "../ChainFactory.h"
#include <boost/make_shared.hpp>
#include "../../testHelpers/Bar.h"

BOOST_AUTO_TEST_SUITE (ChainFactoryTest04);
using namespace Core;
using namespace Factory;

/**
 * Tworzy obiekt klasy, gdzie konstruktor jest bezparametrowy.
 */
BOOST_AUTO_TEST_CASE (testAdvanced)
{
        Ptr <ScalarFactory> factS = boost::make_shared <ScalarFactory> ();
        Ptr <ReflectionFactory> factR = boost::make_shared <ReflectionFactory> ();
        ChainFactory fact;

        // Pierwsza
        fact.addFactory (factS);
        // Druga
        fact.addFactory (factR);

        // 1. Stwórz skalar - powinna zadziałać ScalarFactory.
        VariantMap params;
        params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant ("int");
        VariantVector classArgs;
        classArgs.push_back (Core::Variant ("123"));
        params[Factory::ReflectionFactory::CONSTRUCTOR_ARGS] = Core::Variant (&classArgs);
        Variant v = fact.create (params);
        BOOST_REQUIRE_EQUAL (vcast <int> (v), 123);

        // 2. Stwórz jakiś skomplikowany obiekt:
        params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant ("Telephone");
        classArgs.clear ();
        classArgs.push_back (Core::Variant ("6006424881"));
        v = fact.create (params);
        BOOST_REQUIRE (ccast <Ptr <Telephone> > (v));
        Ptr <Telephone> b = vcast <Ptr <Telephone> > (v);
        BOOST_REQUIRE_EQUAL (b->getName(), "6006424881");
}

BOOST_AUTO_TEST_SUITE_END ();
