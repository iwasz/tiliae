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
#include <misc/K202Proxy.h>

#include "ContainerFactory.h"
#include "metaStructure/model/MetaStructure.h"
#include "common/testHelpers/ContainerTestFactory.h"
#include "Conf.h"
#include "../../../../core/Exception.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerXmlTest10);

/**
 * To jest kawałek kodu, ktory testuje pomysł implementacji prop-value
 * za pomocą beanów.
 */
BOOST_AUTO_TEST_CASE (test046PropValue)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "046-prop-value-test-01.xml");
//TODO odkomentować, kiedy będzie zaimplementowane
//                Variant vB = cont->getBean ("bean");

//                StringMap *cit = vcast <StringMap *> (vB);
//                BOOST_CHECK (cit);
}

/**
 * Test compound porperties. Okazało się, że po prostu działa. Nic
 * nie zmieniałem i po prostu zadziałało :)
 */
BOOST_AUTO_TEST_CASE (test047CompoundProperties)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "047-compound-properties-basic.xml");

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
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "048-property-order.xml");

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
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "049-property-order.xml");
        BOOST_CHECK_THROW ((cont->getBean ("multi")), Core::Exception);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test050PropertyOrderParent)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "050-property-order-parent.xml");

        Variant vB = cont->getBean ("parentMap");
        BOOST_CHECK (ccast <VariantMap *> (vB));

        vB = cont->getBean ("childMap");
        BOOST_CHECK (ccast <VariantMap *> (vB));

        vB = cont->getBean ("testTool");
        BOOST_CHECK (ccast <k202::K202Proxy *> (vB));
        k202::K202Proxy *k202 = vcast <k202::K202Proxy *> (vB);

        BOOST_CHECK (k202);
        vB = k202->run ();

        BOOST_CHECK (ccast <bool> (vB));
        BOOST_CHECK (vcast <bool> (vB) == true);
}

BOOST_AUTO_TEST_SUITE_END ();
