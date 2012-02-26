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
#include <TestHelpers.h> // Z testHelpers
#include <testHelpers/TestFactories.h> // Z factory

#include "ContainerFactory.h"
#include "metaStructure/model/MetaStructure.h"
#include "common/testHelpers/ContainerTestFactory.h"
#include <boost/make_shared.hpp>

/****************************************************************************/

using namespace Container;
using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerTest06);

/**
 *
 */
BOOST_AUTO_TEST_CASE (testBeanWithCustomFactory)
{
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();

        child->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
        child->setId ("mojBean");
//        Nie ma ustawionego class!
//        child->setClass ("String");
        child->setFactory ("nfactory");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child2 = boost::make_shared <MappedMeta> ();
        child2->setId ("nfactory");
        child2->setClass ("CityFactory");

        metaCont->add (child2);

/*--------------------------------------------------------------------------*/

        Ptr <BeanFactoryContainer> cont = ContainerFactory::createContainer (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ());
        BOOST_CHECK (cont->getBeanFactoryMap ()->size () == 2);

/*--------------------------------------------------------------------------*/

        Variant v = cont->getBean ("mojBean");

        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <City *> (v));

        City *a = vcast <City *> (v);
        BOOST_CHECK (a);

        BOOST_CHECK (a->getName () == "Warszawa");
}

/**
 * To jest tak naprawdę pierwszy poważny test kontenera. Wyciągamy beana
 * o nazwie mojBean, który ma ustawioną klasę foo. Ustawionych jest też
 * 7 fieldów w metastrukturze, każdy ma inny typ. Nie ma żadnych refów.
 */
BOOST_AUTO_TEST_CASE (testSingleton)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure07 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createContainer (metaCont);

/****************************************************************************/

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Foo *> (v));
        Foo *foo1 = vcast <Foo *> (v);

        v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Foo *> (v));
        Foo *foo2 = vcast <Foo *> (v);

        BOOST_CHECK (foo1 != foo2);

/****************************************************************************/

        metaCont = ContainerTestFactory::createMetaStructure21 ();
        cont = ContainerFactory::createContainer (metaCont);

/****************************************************************************/

        v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Foo *> (v));
        foo1 = vcast <Foo *> (v);

        v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Foo *> (v));
        foo2 = vcast <Foo *> (v);

        BOOST_CHECK (foo1 == foo2);
}

/**
 * Testuje init method.
 */
BOOST_AUTO_TEST_CASE (testInitMethod)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure22 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createContainer (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ());
        BOOST_CHECK (cont->getBeanFactoryMap ()->size () == 1);

/****************************************************************************/

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <City *> (v));

        City *foo = vcast <City *> (v);

        BOOST_CHECK_EQUAL (foo->getName(), "Warszawa_INIT");
}

/**
 * Okazuje się, że puste listy i puste mapy potrafią zrobić kontenerowi
 * psikusa i wywalić go. Dlatego jest ten test.
 */
BOOST_AUTO_TEST_CASE (testEmptyListEmptyMap)
{
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();
        child->setId ("mojaMapa");
        child->setClass ("VariantMap");
        metaCont->add (child);

        Ptr <IndexedMeta> child2 = boost::make_shared <IndexedMeta> ();
        child2->setId ("mojaLista");
        child2->setClass ("VariantList");
        metaCont->add (child2);

        Ptr <BeanFactoryContainer> cont = ContainerFactory::createContainer (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ());
        BOOST_CHECK (cont->getBeanFactoryMap ()->size () == 2);

/****************************************************************************/

        // Mapa.

        Variant v = cont->getBean ("mojaMapa");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <VariantMap *> (v));

        VariantMap *map = vcast <VariantMap *> (v);
        BOOST_CHECK (map->size () == 0);

        // Lista.

        v = cont->getBean ("mojaLista");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <VariantList *> (v));

        VariantList *list = vcast <VariantList *> (v);
        BOOST_CHECK (list->size () == 0);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testBeanScope)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure23 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createContainer (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ());
        BOOST_CHECK (cont->getBeanFactoryMap ()->size () == 2);

/****************************************************************************/

        Variant v = cont->getBean ("list");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Ptr <BarMap> > (v));

        Ptr <BarMap> barMap = vcast <Ptr <BarMap> > (v);

        BOOST_CHECK (barMap->size () == 2);
        BOOST_CHECK (barMap->find ("key01") != barMap->end ());
        BOOST_CHECK (barMap->find ("key02") != barMap->end ());

        Ptr <Bar> bar1 = barMap->operator[] ("key01");
        Ptr <Bar> bar2 = barMap->operator[] ("key02");

        BOOST_CHECK (bar1 != bar2);

        BOOST_CHECK (bar1->getCity());
        BOOST_CHECK (bar1->getCity3());

        BOOST_CHECK (bar2->getCity());
        BOOST_CHECK (bar2->getCity3());

        BOOST_CHECK (bar1->getCity() == bar1->getCity3());
        BOOST_CHECK (bar2->getCity() == bar2->getCity3());

        BOOST_CHECK (bar1->getCity() != bar2->getCity ());
}

BOOST_AUTO_TEST_SUITE_END ();