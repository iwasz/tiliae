/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "testHelpers/TestHelpers.h"
#include "factory/ScalarFactory.h"
#include "testHelpers/Telephone.h"
#include "testHelpers/City.h"
#include "core/variant/Variant.h"
#include "factory/ReflectionFactory.h"
#include "factory/ChainFactory.h"
#include "factory/LazyFactory.h"
#include <boost/make_shared.hpp>
#include "testHelpers/Bar.h"

BOOST_AUTO_TEST_SUITE (ChainFactoryTest04);
using namespace Core;
using namespace Factory;

/**
 * Tworzy obiekt klasy, gdzie konstruktor jest bezparametrowy.
 */
BOOST_AUTO_TEST_CASE (testAdvanced)
{
        ChainFactory fact (true);

        // Pierwsza
        fact.addFactory (new ScalarFactory);
        // Druga
        fact.addFactory (new ReflectionFactory);

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
        BOOST_REQUIRE (ccast <Telephone *> (v));
        Telephone *b = vcast <Telephone *> (v);
        BOOST_REQUIRE_EQUAL (b->getName(), "6006424881");
        delete b;
}

BOOST_AUTO_TEST_SUITE_END ();
