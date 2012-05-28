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
#include "../MXmlMetaService.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerXmlTest11);

/**
 * Testuje kolejność ustawiania się propery w beanie.
 */
BOOST_AUTO_TEST_CASE (test051PropertyOrder)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "051-property-order.xml");

        Variant vB = cont->getBean ("bean");
        BOOST_CHECK (!vB.isNone());

        BOOST_CHECK_THROW (cont->getBean ("bean2"), Core::Exception);
}

/**
 * Testuje, czy można się odwoływac po id do zagnieżdżonego beana.
 */
BOOST_AUTO_TEST_CASE (test052NestedBeanWithId)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "052-nested-bean-with-id.xml");

        Variant vB = cont->getBean ("bean");
        BOOST_CHECK (!vB.isNone());
        Ptr <Bar> bar = vcast <Ptr <Bar> > (vB);

        BOOST_CHECK (bar->getCity ());
        BOOST_CHECK (bar->getCity3 ());
        BOOST_CHECK (bar->getCity3 () == bar->getCity ());
}

/**
 * Testuje różne zakresy żywotności beana.
 */
BOOST_AUTO_TEST_CASE (test053BeanScopeFirstTests)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "053-bean-scope-first-tests.xml");

        Variant v = cont->getBean ("listaSingleton");
        Ptr <BarList> barList = vcast <Ptr <BarList> > (v);
        BOOST_CHECK (barList);

        BOOST_CHECK (barList->size () == 2);
        BarList::const_iterator i = barList->begin ();

        Ptr <Bar> bar1 = *i++;
        Ptr <Bar> bar2 = *i;

        BOOST_CHECK (bar1 != bar2);

        BOOST_CHECK (bar1->getCity());
        BOOST_CHECK (bar1->getCity3());

        BOOST_CHECK (bar2->getCity());
        BOOST_CHECK (bar2->getCity3());

        BOOST_CHECK (bar1->getCity() == bar1->getCity3());
        BOOST_CHECK (bar2->getCity() == bar2->getCity3());

        BOOST_CHECK (bar1->getCity() == bar2->getCity ());

/****************************************************************************/

        v = cont->getBean ("listaPrototype");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Ptr <BarList> > (v));

        barList = vcast <Ptr <BarList> > (v);

        BOOST_CHECK (barList->size () == 2);

        i = barList->begin ();
        bar1 = *i++;
        bar2 = *i;

        BOOST_CHECK (bar1 != bar2);

        BOOST_CHECK (bar1->getCity());
        BOOST_CHECK (bar1->getCity3());

        BOOST_CHECK (bar2->getCity());
        BOOST_CHECK (bar2->getCity3());

        BOOST_CHECK (bar1->getCity() != bar1->getCity3());
        BOOST_CHECK (bar2->getCity() != bar2->getCity3());

        BOOST_CHECK (bar1->getCity() != bar2->getCity ());

/****************************************************************************/

         Ptr <MetaContainer> mc = MXmlMetaService::parseFile (PATH + "053-bean-scope-first-tests.xml");

        BOOST_CHECK (mc->getMetaMap ().size () == 8);
        IMeta *meta = mc->get ("bean2");

        MetaMap innerM = meta->getInnerMetas ();
        BOOST_CHECK (innerM.size () == 1);

        BOOST_CHECK (innerM.find ("innerCity2") != innerM.end ());

        IMeta *in = innerM["innerCity2"];
        BOOST_CHECK (in);

/****************************************************************************/

        v = cont->getBean ("listaBean1");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Ptr <BarList> > (v));

        Ptr <BeanFactory> bf = cont->getBeanFactory ("bean2");
        BOOST_CHECK (bf);
        bf = bf->getInnerBeanFactory("innerCity2");
        BOOST_CHECK (bf);

        barList = vcast <Ptr <BarList> > (v);

        BOOST_CHECK (barList->size () == 2);

        i = barList->begin ();
        bar1 = *i++;
        bar2 = *i;

        BOOST_CHECK (bar1 != bar2);

        BOOST_CHECK (bar1->getCity());
        BOOST_CHECK (bar1->getCity3());

        BOOST_CHECK (bar2->getCity());
        BOOST_CHECK (bar2->getCity3());

        BOOST_CHECK (bar1->getCity() == bar1->getCity3());
        BOOST_CHECK (bar2->getCity() == bar2->getCity3());

        BOOST_CHECK (bar1->getCity() != bar2->getCity ());

/****************************************************************************/

        v = cont->getBean ("listaBean2");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Ptr <BarList > > (v));

        barList = vcast <Ptr <BarList> > (v);

        BOOST_CHECK (barList->size () == 2);

        i = barList->begin ();
        bar1 = *i++;
        bar2 = *i;

        BOOST_CHECK (bar1 != bar2);

        BOOST_CHECK (bar1->getCity());
        BOOST_CHECK (bar1->getCity3());

        BOOST_CHECK (bar2->getCity());
        BOOST_CHECK (bar2->getCity3());

        BOOST_CHECK (bar1->getCity() == bar1->getCity3());
        BOOST_CHECK (bar2->getCity() == bar2->getCity3());

        BOOST_CHECK (bar1->getCity() != bar2->getCity ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test054InnerBeanParent)
{
//        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "054-inner-bean-parent.xml");
//        Variant v = cont->getBean ("listaSingleton");
//        Ptr <BarList> barList = vcast <Ptr <BarList> > (v);
//        BOOST_CHECK (barList);
}

/**
 * Testuje, czy property ustawione kilka razy (to samo) nadpisue te
 * poprzednie wywołania. Powinno zadziałać ostatnie.
 */
BOOST_AUTO_TEST_CASE (test055MapMetaOverwrite)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "055-map-meta-overwrite.xml");
        Variant vB = cont->getBean ("testTool1");
//        k202::K202Proxy *k202 = vcast <k202::K202Proxy *> (vB);
//        vB = k202->run ();
//        BOOST_CHECK (vcast <bool> (vB) == true);

        vB = cont->getBean ("parentMap");
        BOOST_CHECK_EQUAL (vcast <StringMap *> (vB)->operator[] ("a"), "Test2");


//        vB = cont->getBean ("testTool2");
//        k202 = vcast <k202::K202Proxy *> (vB);
//        vB = k202->run ();
//        BOOST_CHECK (vcast <bool> (vB) == true);

        vB = cont->getBean ("childMap");
        BOOST_CHECK_EQUAL (vcast <StringMap *> (vB)->operator[] ("a"), "Test34");
}

BOOST_AUTO_TEST_SUITE_END ();
