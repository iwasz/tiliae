/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <Pointer.h>
#include <TestHelpers.h>

#include "ContainerFactory.h"
#include "metaStructure/model/MetaStructure.h"
#include "common/testHelpers/ContainerTestFactory.h"
#include "Conf.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerXmlTest07);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test031MapInCarg)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "031-map-in-carg.xml");

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Bar *> (v));

        Bar *foo = vcast <Bar *> (v);

        BOOST_CHECK (foo->getField0() == "value01");
        BOOST_CHECK (foo->getField1() == "value02");

        BOOST_CHECK (!foo->getButter ().isNone ());
        BOOST_CHECK (ccast <StringMap> (foo->getButter ()));

        StringMap *map = vcast <StringMap *> (foo->getButter ());

        BOOST_CHECK (map->size () == 3);
        BOOST_CHECK (map->operator[] ("k1") == "Tokio");
        BOOST_CHECK (map->operator[] ("k2") == "Warsaw");
        BOOST_CHECK (map->operator[] ("k3") == "Piaseczno");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test032ListInCarg)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "032-list-in-carg.xml");

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Bar *> (v));

        Bar *foo = vcast <Bar *> (v);

        BOOST_CHECK (foo->getField0() == "value01");
        BOOST_CHECK (foo->getField1() == "value02");

        BOOST_CHECK (!foo->getButter ().isNone ());
        BOOST_CHECK (ccast <StringVector *> (foo->getButter ()));

        StringVector *list = vcast <StringVector *> (foo->getButter ());

        BOOST_CHECK (list->size () == 3);
        BOOST_CHECK (list->operator[] (0) == "Tokio");
        BOOST_CHECK (list->operator[] (1) == "Warsaw");
        BOOST_CHECK (list->operator[] (2) == "Kraków");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test033BeanInList)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "033-bean-in-list.xml");

        Variant v = cont->getBean ("myList");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <VariantVector *> (v));

        VariantVector *list = vcast <VariantVector *> (v);

        BOOST_CHECK (list->size () == 3);

        BOOST_CHECK (vcast <std::string> (list->operator[] (0)) == "value01");
        BOOST_CHECK (vcast <std::string> (list->operator[] (1)) == "value02");

        BOOST_CHECK (ccast <City *> (list->operator[] (2)));
        BOOST_CHECK (vcast <City *> (list->operator[] (2))->getName () == "Tokio");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test034MapInList)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "034-map-in-list.xml");

        Variant v = cont->getBean ("myList");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <VariantVector *> (v));

        VariantVector *list = vcast <VariantVector *> (v);

        BOOST_CHECK_EQUAL (list->size (), 3U);

        BOOST_CHECK_EQUAL (vcast <std::string> (list->operator[] (0)), "value01");
        BOOST_CHECK_EQUAL (vcast <std::string> (list->operator[] (1)), "value02");

        BOOST_CHECK (ccast <StringMap *> (list->operator[] (2)));
        StringMap *map = vcast <StringMap *> (list->operator[] (2));

        BOOST_CHECK_EQUAL (map->size (), 3U);
        BOOST_CHECK_EQUAL (map->operator[] ("k1"), "Tokio");
        BOOST_CHECK_EQUAL (map->operator[] ("k2"), "Warsaw");
        BOOST_CHECK_EQUAL (map->operator[] ("k3"), "Piaseczno");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test035ListInList)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "035-list-in-list.xml");

        Variant v = cont->getBean ("myList");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <VariantVector *> (v));

        VariantVector *list = vcast <VariantVector *> (v);

        BOOST_CHECK (list->size () == 3);

        BOOST_CHECK (vcast <std::string> (list->operator[] (0)) == "value01");
        BOOST_CHECK (vcast <std::string> (list->operator[] (1)) == "value02");

        BOOST_CHECK (ccast <StringVector *> (list->operator[] (2)));
        StringVector*list2 = vcast <StringVector*> (list->operator[] (2));

        BOOST_CHECK (list2->size () == 3);
        BOOST_CHECK (list2->operator[] (0) == "Tokio");
        BOOST_CHECK (list2->operator[] (1) == "Warsaw");
        BOOST_CHECK (list2->operator[] (2) == "Kraków");
}

BOOST_AUTO_TEST_SUITE_END ();
