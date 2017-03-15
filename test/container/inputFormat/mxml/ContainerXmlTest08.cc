/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>

#include <iostream>
#include "core/Pointer.h"
#include "testHelpers/TestHelpers.h"

#include "container/ContainerFactory.h"
#include "container/metaStructure/model/MetaStructure.h"
#include "container/testHelpers/ContainerTestFactory.h"
#include "Conf.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerXmlTest08);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test036BeanInMap)
{
        BeanFactoryContainer *cont = ContainerTestFactory::getContainer (PATH + "036-bean-in-map.xml");

        Variant v = cont->getBean ("myMap");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <VariantMap *> (v));

        VariantMap *map = vcast <VariantMap *> (v);

        BOOST_CHECK (map->size () == 3);

        BOOST_CHECK (vcast <std::string> (map->operator[] ("k1")) == "Tokio");
        BOOST_CHECK (vcast <std::string> (map->operator[] ("k2")) == "Warsaw");

        BOOST_CHECK (ccast <City *> (map->operator[] ("k3")));
        BOOST_CHECK (vcast <City *> (map->operator[] ("k3"))->getName () == "Pcim");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test037MapInMap)
{
        BeanFactoryContainer *cont = ContainerTestFactory::getContainer (PATH + "037-map-in-map.xml");

        Variant v = cont->getBean ("myMap");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <VariantMap *> (v));

        VariantMap *map = vcast <VariantMap *> (v);

        BOOST_CHECK (map->size () == 3);

        BOOST_CHECK (vcast <std::string> (map->operator[] ("k1")) == "Tokio");
        BOOST_CHECK (vcast <std::string> (map->operator[] ("k2")) == "Warsaw");

        BOOST_CHECK (ccast <StringMap *> (map->operator[] ("k3")));
        StringMap *map2 = vcast <StringMap *> (map->operator[] ("k3"));

        BOOST_CHECK (map2->size () == 3);
        BOOST_CHECK (map2->operator[] ("k1") == "Tokio");
        BOOST_CHECK (map2->operator[] ("k2") == "Warsaw");
        BOOST_CHECK (map2->operator[] ("k3") == "Piaseczno");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test038ListInMap)
{
        BeanFactoryContainer *cont = ContainerTestFactory::getContainer (PATH + "038-list-in-map.xml");

        Variant v = cont->getBean ("myMap");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <VariantMap *> (v));

        VariantMap *map = vcast <VariantMap *> (v);

        BOOST_CHECK (map->size () == 3);

        BOOST_CHECK (vcast <std::string> (map->operator[] ("k1")) == "Tokio");
        BOOST_CHECK (vcast <std::string> (map->operator[] ("k2")) == "Warsaw");

        BOOST_CHECK (ccast <StringVector *> (map->operator[] ("k3")));
        StringVector *list2 = vcast <StringVector *> (map->operator[] ("k3"));

        BOOST_CHECK (list2->size () == 3);
        BOOST_CHECK (list2->operator[] (0) == "Tokio");
        BOOST_CHECK (list2->operator[] (1) == "Warsaw");
        BOOST_CHECK (list2->operator[] (2) == "Kraków");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test039ComplicatedBeans)
{
        BeanFactoryContainer *cont = ContainerTestFactory::getContainer (PATH + "039-complicated-beans.xml");

        Variant v = cont->getBean ("myMap");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <VariantMap *> (v));
        VariantMap *map = vcast <VariantMap *> (v);
        BOOST_CHECK (map->size () == 3);

        v = cont->getBean ("myList");
        BOOST_REQUIRE (!v.isNone ());
        BOOST_REQUIRE (ccast <VariantList *> (v));
        VariantList *list = vcast <VariantList *> (v);
        BOOST_REQUIRE_EQUAL (list->size (), 3U);

        v = cont->getBean ("myBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Bar *> (v));
        Bar *bar = vcast <Bar *>(v);
        BOOST_CHECK (bar->getCity());
        BOOST_CHECK (!bar->getButter ().isNone ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test040MultipleNesting)
{
        BeanFactoryContainer *cont = ContainerTestFactory::getContainer (PATH + "040-multiple-nesting.xml");

        Variant v = cont->getBean ("myBean");
        BOOST_REQUIRE (!v.isNone ());
        Bar *bar = vcast <Bar *>(v);
        BOOST_CHECK (bar->getCity());
        BOOST_CHECK (!bar->getButter ().isNone ());

        BOOST_CHECK (ccast <VariantMap *> (bar->getButter ()));
        VariantMap *vm = vcast <VariantMap *> (bar->getButter ());
        BOOST_REQUIRE_EQUAL (vm->size (), 3U);
        BOOST_CHECK (ccast <City *> (vm->operator[] ("k1")));
        City *cit = vcast <City *> (vm->operator[] ("k1"));
        BOOST_CHECK (cit->getName () == "Pcim");

        BOOST_CHECK (ccast <StringMap *> (vm->operator[] ("k2")));
        StringMap *map = vcast <StringMap *> (vm->operator[] ("k2"));
        BOOST_REQUIRE_EQUAL (map->size (), 3U);
        BOOST_CHECK (map->operator[] ("k1") == "Tokio");
        BOOST_CHECK (map->operator[] ("k2") == "Warsaw");
        BOOST_CHECK (map->operator[] ("k3") == "Piaseczno");

        BOOST_CHECK (ccast <VariantVector *> (vm->operator[] ("k3")));
        VariantVector *list = vcast <VariantVector *> (vm->operator[] ("k3"));
        BOOST_REQUIRE_EQUAL (list->size (), 3U);
        BOOST_CHECK (ccast <City *> (list->operator[] (0)));
        BOOST_CHECK (ccast <StringMap *> (list->operator[] (1)));
        BOOST_CHECK (ccast <StringList *> (list->operator[] (2)));
}

BOOST_AUTO_TEST_SUITE_END ();
