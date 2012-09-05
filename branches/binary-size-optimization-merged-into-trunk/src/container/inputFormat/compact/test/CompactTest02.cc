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

#include "Conf.h"
#include "ContainerFactory.h"
#include "../CompactMetaService.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (CompactXmlTest02);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test006EmptyBean)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "006-empty-bean.xml"));

        Variant vB = cont->getBean ("bean1");
        BOOST_CHECK (ccast <String> (vB));

        String cit = vcast <String> (vB);
        BOOST_CHECK (cit.empty ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test007ParentTest)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "007-parent-test.xml"));

        Variant v = cont->getBean ("childBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Foo *> (v));

        Foo *foo = vcast <Foo *> (v);

        BOOST_CHECK (foo->getField0 () == "value0");
        BOOST_CHECK (foo->getField1 () == "value1");
        BOOST_CHECK (foo->getField2 () == 6678);
        BOOST_CHECK (foo->getField3 () == 12.34);
        BOOST_CHECK (foo->getField4 () == 'g');
        BOOST_CHECK (foo->getField5 () == true);
        BOOST_CHECK (foo->getField6 () == 0);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test008StringMap)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "008-string-map.xml"));

        Variant v = cont->getBean ("mojaMapa");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <StringMap *> (v));

        StringMap *map = vcast <StringMap *> (v);

        BOOST_CHECK (map->operator[] ("klucz0") == "wartość0");
        BOOST_CHECK (map->operator[] ("klucz1") == "value1");
        BOOST_CHECK (map->operator[] ("klucz2") == "value2");

        /****************************************************************************/

        map = vcast <StringMap *> (cont->getBean ("mojaMapa3"));
        BOOST_CHECK_EQUAL (map->operator[] ("klucz0"), "wartosc0");
        BOOST_CHECK_EQUAL (map->operator[] ("klucz1"), "wartosc1");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test009StringMapComplex)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "009-string-map-complex.xml"));

        Variant v = cont->getBean ("mojaMapa");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <StringMap *> (v));

        StringMap *map = vcast <StringMap *> (v);

        BOOST_CHECK (map->operator[] ("klucz0") == "wartość0");
        BOOST_CHECK (map->operator[] ("klucz1") == "value1");
        BOOST_CHECK (map->operator[] ("klucz2") == "value2");
        BOOST_CHECK (map->operator[] ("klucz3") == "value3");
}

/**
 *
 */
//BOOST_AUTO_TEST_CASE (test010StringMapComplex)
//{
//}

BOOST_AUTO_TEST_SUITE_END ();
