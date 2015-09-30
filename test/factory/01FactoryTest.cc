/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#define BOOST_TEST_MODULE FactoryTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
#include <iostream>
#include <algorithm>
#include "factory/testHelpers/MegaTonFactory.h"
#include "core/variant/Variant.h"
#include "factory/testHelpers/MegaTon.h"
#include "core/variant/Cast.h"
#include "factory/SingletonFactory.h"
#include "core/Typedefs.h"
#include "core/Pointer.h"
#include "factory/ReflectionFactory.h"
#include "factory/ProxyFactory.h"
#include "testHelpers/City.h"
#include "factory/testHelpers/SillyFactory.h"
#include "testHelpers/Reflection_output.cc.h"

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (FactoryTest01);
using namespace Core;
using namespace Factory;

/**
 *
 */
BOOST_AUTO_TEST_CASE (testMegaTonFactory)
{
        MegaTonFactory factory;

        Variant v = factory.create ();

        BOOST_REQUIRE (!v.isNone ());
        BOOST_REQUIRE (ccast <MegaTon *> (v));

        MegaTon *m1 = vcast <MegaTon *> (v);

        Variant v2 = factory.create ();

        BOOST_REQUIRE (!v2.isNone ());
        BOOST_REQUIRE (ccast <MegaTon *> (v2));

        MegaTon *m2 = vcast <MegaTon *> (v2);

        BOOST_REQUIRE (m2 != m1);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testMegaTonSingletinFactory)
{
        SingletonFactory sfct (new MegaTonFactory, true);

        Variant v = sfct.create ();

        BOOST_REQUIRE (!v.isNone ());
        BOOST_REQUIRE (ccast <MegaTon *> (v));

        MegaTon *m1 = vcast <MegaTon *> (v);

        Variant v2 = sfct.create ();

        BOOST_REQUIRE (!v2.isNone ());
        BOOST_REQUIRE (ccast <MegaTon *> (v2));

        MegaTon *m2 = vcast <MegaTon *> (v2);

        BOOST_REQUIRE_EQUAL (m2, m1);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testSillyFactory)
{
        SillyFactory factory;
        factory.setOriginal (Core::Variant (667));

        Variant v = factory.create ();

        BOOST_REQUIRE (!v.isNone ());
        BOOST_REQUIRE (!ccast <MegaTon *> (v));
        BOOST_REQUIRE (ccast <int> (v));
        BOOST_REQUIRE (ccast <int *> (v));
        BOOST_REQUIRE (v.isValue ());

        Variant v2 = factory.create ();

        int *ps1 = vcast <int *> (v);
        int *ps2 = vcast <int *> (v2);

        BOOST_REQUIRE (ps1 != ps2);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testProxyFactory)
{
        VariantMap factoryParams;
        factoryParams[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant ("City");

        ProxyFactory cities (new ReflectionFactory, factoryParams, true);

        Variant result = cities.create ();
        BOOST_REQUIRE (ccast <City *> (result));
}

BOOST_AUTO_TEST_SUITE_END ();
