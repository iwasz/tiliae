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
#include "../CompactMetaService.h"
#include "Conf.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (CompactXmlTest03);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test011VariantMap)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "011-variant-map.xml"));

        Variant v = cont->getBean ("mojaMapa");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <VariantMap *> (v));

        VariantMap *map = vcast <VariantMap *> (v);

        BOOST_CHECK (vcast <std::string> (map->operator[] ("field0")) == "value0");
        BOOST_CHECK (vcast <std::string> (map->operator[] ("field1")) == "value1");
        BOOST_CHECK (vcast <int> (map->operator[] ("field2")) == 6670);
        BOOST_CHECK (vcast <double> (map->operator[] ("field3")) == 12.34);
        BOOST_CHECK (vcast <char> (map->operator[] ("field4")) == 'g');
        BOOST_CHECK (vcast <bool> (map->operator[] ("field5")) == true);
        BOOST_CHECK (map->operator[] ("field6").isNull ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test012StringList)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "012-string-list.xml"));

        Variant v = cont->getBean ("mojaLista");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <StringVector *> (v));

        StringVector *list = vcast <StringVector *> (v);

        BOOST_REQUIRE_EQUAL (list->size (), 5U);

        BOOST_CHECK_EQUAL (list->operator[] (0), "value01");
        BOOST_CHECK_EQUAL (list->operator[] (1), "value02");
        BOOST_CHECK_EQUAL (list->operator[] (2), "value03");
        BOOST_CHECK_EQUAL (list->operator[] (3), "value04");
        BOOST_CHECK_EQUAL (list->operator[] (4), "value05");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test013VariantList)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "013-variant-list.xml"));

        Variant v = cont->getBean ("mojaLista");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <VariantVector*> (v));

        VariantVector*list = vcast <VariantVector*> (v);

        BOOST_CHECK (list->size () == 8);

        BOOST_CHECK (vcast <std::string> (list->operator[] (0)) == "value01");
        BOOST_CHECK (vcast <Core::String> (list->operator[] (1)) == "value02");
        BOOST_CHECK (vcast <std::string> (list->operator[] (2)) == "value03");
        BOOST_CHECK (vcast <int> (list->operator[] (3)) == 6670);
        BOOST_CHECK (vcast <double> (list->operator[] (4)) == 12.34);
        BOOST_CHECK (vcast <char> (list->operator[] (5)) == 'g');
        BOOST_CHECK (vcast <bool> (list->operator[] (6)) == true);
        BOOST_CHECK (list->operator[] (7).isNull ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test014FirstRefTest)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "014-first-ref-test.xml"));

        Variant v = cont->getBean ("kinkreet");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Foo *> (v));

        Foo *foo = vcast <Foo *> (v);

        BOOST_CHECK (foo->getField0() == "value01");
        BOOST_CHECK (foo->getField1() == "value02");

        BOOST_CHECK (foo->getCity ());
        BOOST_CHECK (foo->getCity ()->getName () == "Tokio");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test015RefTagTest)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "015-ref-tag-test.xml"));

        Variant v = cont->getBean ("kinkreet");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Foo *> (v));

        Foo *foo = vcast <Foo *> (v);

        BOOST_CHECK (foo->getField0() == "value01");
        BOOST_CHECK (foo->getField1() == "value02");

        BOOST_CHECK (foo->getCity ());
        BOOST_CHECK (foo->getCity ()->getName () == "Tokio");
}

BOOST_AUTO_TEST_SUITE_END ();
