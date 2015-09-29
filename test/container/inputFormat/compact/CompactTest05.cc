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

BOOST_AUTO_TEST_SUITE (CompactXmlTest05);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test022ListWithCustomEditor)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "022-list-with-custom-editor.xml"));

        Variant v = cont->getBean ("mojString");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <std::string> (v));

        std::string s = vcast <std::string> (v);
        BOOST_CHECK (s == "\"value0\",\"value1\",\"value2\",\"value3\",\"value4\"");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test023BeanWithCustomFactory)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "023-bean-with-custom-factory.xml"));

        Variant v = cont->getBean ("city");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <City *> (v));

        City *a = vcast <City *> (v);

        BOOST_CHECK (a);
        BOOST_CHECK (a->getName () == "Warszawa");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test024MapAndListWithCustomFactory)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "024-map-and-list-with-custom-factory.xml"));

        Variant v = cont->getBean ("myMap");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <StringMap *> (v));

        StringMap *a = vcast <StringMap *> (v);
        BOOST_CHECK (a->size () == 4);

        BOOST_CHECK (a->operator[] ("k1") == "v1");
        BOOST_CHECK (a->operator[] ("k2") == "v2");
        BOOST_CHECK (a->operator[] ("k3") == "v3");
        BOOST_CHECK (a->operator[] ("k4") == "v4");

// ---------------------
//
//        v = cont->getBean ("myList");
//        BOOST_CHECK (!v.isNone ());
//        BOOST_CHECK (ccast <StringVector *> (v));
//
//        StringVector *b = vcast <StringVector *> (v);
//        BOOST_CHECK (b->size () == 4);
//
//        BOOST_CHECK (b->operator[] (0) == "v1");
//        BOOST_CHECK (b->operator[] (1) == "v2");
//        BOOST_CHECK (b->operator[] (2) == "v3");
//        BOOST_CHECK (b->operator[] (3) == "v4");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test025ValueWithCustomEditor)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "025-value-with-custom-editor.xml"));

        Variant v = cont->getBean ("mojaMapa");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <StringMap *> (v));

        StringMap *map = vcast <StringMap *> (v);

        BOOST_CHECK (map->operator[] ("k0") == "(value1)");
        BOOST_CHECK (map->operator[] ("k1") == "(value2)");
        BOOST_CHECK (map->operator[] ("k2") == "(value3)");
}

BOOST_AUTO_TEST_SUITE_END ();
