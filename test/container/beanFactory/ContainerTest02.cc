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

/****************************************************************************/

using namespace Container;
using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerTest02);

/**
 * To jest tak naprawdę pierwszy poważny test kontenera. Wyciągamy beana
 * o nazwie mojBean, który ma ustawioną klasę foo. Ustawionych jest też
 * 7 fieldów w metastrukturze, każdy ma inny typ. Nie ma żadnych refów.
 */
BOOST_AUTO_TEST_CASE (testCreateOneSimpleBean)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure07 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ().size () == 1);

/****************************************************************************/

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Foo *> (v));

        Ptr <Foo> foo = vcast <Ptr <Foo> > (v);

        BOOST_CHECK_EQUAL (foo->getField0 (), "value0");
        BOOST_CHECK_EQUAL (foo->getField1 (), "value1");
        BOOST_CHECK_EQUAL (foo->getField2 (), 6667);
        BOOST_CHECK_EQUAL (foo->getField3 (), 123.45);
        BOOST_CHECK_EQUAL (foo->getField4 (), 'f');
        BOOST_CHECK_EQUAL (foo->getField5 (), true);
        BOOST_CHECK (!foo->getField6 ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testCreateBeanWithReference)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure08 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        BOOST_CHECK_EQUAL (cont->getBeanFactoryMap ().size (), 1U);
//        Tak nie można, bo tam są serwisowe, ale jest jedna fabryka i jeden singleton
//        BOOST_CHECK_EQUAL (cont->getSingletons ()->size (), 1U);

/****************************************************************************/

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());

        Ptr <Foo> foo = vcast <Ptr <Foo> > (v);

        BOOST_CHECK_EQUAL (foo->getField0 (), "value0");
        BOOST_CHECK_EQUAL (foo->getField1 (), "value1");
        BOOST_CHECK_EQUAL (foo->getField2 (), 6667);
        BOOST_CHECK_EQUAL (foo->getField3 (), 123.45);
        BOOST_CHECK_EQUAL (foo->getField4 (), 'f');
        BOOST_CHECK_EQUAL (foo->getField5 (), true);
        BOOST_CHECK (!foo->getField6 ());

/****************************************************************************/

        BOOST_CHECK (foo->getCity ());
        BOOST_CHECK (foo->getCity ()->getName () == "Warszawa");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testCreateStringMap)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure09 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        Variant v = cont->getBean ("mojaMapa");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <StringMap *> (v));

        StringMap *map = vcast <StringMap *> (v);

        BOOST_CHECK_EQUAL (map->size (), 4U);
        BOOST_CHECK_EQUAL (map->operator[] ("field0"), "value0");
        BOOST_CHECK_EQUAL (map->operator[] ("field1"), "value1");
        BOOST_CHECK_EQUAL (map->operator[] ("field2"), "value2");
        BOOST_CHECK_EQUAL (map->operator[] ("field3"), "value3");
}

BOOST_AUTO_TEST_SUITE_END ();
