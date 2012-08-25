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
#include "Conf.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerXmlTest06);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test026TestSingleton)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "026-test-singleton.xml");

        Variant vNS1 = cont->getBean ("cityNonSingleton");
        BOOST_CHECK (ccast <City *> (vNS1));

        Variant vNS2 = cont->getBean ("cityNonSingleton");
        BOOST_CHECK (ccast <City *> (vNS2));

        BOOST_CHECK (vcast <Ptr <City> > (vNS1) != vcast <Ptr <City> > (vNS2));

        // -------------------------

        Variant vS1 = cont->getBean ("citySingleton");
        BOOST_CHECK (ccast <City *> (vS1));

        Variant vS2 = cont->getBean ("citySingleton");
        BOOST_CHECK (ccast <City *> (vS2));

        BOOST_CHECK (vcast <City *> (vS1) == vcast <City *> (vS2));

/*--------------------------------------------------------------------------*/

        {
                Variant vS1 = cont->getBean ("lista");
                BOOST_CHECK (ccast <StringList *> (vS1));

                Variant vS2 = cont->getBean ("lista");
                BOOST_CHECK (ccast <StringList*> (vS2));

                BOOST_CHECK (vcast <StringList *> (vS1) == vcast <StringList *> (vS2));
        }

/*--------------------------------------------------------------------------*/

        {
                Variant vS1 = cont->getBean ("mapa");
                BOOST_CHECK (ccast <StringMap *> (vS1));

                Variant vS2 = cont->getBean ("mapa");
                BOOST_CHECK (ccast <StringMap*> (vS2));

                BOOST_CHECK (vcast <StringMap *> (vS1) == vcast <StringMap *> (vS2));
        }

/*--------------------------------------------------------------------------*/

        {
                Variant vS1 = cont->getBean ("citySingleton2");
                BOOST_CHECK (ccast <City *> (vS1));

                Variant vS2 = cont->getBean ("citySingleton2");
                BOOST_CHECK (ccast <City *> (vS2));

                BOOST_CHECK (vcast <City *> (vS1) == vcast <City *> (vS2));
        }

/*--------------------------------------------------------------------------*/

        {
                Variant vS1 = cont->getBean ("lista2");
                BOOST_CHECK (ccast <StringList *> (vS1));

                Variant vS2 = cont->getBean ("lista2");
                BOOST_CHECK (ccast <StringList*> (vS2));

                BOOST_CHECK (vcast <StringList *> (vS1) == vcast <StringList *> (vS2));
        }

/*--------------------------------------------------------------------------*/

        {
                Variant vS1 = cont->getBean ("mapa2");
                BOOST_CHECK (ccast <StringMap *> (vS1));

                Variant vS2 = cont->getBean ("mapa2");
                BOOST_CHECK (ccast <StringMap*> (vS2));

                BOOST_CHECK (vcast <StringMap *> (vS1) == vcast <StringMap *> (vS2));
        }

}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test027EmbededBean)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "027-embeded-bean.xml");

        Variant v = cont->getBean ("kinkreet");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Foo *> (v));

        Foo *foo = vcast <Foo *> (v);

        BOOST_CHECK (foo->getField0() == "value01");
        BOOST_CHECK (foo->getField1() == "value02");

        BOOST_CHECK (foo->getCity ());
        BOOST_CHECK (foo->getCity ()->getName () == "Tokio");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test028EmbededMap)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "028-embeded-map.xml");

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Bar *> (v));

        Bar *foo = vcast <Bar *> (v);

        BOOST_CHECK (foo->getField0() == "value01");
        BOOST_CHECK (foo->getField1() == "value02");

        BOOST_CHECK (!foo->getButter ().isNone ());
        BOOST_CHECK (ccast <StringMap> (foo->getButter ()));

        StringMap *map = vcast <StringMap *> (foo->getButter ());

        BOOST_CHECK (map->size () == 3);
        BOOST_CHECK (map->operator[] ("k1") == "Tokio");
        BOOST_CHECK (map->operator[] ("k2") == "Warsaw");
        BOOST_CHECK (map->operator[] ("k3") == "Piaseczno");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test029EmbededList)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "029-embeded-list.xml");

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Bar *> (v));

        Bar *foo = vcast <Bar *> (v);

        BOOST_CHECK (foo->getField0() == "value01");
        BOOST_CHECK (foo->getField1() == "value02");

        BOOST_CHECK (!foo->getButter ().isNone ());
        BOOST_CHECK (ccast <StringVector *> (foo->getButter ()));

        StringVector *list = vcast <StringVector *> (foo->getButter ());

        BOOST_CHECK (list->size () == 3);
        BOOST_CHECK (list->operator[] (0) == "Tokio");
        BOOST_CHECK (list->operator[] (1) == "Warsaw");
        BOOST_CHECK (list->operator[] (2) == "Kraków");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test030BeanInCarg)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "030-bean-in-carg.xml");

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Bar *> (v));

        Bar *foo = vcast <Bar *> (v);

        BOOST_CHECK (foo->getField0() == "value01");
        BOOST_CHECK (foo->getField1() == "value02");

        BOOST_CHECK (!foo->getButter ().isNone ());
        BOOST_CHECK (ccast <City *> (foo->getButter ()));

        City *cit = vcast <City *> (foo->getButter ());

        BOOST_CHECK (cit->getName () == "Tokio");
}

BOOST_AUTO_TEST_SUITE_END ();
