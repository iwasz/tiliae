/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#define BOOST_TEST_MODULE ContainerTest
#define BOOST_TEST_DYN_LINK
 
#include <boost/test/unit_test.hpp>

//#include "factory/VisitorFactory.h"
//#include "testHelpers/ContainerTestFactory.h"
//#include "metaVisitor/ParentVisitor.h"
//#include "metaVisitor/ReferenceVisitor.h"
//#include "metaStructure/MetaContainer.h"
//#include "../misc/OrderedVariantMap.h"

/****************************************************************************/

//using namespace Container;
//using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (VisitorTest01);
#if 0
/**
 * Testuje czy proste meta struktury zakłądają w mapie tymczaswej
 * (output map, temp map) poprawe obiekty (listy i mapy). Dla
 * MappedMeta powinna się założyć mapa, a dla IndexedMeta powinna
 * się założyć VariantList.
 */
BOOST_AUTO_TEST_CASE (testInitialMapVisitor)
{
        // Cała metastruktura.
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure01 ();
        Ptr <ValueVisitor> initV = VisitorFactory::createValueVisitor ();

        VariantMap initMap;
        initV->setOutputMap (&initMap);

        VariantMap cArgsMap;
        initV->setCArgsMap (&cArgsMap);

        // Tu sie pozaklada wszystko co trzeba.
        metaCont->accept (initV.get ());

/*--------------------------------------------------------------------------*/

        // testujemy, czy mapa sie wypelnila:
        BOOST_CHECK (initMap.size () == 1);
        BOOST_CHECK (initMap.containsKey ("syn"));

        Variant v = initMap.get ("syn");
        BOOST_CHECK (ccast <OrderedVariantMap *> (v));

/*--------------------------------------------------------------------------*/

        metaCont = ContainerTestFactory::createMetaStructure02 ();

        VariantMap initMap2;
        initV->setOutputMap (&initMap2);

        metaCont->accept (initV.get ());

/*--------------------------------------------------------------------------*/

        // testujemy, czy mapa sie wypelnila:
        BOOST_CHECK (initMap2.size () == 4);
        BOOST_CHECK (initMap2.containsKey ("syn"));
        BOOST_CHECK (initMap2.containsKey ("aska"));
        BOOST_CHECK (initMap2.containsKey ("aska2"));
        BOOST_CHECK (initMap2.containsKey ("aska3"));

        v = initMap2.get ("syn");
        BOOST_CHECK (ccast <OrderedVariantMap *> (v));

        v = initMap2.get ("aska");
        BOOST_CHECK (ccast <OrderedVariantMap *> (v));

        v = initMap2.get ("aska2");
        BOOST_CHECK (ccast <VariantList *> (v));

        v = initMap2.get ("aska3");
        BOOST_CHECK (ccast <VariantList *> (v));
}

/**
 * Ten test jest rozwinięciem poprzedniego testu (VisitorTest::testInitialMapVisitor).
 * Sprawdza, czy prosta metastruktura (jeden MappedMeta o id "syn" awierający kilka pól)
 * stworzy w mapie wynikowej (outputMap, lub tempMap) poprawny obiekt (powinno być VariantMap)
 * i czy ta wynikowa mapa zawiera poprawne elementy (powinna zawierać elementy o kluczach z
 * nazwami pól z metastruktury. Zależność powinna być 1 na 1).
 */
BOOST_AUTO_TEST_CASE (testInitialMapVisitorAdvanced1)
{
        // Meta struktura.
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure01 ();

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
        BOOST_CHECK (ccast <OrderedVariantMap *> (v));

        OrderedVariantMap *synInitial = vcast <OrderedVariantMap *> (v);
        // Ma być 2, bo nie użyliśmy serwisu parentującego, a syn ma tylko 2 pola.
        BOOST_CHECK (synInitial->size () == 2);

        // Czy obiekt wynikowy zawiera pola taki jak w metastrukturze?
        BOOST_CHECK (synInitial->containsKey ("field3"));
        BOOST_CHECK (synInitial->containsKey ("field4"));

        Variant field3 = synInitial->get ("field3");
        Variant field4 = synInitial->get ("field4");

        BOOST_CHECK (ccast <Core::String> (field3));
        BOOST_CHECK (ccast <Core::String> (field4));

        BOOST_CHECK (vcast <Core::String> (field3) == "value3");
        BOOST_CHECK (vcast <Core::String> (field4) == "value4");
}

/**
 * Ten test jest dokładnie taki sam jak poprzedni (VisitorTest::testInitialMapVisitorAdvanced1),
 * tylko metastruktuja jest odrobinę inna (ale w sumie bardzo podobna). Tutaj bean "syn" ma
 * po prostu więcej pól, więc trochę bez sensu.
 */
BOOST_AUTO_TEST_CASE (testInitialMapVisitorAdvanced2)
{
        // Meta struktura.
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure03 ();

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
        BOOST_CHECK (ccast <OrderedVariantMap *> (v));

        OrderedVariantMap *synInitial = vcast <OrderedVariantMap *> (v);

/*--------------------------------------------------------------------------*/

        BOOST_CHECK (synInitial->size () == 7);

        // Czy obiekt wynikowy zawiera pola taki jak w metastrukturze?
        BOOST_CHECK (synInitial->containsKey ("field0"));
        BOOST_CHECK (synInitial->containsKey ("field1"));
        BOOST_CHECK (synInitial->containsKey ("field2"));
        BOOST_CHECK (synInitial->containsKey ("field3"));
        BOOST_CHECK (synInitial->containsKey ("field4"));
        BOOST_CHECK (synInitial->containsKey ("field5"));
        BOOST_CHECK (synInitial->containsKey ("field6"));

        Variant field0 = synInitial->get ("field0");
        Variant field1 = synInitial->get ("field1");
        Variant field2 = synInitial->get ("field2");
        Variant field3 = synInitial->get ("field3");
        Variant field4 = synInitial->get ("field4");
        Variant field5 = synInitial->get ("field5");
        Variant field6 = synInitial->get ("field6");

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
#endif
BOOST_AUTO_TEST_SUITE_END ();
