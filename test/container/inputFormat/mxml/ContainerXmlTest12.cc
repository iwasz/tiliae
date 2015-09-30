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

BOOST_AUTO_TEST_SUITE (ContainerXmlTest12);

/**
 * Gdy dziedziczmymy z parenta, który nie został zdefiniowany,
 * leci wyjątek NoSuchBeanException.
 */
BOOST_AUTO_TEST_CASE (test056NonExistentParent)
{
        BOOST_REQUIRE_THROW ((ContainerTestFactory::getContainer (PATH + "056-non-existent-parent.xml")), NoSuchBeanException);
}

/**
 * Testuje różne zakresy żywotności listy.
 */
BOOST_AUTO_TEST_CASE (test057ListScopeTests)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "057-list-scope.xml");

        Variant v = cont->getBean ("listaSingleton");
        BarList *barList = vcast <BarList *> (v);
        BOOST_CHECK (barList);

        BOOST_CHECK (barList->size () == 2);

        BarList::const_iterator i = barList->begin ();

        BOOST_CHECK (*i);
        Ptr <Bar> bar1 = *i++;

        BOOST_CHECK (*i);
        Ptr <Bar> bar2 = *i;

        BOOST_CHECK (bar1 != bar2);

        BOOST_CHECK (vcast <StringList *> (bar1->getButter()) == vcast <StringList *> (bar1->getButter2()));
        BOOST_CHECK (vcast <StringList *> (bar2->getButter()) == vcast <StringList *> (bar2->getButter2()));
        BOOST_CHECK (vcast <StringList *> (bar1->getButter()) == vcast <StringList *> (bar1->getButter()));

/****************************************************************************/

        v = cont->getBean ("listaPrototype");
        BOOST_CHECK (!v.isNone ());

        barList = vcast <BarList *> (v);

        BOOST_CHECK (barList->size () == 2);

        i = barList->begin ();
        bar1 = *i++;
        bar2 = *i;

        BOOST_CHECK (bar1 != bar2);

        BOOST_CHECK (vcast <StringList *> (bar1->getButter()) != vcast <StringList *> (bar1->getButter2()));
        BOOST_CHECK (vcast <StringList *> (bar2->getButter()) != vcast <StringList *> (bar2->getButter2()));
        BOOST_CHECK (vcast <StringList *> (bar1->getButter()) != vcast <StringList *> (bar2->getButter()));

/****************************************************************************/

        v = cont->getBean ("listaBean1");
        BOOST_CHECK (!v.isNone ());

        BeanFactory *bf = cont->getBeanFactory ("bean2");
        BOOST_CHECK (bf);
        bf = bf->getInnerBeanFactory("inner2");
        BOOST_CHECK (bf);

        barList = vcast <BarList *> (v);

        BOOST_CHECK (barList->size () == 2);

        i = barList->begin ();
        bar1 = *i++;
        bar2 = *i;

        BOOST_CHECK (bar1 != bar2);

        BOOST_CHECK (vcast <StringList *> (bar1->getButter()) == vcast <StringList *> (bar1->getButter2()));
        BOOST_CHECK (vcast <StringList *> (bar2->getButter()) == vcast <StringList *> (bar2->getButter2()));
        BOOST_CHECK (vcast <StringList *> (bar1->getButter()) != vcast <StringList *> (bar2->getButter()));
}

/**
 * Testuje różne zakresy żywotności map.
 */
BOOST_AUTO_TEST_CASE (test058MapScopeTests)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "058-map-scope.xml");

        Variant v = cont->getBean ("listaSingleton");
        BarList *barList = vcast <BarList *> (v);
        BOOST_CHECK (barList);

        BOOST_CHECK (barList->size () == 2);

        BarList::const_iterator i = barList->begin ();
        Ptr <Bar> bar1 = *i++;
        Ptr <Bar> bar2 = *i;

        BOOST_CHECK (bar1);
        BOOST_CHECK (bar2);

        BOOST_CHECK (bar1 != bar2);

        BOOST_CHECK (vcast <StringMap *> (bar1->getButter()) == vcast <StringMap *> (bar1->getButter2()));
        BOOST_CHECK (vcast <StringMap *> (bar2->getButter()) == vcast <StringMap *> (bar2->getButter2()));
        BOOST_CHECK (vcast <StringMap *> (bar1->getButter()) == vcast <StringMap *> (bar1->getButter()));

/****************************************************************************/

        v = cont->getBean ("listaPrototype");
        BOOST_CHECK (!v.isNone ());

        barList = vcast <BarList *> (v);

        BOOST_CHECK (barList->size () == 2);

        i = barList->begin ();
        bar1 = *i++;
        bar2 = *i;

        BOOST_CHECK (bar1 != bar2);

        BOOST_CHECK (vcast <StringMap *> (bar1->getButter()) != vcast <StringMap *> (bar1->getButter2()));
        BOOST_CHECK (vcast <StringMap *> (bar2->getButter()) != vcast <StringMap *> (bar2->getButter2()));
        BOOST_CHECK (vcast <StringMap *> (bar1->getButter()) != vcast <StringMap *> (bar2->getButter()));

/****************************************************************************/

        v = cont->getBean ("listaBean1");
        BOOST_CHECK (!v.isNone ());

        BeanFactory *bf = cont->getBeanFactory ("bean2");
        BOOST_CHECK (bf);
        bf = bf->getInnerBeanFactory("inner2");
        BOOST_CHECK (bf);

        barList = vcast <BarList *> (v);

        BOOST_CHECK (barList->size () == 2);

        i = barList->begin ();
        bar1 = *i++;
        bar2 = *i;

        BOOST_CHECK (bar1 != bar2);

        BOOST_CHECK (vcast <StringMap *> (bar1->getButter()) == vcast <StringMap *> (bar1->getButter2()));
        BOOST_CHECK (vcast <StringMap *> (bar2->getButter()) == vcast <StringMap *> (bar2->getButter2()));
        BOOST_CHECK (vcast <StringMap *> (bar1->getButter()) != vcast <StringMap *> (bar2->getButter()));
}

/**
 * Testuje import - Xml importuje jeden XML.
 */
BOOST_AUTO_TEST_CASE (test059ImportSimple)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "059-import.xml");

        StringList *list = vcast <StringList *> (cont->getBean ("bean1"));
        BOOST_CHECK (list);

        list = vcast <StringList *> (cont->getBean ("bean2"));
        BOOST_CHECK (list);
}

/**
 * Testuje import, ale wiele zagnieżdżeń.
 */
BOOST_AUTO_TEST_CASE (test060ImportAdvanced)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "060-import.xml");

        StringList * list = vcast <StringList *> (cont->getBean ("bean1"));
        BOOST_CHECK (list);

        list = vcast <StringList *> (cont->getBean ("bean2"));
        BOOST_CHECK (list);

        list = vcast <StringList *> (cont->getBean ("bean3"));
        BOOST_CHECK (list);

        list = vcast <StringList *> (cont->getBean ("bean4"));
        BOOST_CHECK (list);
}

BOOST_AUTO_TEST_SUITE_END ();
