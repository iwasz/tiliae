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

BOOST_AUTO_TEST_SUITE (ScalarFactoryTest03);
using namespace Core;
using namespace Factory;

/**
 * Tworzy obiekt klasy, gdzie konstruktor jest bezparametrowy.
 */
BOOST_AUTO_TEST_CASE (testWOArgument)
{
        ScalarFactory fact;

        VariantMap params;
        params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant ("int");
        Variant v = fact.create (params);
        BOOST_REQUIRE_EQUAL (vcast <int> (v), 0);

        params.clear ();
        params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant ("double");
        v = fact.create (params);
        BOOST_REQUIRE_EQUAL (vcast <double> (v), 0.0);

        params.clear ();
        params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant ("String");
        v = fact.create (params);
        BOOST_REQUIRE_EQUAL (vcast <Core::String> (v), "");

        params.clear ();
        params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant ("string");
        v = fact.create (params);
        BOOST_REQUIRE_EQUAL (vcast <std::string> (v), "");
}

/**
 * Tworzy skalar, gdzie konstruktor przyjmuje argumenty.
 */
BOOST_AUTO_TEST_CASE (testWithArgument)
{
        ScalarFactory fact;

        VariantMap params;
        params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant ("int");
        VariantVector classArgs;
        classArgs.push_back (Core::Variant ("123"));
        params[Factory::ReflectionFactory::CONSTRUCTOR_ARGS] = Core::Variant (&classArgs);
        Variant v = fact.create (params);
        BOOST_REQUIRE_EQUAL (vcast <int> (v), 123);

        classArgs.clear ();
        classArgs.push_back (Core::Variant (Core::String ("123")));
        v = fact.create (params);
        BOOST_REQUIRE_EQUAL (vcast <int> (v), 123);

        params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant ("String");
        classArgs.clear ();
        classArgs.push_back (Core::Variant ("123"));
        v = fact.create (params);
        BOOST_REQUIRE_EQUAL (vcast <Core::String> (v), "123");
}

BOOST_AUTO_TEST_SUITE_END ();
