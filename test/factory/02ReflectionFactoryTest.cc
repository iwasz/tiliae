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

#include "factory/ReflectionFactory.h"
#include "testHelpers/Telephone.h"
#include "testHelpers/City.h"
#include "core/variant/Variant.h"

BOOST_AUTO_TEST_SUITE (ReflectionFactoryTest02);
using namespace Core;

/**
 * Tworzy obiekt klasy, gdzie konstruktor jest bezparametrowy.
 */
BOOST_AUTO_TEST_CASE (testWOArgument)
{
        Factory::ReflectionFactory fact;

        VariantMap params;
        params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant ("City");
        Variant v = fact.create (params);

        BOOST_REQUIRE (ccast <City *> (v));
        City *city = vcast <City *> (v);
        BOOST_REQUIRE (city);
}

/**
 * Tworzy obiekt klasy, gdzie konstruktor przyjmuje argumenty.
 */
BOOST_AUTO_TEST_CASE (testWithArgument)
{
        Factory::ReflectionFactory fact;

        VariantMap params;
        params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant ("Telephone");
        VariantVector classArgs;
        classArgs.push_back (Core::Variant ("666777"));
        params[Factory::ReflectionFactory::CONSTRUCTOR_ARGS] = Core::Variant (&classArgs);
        Variant v = fact.create (params);

        BOOST_REQUIRE (ccast <Telephone *> (v));
        Telephone *tel = vcast <Telephone *> (v);
        BOOST_REQUIRE (tel);
        BOOST_REQUIRE_EQUAL (tel->getName (), "666777");
}

BOOST_AUTO_TEST_SUITE_END ();
