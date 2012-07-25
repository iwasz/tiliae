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

BOOST_AUTO_TEST_SUITE (CommonXmlTest09);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test041InitMethod)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "041-init-method.xml"));

        Variant vB = cont->getBean ("city");
        BOOST_CHECK (ccast <City *> (vB));

        City *cit = vcast <City *> (vB);
        BOOST_CHECK (cit);
        BOOST_CHECK_EQUAL (cit->getName (), "Warszawa_INIT");
}

/**
 * Miałem notatkę, że się wyjebywało na mapie z pustym kluczem (w poprzedniej wersji).
 * Stąd ten test.
 */
BOOST_AUTO_TEST_CASE (test042EmptyMapKey)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "042-map-with-empty-key.xml"));

        Variant vB = cont->getBean ("mojaMapa");
        BOOST_CHECK (ccast <StringMap *> (vB));

        StringMap *map = vcast <StringMap *> (vB);
        BOOST_CHECK (map);
}

/**
 * Kolejny błąd, który miałem zapisany : kiedy były 2 beany o
 * tym samym ID, to leciał SegF w poprzedniej wersji.
 */
BOOST_AUTO_TEST_CASE (test043MultipleIdBean)
{
        BOOST_REQUIRE_THROW (ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "043-multiple-id-bean.xml")), Core::Exception);
}

/**
 * Kolejny jakiś tam test, na coś, co się kiedyś działo : kiedyś, w starej
 * wersji za property działało jak entry i dodawało elementy do mapy. Teraz
 * już tak nie jest. Dlaczego parser nie zgłasza błędu, przecież w DTD to jest
 * zabronione!
 */
BOOST_AUTO_TEST_CASE (test044PropertyInMap)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "044-property-in-map.xml"));

        Variant vB = cont->getBean ("mojaMapa");
        BOOST_CHECK (ccast <StringMap *> (vB));

        StringMap *map = vcast <StringMap *> (vB);
        BOOST_CHECK (map);

        BOOST_CHECK (map->find ("klucz0") != map->end ());
        BOOST_CHECK (map->find ("klucz1") != map->end ());
        BOOST_CHECK_EQUAL (map->size (), 2U);

/*--------------------------------------------------------------------------*/

//        W MXML to już zrzuca wyjątek

//        vB = cont->getBean ("mojaMapa2");
//        BOOST_CHECK (ccast <StringMap *> (vB));
//
//        map = vcast <StringMap *> (vB);
//        BOOST_CHECK (map);
//
//        BOOST_CHECK (map->size () == 0);
}

/**
 * Testy, czy da sie tworzyć skalary jako beany i czy da sie używać
 * ich konstruktorów kopiujących.
 */
BOOST_AUTO_TEST_CASE (test045BaseTypesConstructors)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "045-base-types-constructors.xml"));

        Variant vB = cont->getBean ("string1");
        BOOST_CHECK (ccast <String> (vB));
        BOOST_CHECK_EQUAL (vcast <String> (vB), "");

        vB = cont->getBean ("string2");
        BOOST_CHECK (ccast <String> (vB));
        BOOST_CHECK_EQUAL (vcast <String> (vB), "testaaa");

        vB = cont->getBean ("int1");
        BOOST_CHECK (ccast <int> (vB));

        vB = cont->getBean ("int2");
        BOOST_CHECK (ccast <int> (vB));
        BOOST_CHECK (vcast <int> (vB) == 6667);
}

BOOST_AUTO_TEST_SUITE_END ();
