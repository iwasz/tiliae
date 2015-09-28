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

BOOST_AUTO_TEST_SUITE (CompactXmlTest10);

/**
 * To jest kawałek kodu, ktory testuje pomysł implementacji prop-value
 * za pomocą beanów.
 */
BOOST_AUTO_TEST_CASE (test046PropValue)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "046-prop-value-test-01.xml"));
        Variant vB = cont->getBean ("bean1");

        StringMap *cit = vcast <StringMap *> (vB);
        BOOST_CHECK (cit);
}

/**
 * Test compound porperties. Okazało się, że po prostu działa. Nic
 * nie zmieniałem i po prostu zadziałało :)
 */
BOOST_AUTO_TEST_CASE (test047CompoundProperties)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "047-compound-properties-basic.xml"));

        Variant vB = cont->getBean ("multi");
        BOOST_CHECK (ccast <Bar *> (vB));

        Bar *bar = vcast <Bar *> (vB);
        BOOST_CHECK (bar);
        BOOST_CHECK (bar->getCity ());
        BOOST_CHECK (bar->getCity ()->getName () == "Warszawa44");
}

/**
 * Testuje kolejność ustawiania properties beanowi. Powstało wymaganie,
 * aby kolejność ustawiania property do wynikowego beana była taka sama
 * jak kolejność meta-elementów w obiekcie meta i co za tym idzie kolejność
 * występowania tagów <property> w pliku XML. Jest to potrzebne do
 * poprawnego działania compound-properties. Na przykład co by się stało
 * gdyby ktoś najpierw ustawił property city.name, a dopiero potem city?
 *
 * Ten test powinien przejść.
 */
BOOST_AUTO_TEST_CASE (test048PropertyOrder)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "048-property-order.xml"));

        Variant vB = cont->getBean ("multi01");
        BOOST_CHECK (ccast <Bar *> (vB));

        Bar *bar = vcast <Bar *> (vB);
        BOOST_CHECK (bar);
        BOOST_CHECK (bar->getCity3 ());
        BOOST_CHECK (bar->getCity3 ()->getName () == "Warszawa");
}

/**
 * Ten test kidyś miał się wywalić, a teraz po małym refaktorze przejdzie.
 * Otóż propertisy ustawiają się w kolejniści występowania w XML, z małą
 * różnicą : refy idą najpierw.
 */
BOOST_AUTO_TEST_CASE (test049PropertyOrder)
{
        BOOST_CHECK_THROW (ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "049-property-order.xml")), Core::Exception);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test050PropertyOrderParent)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "050-property-order-parent.xml"));

        Variant vB = cont->getBean ("parentMap");
        BOOST_REQUIRE (ccast <VariantMap *> (vB));

        vB = cont->getBean ("childMap");
        BOOST_REQUIRE (ccast <VariantMap *> (vB));

        VariantMap *m1 = vcast <VariantMap *> (vB);
        VariantMap *m2 = vcast <VariantMap *> (m1->operator [] ("b"));
        BOOST_REQUIRE_EQUAL (vcast <std::string> (m2->operator []("c")), "Test34");
}

BOOST_AUTO_TEST_SUITE_END ();
