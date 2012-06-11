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
#include "../../../core/Typedefs.h"

/****************************************************************************/

using namespace Container;
using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerTest03);

/**
 *
 */
BOOST_AUTO_TEST_CASE (testCreateVariantMap)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure10 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ().size () == 1U);

/****************************************************************************/

        Variant v = cont->getBean ("mojaMapa");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <VariantMap *> (v));

        VariantMap *map = vcast <VariantMap *> (v);

        BOOST_CHECK_EQUAL (map->size (), 7U);

        BOOST_CHECK (vcast <Core::String> (map->operator[] ("field0")) == "value0");
        BOOST_CHECK (vcast <std::string> (map->operator[] ("field1")) == "value1");
        BOOST_CHECK (vcast <int> (map->operator[] ("field2")) == 6667);
        BOOST_CHECK (vcast <double> (map->operator[] ("field3")) == 123.45);
        BOOST_CHECK (vcast <char> (map->operator[] ("field4")) == 'f');
        BOOST_CHECK (vcast <bool> (map->operator[] ("field5")) == true);
        BOOST_CHECK (map->operator[] ("field6").isNull ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testCreateStringList)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure11 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ().size () == 1);

/****************************************************************************/

        Variant v = cont->getBean ("mojaLista");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <StringList *> (v));

        StringList *list = vcast <StringList *> (v);

        BOOST_CHECK (list->size () == 5);
        StringList::const_iterator i = list->begin ();

        BOOST_CHECK_EQUAL (*i++, "value0");
        BOOST_CHECK_EQUAL (*i++, "value1");
        BOOST_CHECK_EQUAL (*i++, "value2");
        BOOST_CHECK_EQUAL (*i++, "value3");
        BOOST_CHECK_EQUAL (*i++, "value4");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testCreateVariantList)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure12 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ().size () == 1);

/****************************************************************************/

        Variant v = cont->getBean ("mojaLista");
        BOOST_CHECK (!v.isNone ());

        VariantList *list = vcast <VariantList *> (v);

        BOOST_CHECK (list->size () == 7);

        VariantList::const_iterator i = list->begin ();
        BOOST_CHECK_EQUAL (vcast <String> (*i++), "value0");
        BOOST_CHECK_EQUAL (vcast <std::string> (*i++), "value1");
        BOOST_CHECK_EQUAL (vcast <int> (*i++), 6665);
        BOOST_CHECK_EQUAL (vcast <double> (*i++), 123.45);
        BOOST_CHECK_EQUAL (vcast <char> (*i++), 'f');
        BOOST_CHECK_EQUAL (vcast <bool> (*i++), true);
        BOOST_CHECK ((*i++).isNull ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testCreateCountryList)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure13 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ().size () == 4);

/****************************************************************************/

        Variant v = cont->getBean ("mojaLista");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <CountryVector *> (v));

        CountryVector *list = vcast <CountryVector *> (v);

        BOOST_CHECK (list->size () == 3);

        Ptr <Country> c = list->operator[] (0);
        BOOST_CHECK (c->getName () == "Polska");

        c = list->operator[] (1);
        BOOST_CHECK (c->getName () == "Jamajka");

        c = list->operator[] (2);
        BOOST_CHECK (c->getName () == "Wolny Tybet");
}

/**
 * Tworzymy mape, ktora zawera referencje do 3 beanow typu Conuntry, kazdy
 z nich ma ustawione property name.
 */
BOOST_AUTO_TEST_CASE (testCreateCountryMap)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure14 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ().size () == 4);

/****************************************************************************/

        City cit;
        City *cit0 = &cit;
        Variant v1 = Core::Variant (cit0);
        BOOST_CHECK (!v1.isNone ());
        BOOST_CHECK (ccast <City *> (v1));
        BOOST_CHECK (ccast <City const *> (v1));


        Variant v = cont->getBean ("city1");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <City *> (v));
        BOOST_CHECK (ccast <City const *> (v));

        v = cont->getBean ("mojaMapka");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <CityMap *> (v));

        CityMap *map = vcast <CityMap *> (v);

        BOOST_CHECK (map->size () == 3);
        BOOST_CHECK (map->find ("field0") != map->end ());
        BOOST_CHECK (map->find ("field1") != map->end ());
        BOOST_CHECK (map->find ("field2") != map->end ());

        BOOST_CHECK (map->operator[] ("field0")->getName () == "Warszawa");
        BOOST_CHECK (map->operator[] ("field1")->getName () == "Krakow");
        BOOST_CHECK (map->operator[] ("field2")->getName () == "Piaseczno");
}

BOOST_AUTO_TEST_SUITE_END ();
