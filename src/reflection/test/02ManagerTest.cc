/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "Reflection.h"
#include "Core.h"
#include "../../testHelpers/Address.h"
#include "../../testHelpers/City.h"
#include "../../testHelpers/Country.h"

BOOST_AUTO_TEST_SUITE (ManagerTest);

using namespace boost;
using namespace Core;
using namespace Reflection;

/**
 * Probuje podbrac metode o zadanej nazwie z obiektu i wywołać ją.
 */
BOOST_AUTO_TEST_CASE (testGetClassForName)
{
        Class *cls = Manager::classForName ("Address");
        BOOST_REQUIRE (cls);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testGetClassForTypeInfo)
{
        const std::type_info *ty = &typeid (Address);
        Class *cls = Manager::classForType (*ty);
        BOOST_REQUIRE (cls);

        const std::type_info *ty1 = &typeid (Address &);
        cls = Manager::classForType (*ty1);
        BOOST_REQUIRE (cls);

        Address address;
        const std::type_info *ty3 = &typeid (address);
        cls = Reflection::Manager::classForType (*ty3);
        BOOST_REQUIRE (cls);

        Address *pa = &address;
        Variant v = Core::Variant (*pa);
        const std::type_info &ty4 = v.getTypeInfo ();
        cls = Reflection::Manager::classForType (ty4);
        BOOST_REQUIRE (cls);

        const Address *pa1 = &address;
        v = Core::Variant (pa1);
        cls = Reflection::Manager::classForType (v.getTypeInfo ());
        BOOST_REQUIRE (cls);
}

BOOST_AUTO_TEST_CASE (testClassProperClass)
{
        Class *cls = Manager::classForName ("Address");
        BOOST_REQUIRE (cls);
        BOOST_REQUIRE_EQUAL (cls->getName (), "Address");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testContainsCommand)
{
//        BOOST_REQUIRE (Manager::containsCommand ("Address"));
//        BOOST_REQUIRE (!Manager::containsCommand ("Testklasa"));
//
//        Manager::add (new ClassCommand (), "NaszaKlasa");
//        BOOST_REQUIRE (Manager::containsCommand ("NaszaKlasa"));

//        std::cerr << "OK ManagerTest::testContainsCommand" << std::endl;
}

BOOST_AUTO_TEST_CASE (testToString)
{
//	std::cerr << Manager::instance().toString() << std::endl;
}

BOOST_AUTO_TEST_SUITE_END ();
