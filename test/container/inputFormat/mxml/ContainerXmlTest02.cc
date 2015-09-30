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

BOOST_AUTO_TEST_SUITE (ContainerXmlTest02);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test006EmptyBean)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "006-empty-bean.xml");

        Variant vB = cont->getBean ("bean");
        BOOST_CHECK (ccast <std::string> (vB));

        std::string cit = vcast <std::string> (vB);
        BOOST_CHECK (cit.empty ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test007ParentTest)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "007-parent-test.xml");

        Variant v = cont->getBean ("childBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Foo *> (v));

        Foo *foo = vcast <Foo *> (v);

        BOOST_CHECK_EQUAL (foo->getField0 (), "value0");
        BOOST_CHECK_EQUAL (foo->getField1 (), "value1");
        BOOST_CHECK_EQUAL (foo->getField2 (), 6678);
        BOOST_CHECK_EQUAL (foo->getField3 (), 12.34);
        BOOST_CHECK_EQUAL (foo->getField4 (), 'g');
        BOOST_CHECK_EQUAL (foo->getField5 (), true);
        BOOST_CHECK (!foo->getField6 ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test008StringMap)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "008-string-map.xml");

        Variant v = cont->getBean ("mojaMapa");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <StringMap *> (v));

        StringMap *map = vcast <StringMap *> (v);

        BOOST_CHECK (map->operator[] ("klucz0") == "wartość0");
        BOOST_CHECK (map->operator[] ("klucz1") == "value1");
        BOOST_CHECK (map->operator[] ("klucz2") == "value2");
        BOOST_CHECK (map->operator[] ("klucz3") == "value3");
        BOOST_CHECK (map->operator[] ("klucz4") == "value4");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test009StringMapComplex)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "009-string-map-complex.xml");

        Variant v = cont->getBean ("mojaMapa");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <StringMap *> (v));

        StringMap *map = vcast <StringMap *> (v);

        BOOST_CHECK (map->operator[] ("klucz0") == "wartość0");
        BOOST_CHECK (map->operator[] ("klucz1") == "value1");
        BOOST_CHECK (map->operator[] ("klucz2") == "value2");
        BOOST_CHECK (map->operator[] ("klucz3") == "value3");
        BOOST_CHECK (map->operator[] ("klucz4") == "value4");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test010StringMapComplex)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "010-string-map-complex.xml");

        Variant v = cont->getBean ("mojaMapa");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <StringMap *> (v));

        StringMap *map = vcast <StringMap *> (v);

        BOOST_CHECK (map->operator[] ("klucz0") == "wartość0");
        BOOST_CHECK (map->operator[] ("klucz1") == "value1");
        BOOST_CHECK (map->operator[] ("klucz2") == "value2");
        BOOST_CHECK (map->operator[] ("klucz3") == "value3");
        BOOST_CHECK (map->operator[] ("klucz4") == "value4");
}

BOOST_AUTO_TEST_SUITE_END ();
