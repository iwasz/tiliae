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
#include "container/inputFormat/compact/CompactMetaService.h"
#include "Conf.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (CompactXmlTest04);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test016CityMap)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "016-city-map.xml"));

        Variant v = cont->getBean ("mojaMapa");
        BOOST_CHECK (!v.isNone ());

        CityMap *foo = vcast <CityMap *> (v);

//        std::cerr << foo->size () << std::endl;
//        std::cerr << foo->operator[] ("city01")->getName () << std::endl;

        BOOST_CHECK (foo->operator[] ("city01"));
        BOOST_CHECK (foo->operator[] ("city01")->getName () == "Tokio");

        BOOST_CHECK (foo->operator[] ("city02"));
//        std::cerr << foo->operator[] ("city02")->getName () << std::endl;
        BOOST_CHECK (foo->operator[] ("city02")->getName () == "Kraków");

        BOOST_CHECK (foo->operator[] ("city03"));
//        std::cerr << foo->operator[] ("city03")->getName () << std::endl;
        BOOST_CHECK (foo->operator[] ("city03")->getName () == "Warszawa");

        BOOST_CHECK (foo->operator[] ("city04"));
//        std::cerr << foo->operator[] ("city04")->getName () << std::endl;
        BOOST_CHECK (foo->operator[] ("city04")->getName () == "Oszlo");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test017CityList)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "017-city-list.xml"));

        Variant v = cont->getBean ("miasta");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <CityList *> (v));

        CityList *foo = vcast <CityList *> (v);

        BOOST_CHECK (foo->size () == 5);
        CityList::const_iterator i = foo->begin ();

        City *c = *i++;
        BOOST_CHECK (c);
        BOOST_CHECK_EQUAL (c->getName (), "Tokio");

        c = *i++;
        BOOST_CHECK (c);
        BOOST_CHECK_EQUAL (c->getName (), "Kraków");

        c = *i++;
        BOOST_CHECK (c);
        BOOST_CHECK_EQUAL (c->getName (), "Warszawa");

        c = *i++;
        BOOST_CHECK (c);
        BOOST_CHECK_EQUAL (c->getName (), "Oszlo");

        c = *i;
        BOOST_CHECK (!c);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test018EmptyListEmptyMap)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "018-empty-list-empty-map.xml"));

        // Lista

        Variant v = cont->getBean ("mojaLista");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <CityList *> (v));

        CityList *foo = vcast <CityList *> (v);
        BOOST_CHECK (foo->size () == 0);

        // Mapa

        v = cont->getBean ("mojaMapa");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <CityMap *> (v));

        CityMap *mojaMapa = vcast <CityMap *> (v);
        BOOST_CHECK (mojaMapa->size () == 0);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test019BeanWithCArgs)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "019-bean-with-cargs.xml"));

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Bar *> (v));

        Bar *foo = vcast <Bar *> (v);

        BOOST_CHECK (foo->getField0 () == "value0");
        BOOST_CHECK (foo->getField1 () == "value1");
        BOOST_CHECK (foo->getField2 () == 6678);
        BOOST_CHECK (foo->getField3 () == 12.34);
        BOOST_CHECK (foo->getField4 () == 'g');
        BOOST_CHECK (foo->getField5 () == true);
        BOOST_CHECK (!foo->getField6 ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test020CArgsAndRef)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "020-cargs-and-ref.xml"));

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Bar *> (v));

        Bar *foo = vcast <Bar *> (v);

        BOOST_CHECK (foo->getField0 () == "value0");
        BOOST_CHECK (foo->getField1 () == "value1");

        BOOST_CHECK (foo->getCity ());
        BOOST_CHECK (foo->getCity ()->getName () == "Tokio");
}

BOOST_AUTO_TEST_SUITE_END ();
