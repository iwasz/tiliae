/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>

//#include "factory/VisitorFactory.h"
//#include "testHelpers/ContainerTestFactory.h"
//#include "metaVisitor/ParentVisitor.h"
//#include "metaVisitor/ReferenceVisitor.h"
//#include "container/metaStructure/MetaContainer.h"
//#include "misc/OrderedVariantMap.h"

/****************************************************************************/

//using namespace Container;
//using namespace Core;

BOOST_AUTO_TEST_SUITE (VisitorTest02);

/**
 * Znów zamiana prostej metastruktury na mapę wynikową outputMap, ale teraz
 * "syn" jest IndexedMeta, więc oczekujemy, że w mapie wynikowej pojawi się
 * jeden obiekt o kluczu "syn" i typie VariantList. Sprawdzamy, czy zawiera
 * takie same elementy jak ten IndexedMeta.
 */
#if 0
BOOST_AUTO_TEST_CASE (testInitialListVisitorAdvanced)
{
        // Meta struktura.
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure04 ();

        // Visitor, ktory przeprowadzi na niej operacje (odwiedzi ją).
        Ptr <ValueVisitor> initV = VisitorFactory::createValueVisitor ();

        VariantMap initMap;
        initV->setOutputMap (&initMap);

        VariantMap cArgsMap;
        initV->setCArgsMap (&cArgsMap);

        // Tu sie pozaklada wszystko co trzeba.
        metaCont->accept (initV.get ());

        // Testujemy, czy mapa sie wypelnila:
        BOOST_CHECK (initMap.size () == 1);
        BOOST_CHECK (initMap.containsKey ("syn"));

        // Czy dla beana "syn" utworzyła sie VariantMap?
        Variant v = initMap.get ("syn");
        BOOST_CHECK (ccast <VariantList *> (v));

        VariantList *synInitial = vcast <VariantList *> (v);

/*--------------------------------------------------------------------------*/

        BOOST_CHECK (synInitial->size () == 7);

        // Czy obiekt wynikowy zawiera pola taki jak w metastrukturze?
        Variant field0 = synInitial->get (0);
        Variant field1 = synInitial->get (1);
        Variant field2 = synInitial->get (2);
        Variant field3 = synInitial->get (3);
        Variant field4 = synInitial->get (4);
        Variant field5 = synInitial->get (5);
        Variant field6 = synInitial->get (6);

        BOOST_CHECK (ccast <Core::String> (field0));
        BOOST_CHECK (ccast <Core::String> (field1));
        BOOST_CHECK (ccast <int> (field2));
        BOOST_CHECK (ccast <double> (field3));
        BOOST_CHECK (ccast <char> (field4));
        BOOST_CHECK (ccast <bool> (field5));

        BOOST_CHECK (vcast <Core::String> (field0) == "value0");
        BOOST_CHECK (vcast <Core::String> (field1) == "value1");
        BOOST_CHECK (vcast <int> (field2) == 6667);
        BOOST_CHECK (vcast <double> (field3) == 123.45);
        BOOST_CHECK (vcast <char> (field4) == 'f');
        BOOST_CHECK (vcast <bool> (field5) == true);
        BOOST_CHECK (!field6.isNone ());
        BOOST_CHECK (field6.isNull ());
}

/**
 * Ten test używa nie tylko ValueVisitor jak wszystkie poprzednie, ale
 * też ReferenceVisitor, który tworzy referencje do innych obiektów.
 * Działa na mapach.
 */
BOOST_AUTO_TEST_CASE (testReferenceVisitorBasic)
{
        // Meta struktura.
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure05 ();

        // Visitor, ktory przeprowadzi na niej operacje (odwiedzi ją).
        Ptr <ValueVisitor> initV = VisitorFactory::createValueVisitor ();
        Ptr <ReferenceVisitor> refV = VisitorFactory::createReferenceVisitor ();

        VariantMap initMap;
        VariantMap cArgsMap;

        initV->setOutputMap (&initMap);
        initV->setCArgsMap (&cArgsMap);

        refV->setOutputMap (&initMap);
        refV->setCArgsMap (&cArgsMap);

        // Tu sie pozaklada wszystko co trzeba + wartosci.
        metaCont->accept (initV.get ());

        // A tu referencje i idRefy
        metaCont->accept (refV.get ());

        // Testujemy, czy mapa sie wypelnila:
        BOOST_CHECK (initMap.size () == 5);
        BOOST_CHECK (initMap.containsKey ("aska0"));
        BOOST_CHECK (initMap.containsKey ("askaParent"));
        BOOST_CHECK (initMap.containsKey ("aska"));
        BOOST_CHECK (initMap.containsKey ("aska2"));
        BOOST_CHECK (initMap.containsKey ("aska3"));

/*--------------------------------------------------------------------------*/

        Variant v = initMap.get ("aska0");
        BOOST_CHECK (ccast <OrderedVariantMap *> (v));

        OrderedVariantMap *aska0 = vcast <OrderedVariantMap *> (v);
        BOOST_CHECK (aska0->containsKey ("field0"));
        BOOST_CHECK (ccast <Core::String> (aska0->get ("field0")));
        BOOST_CHECK (vcast <Core::String> (aska0->get ("field0")) == "value0");

/*--------------------------------------------------------------------------*/

        v = initMap.get ("aska");
        BOOST_CHECK (ccast <OrderedVariantMap *> (v));

        OrderedVariantMap *aska = vcast <OrderedVariantMap *> (v);

        BOOST_CHECK (aska->containsKey ("field11"));
        BOOST_CHECK (ccast <Core::String> (aska->get ("field11")));
        BOOST_CHECK (vcast <Core::String> (aska->get ("field11")) == "value11");

        BOOST_CHECK (aska->containsKey ("field1"));
        BOOST_CHECK (ccast <OrderedVariantMap *> (aska->get ("field1")));
        BOOST_CHECK (vcast <OrderedVariantMap *> (aska->get ("field1")) == aska0);

/*--------------------------------------------------------------------------*/

        v = initMap.get ("aska2");
        BOOST_CHECK (ccast <OrderedVariantMap *> (v));

        OrderedVariantMap *aska2 = vcast <OrderedVariantMap *> (v);

        BOOST_CHECK (aska2->containsKey ("field22"));
        BOOST_CHECK (ccast <Core::String> (aska2->get ("field22")));
        BOOST_CHECK (vcast <Core::String> (aska2->get ("field22")) == "value22");

        BOOST_CHECK (aska2->containsKey ("field2"));
        BOOST_CHECK (ccast <OrderedVariantMap *> (aska2->get ("field2")));
        BOOST_CHECK (vcast <OrderedVariantMap *> (aska2->get ("field2")) == aska);

/*--------------------------------------------------------------------------*/

        v = initMap.get ("aska3");
        BOOST_CHECK (ccast <OrderedVariantMap *> (v));

        OrderedVariantMap *aska3 = vcast <OrderedVariantMap *> (v);

        BOOST_CHECK (aska3->containsKey ("field33"));
        BOOST_CHECK (ccast <Core::String> (aska3->get ("field33")));
        BOOST_CHECK (vcast <Core::String> (aska3->get ("field33")) == "value33");

        BOOST_CHECK (aska3->containsKey ("field3"));
        BOOST_CHECK (ccast <OrderedVariantMap *> (aska3->get ("field3")));
        BOOST_CHECK (vcast <OrderedVariantMap *> (aska3->get ("field3")) == aska2);
}

/**
 * Ten test używa nie tylko ValueVisitor jak wszystkie poprzednie, ale
 * też ReferenceVisitor, który tworzy referencje do innych obiektów.
 * Działa na listach.
 */
BOOST_AUTO_TEST_CASE (testReferenceVisitorBasicList)
{
        // Meta struktura.
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure06 ();

        Ptr <ValueVisitor> initV = VisitorFactory::createValueVisitor ();
        Ptr <ReferenceVisitor> refV = VisitorFactory::createReferenceVisitor ();

        VariantMap initMap;
        VariantMap cArgsMap;

        initV->setOutputMap (&initMap);
        initV->setCArgsMap (&cArgsMap);

        refV->setOutputMap (&initMap);
        refV->setCArgsMap (&cArgsMap);

        // Tu sie pozaklada wszystko co trzeba + wartosci.
        metaCont->accept (initV.get ());

        // A tu referencje i idRefy
        metaCont->accept (refV.get ());

        // Testujemy, czy mapa sie wypelnila:
        BOOST_CHECK (initMap.size () == 3);
        BOOST_CHECK (initMap.containsKey ("syn"));
        BOOST_CHECK (initMap.containsKey ("ociec"));
        BOOST_CHECK (initMap.containsKey ("dziadzio"));

/*--------------------------------------------------------------------------*/

        Variant v = initMap.get ("syn");
        BOOST_CHECK (ccast <VariantList *> (v));
        VariantList *synInitial = vcast <VariantList *> (v);
        BOOST_CHECK (synInitial->size () == 7);

/*--------------------------------------------------------------------------*/

        v = initMap.get ("dziadzio");
        BOOST_CHECK (ccast <VariantList *> (v));
        VariantList *list = vcast <VariantList *> (v);
        BOOST_CHECK (list->size () == 2);

        Variant field0 = list->get (0);
        Variant field1 = list->get (1);

        BOOST_CHECK (ccast <Core::String> (field0));
        BOOST_CHECK (ccast <VariantList *> (field1));

        BOOST_CHECK (vcast <Core::String> (field0) == "value0");
//        BOOST_CHECK (vcast <VariantList *> (field1) == "value1");

/*--------------------------------------------------------------------------*/

        v = initMap.get ("ociec");
        BOOST_CHECK (ccast <VariantList *> (v));
        list = vcast <VariantList *> (v);
        BOOST_CHECK (list->size () == 2);
        BOOST_CHECK (vcast <VariantList *> (field1) == list);

        field0 = list->get (0);
        field1 = list->get (1);

        BOOST_CHECK (ccast <Core::String> (field0));
        BOOST_CHECK (ccast <VariantList *> (field1));

        BOOST_CHECK (vcast <Core::String> (field0) == "value0");
//        BOOST_CHECK (vcast <VariantList *> (field1) == "value1");

/*--------------------------------------------------------------------------*/

        v = initMap.get ("syn");
        BOOST_CHECK (ccast <VariantList *> (v));
        list = vcast <VariantList *> (v);
        BOOST_CHECK (list->size () == 7);
        BOOST_CHECK (vcast <VariantList *> (field1) == list);
}
#endif
BOOST_AUTO_TEST_SUITE_END ();
