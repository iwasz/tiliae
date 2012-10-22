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
#include "container/common/testHelpers/ContainerTestFactory.h"
#include "Conf.h"
#include "container/inputFormat/mxml/MXmlMetaService.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerXmlTest13);

/**
 * Testuje linked containers - testuje refy. Ten test jest bardziej zaawansowany niż
 * ten 62, ale nie chciało mi się zmieniać nazw XMLi.
 */
BOOST_AUTO_TEST_CASE (test061LinkedContainers)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (MXmlMetaService::parseFile (PATH + "061-linked-01.xml"), true);

        std::string b1 = vcast <std::string> (cont->getBean ("bean1"));

        Ptr <BeanFactoryContainer> cont2 = ContainerFactory::createAndInit (MXmlMetaService::parseFile (PATH + "061-linked-02.xml"), false, cont.get ());

        StringList *list = vcast <StringList *> (cont2->getBean ("bean2"));
        BOOST_CHECK (list);
        BOOST_CHECK_EQUAL (list->size (), 1U);
}

/**
 * Testuje linked containers - to jest takie coś, że tworzy się główny kontener, i potem
 * drugi, który może korzystać z definicji z tego pierwszego. To jest potrzebne do ładowania
 * plików w różnych momentach działania programu. Pewna baza ładuje się na początku, a potem
 * sukcesywnie można dogrywać następne części (ale dopiero gdy są potrzebne - w przeciwieństwie
 * do mechanizmu import).
 *
 * Testuje w nich parentowanie (do tego jest potrzebny tylko metaCOntainer).
 */
BOOST_AUTO_TEST_CASE (test062LinkedContainers)
{
        // Stwórz kontener i umieść w nim jego meta-kontener.
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (MXmlMetaService::parseFile (PATH + "062-linked-01.xml"), true);

        Address *b1 = vcast <Address *> (cont->getBean ("bean1"));
        BOOST_CHECK (b1);
        BOOST_CHECK_EQUAL (b1->getPostalCode(), "KodPocztowy");
        BOOST_CHECK_EQUAL (b1->getStreet(), "Ulica");

        Address *b3 = vcast <Address *> (cont->getBean ("bean3"));
        BOOST_CHECK (b3);
        BOOST_CHECK_EQUAL (b3->getPostalCode(), "KodPocztowy");
        BOOST_CHECK_EQUAL (b3->getStreet(), "Ulica");
        BOOST_CHECK_EQUAL (b3->getString(), "Napis");

        // Utwórz podlinkowany kontener. Nie zapamiętuj jego metaKontenera (nie będziemy do niego linkowac nic).
        Ptr <BeanFactoryContainer> cont2 = ContainerFactory::createAndInit (MXmlMetaService::parseFile (PATH + "062-linked-02.xml"), false, cont.get ());

        Address *b4 = vcast <Address *> (cont2->getBean ("bean4"));
        BOOST_CHECK (b4);
        BOOST_CHECK_EQUAL (b4->getPostalCode(), "KodPocztowy4");
        BOOST_CHECK_EQUAL (b4->getStreet(), "Ulica4");

        Address *b2 = vcast <Address *> (cont2->getBean ("bean2"));
        BOOST_CHECK (b2);
        BOOST_CHECK_EQUAL (b2->getPostalCode(), "KodPocztowy");
        BOOST_CHECK_EQUAL (b2->getStreet(), "Ulica");
        BOOST_CHECK_EQUAL (b2->getString(), "Napis");
}

/**
 * Testuje instancjonowanie singletonów nie lazy-init. Patrz komentarze w funkcji co
 * się dzieje po kolei.
 */
BOOST_AUTO_TEST_CASE (test063SingletonInit)
{
        // Poniżej init uruchamia się w place i place2 (2)
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "063-singleton-init.xml");

        // place jest singletonem (lazy-init==false) i jest już utworzone, więc init się nie wywołuje.
        Place *p = vcast <Place *> (cont->getBean ("place"));

        /*
         * Jeżeli instancjonowanie nie działa, to nie wywołuje też metody init. Wówczas poniższe
         * wywołanie powinno zwrócić 1 i wyrzucić błąd. Wobec tego to jest 3cie uruchomienie funkcji
         * init (3).
         */
        BOOST_CHECK_EQUAL (p->init (), 3);

        /*
         * place2 jest singletonem i ma lazy-init = false, więc już init się wywołało na początku. Wobec
         * tego teraz jest 4-rte wywołanie.
         */
        p = vcast <Place *> (cont->getBean ("place2"));
        BOOST_CHECK_EQUAL (p->init (), 4);

        /*
         * place3 jest singletonem, ale ma lazy-init == true, czyli jest tworzone przy PIERWSZYM pobraniu.
         * Czyli teraz (5):
         */
        p = vcast <Place *> (cont->getBean ("place3"));

        // Czyli to jest 6ste wywołanie:
        BOOST_CHECK_EQUAL (p->init (), 6);
}

typedef std::vector <int> IntVector;
REFLECTION_COLLECTION (IntVector)

/**
 *
 */
BOOST_AUTO_TEST_CASE (test064ListWithConversion)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "064-list-with-conversion.xml");

        Variant v = cont->getBean ("mojaLista");
        BOOST_CHECK (!v.isNone ());

        IntVector *list = vcast <IntVector *> (v);

        BOOST_CHECK_EQUAL (list->size (), 4U);

        BOOST_CHECK_EQUAL (list->operator[] (0), 123);
        BOOST_CHECK_EQUAL (list->operator[] (1), 234);
        BOOST_CHECK_EQUAL (list->operator[] (2), 345);
        BOOST_CHECK_EQUAL (list->operator[] (3), 456);
}

/**
 * Bean z konwersją.
 */
BOOST_AUTO_TEST_CASE (test065BeanWithConversion)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "065-bean-with-conversion.xml");

        Variant v = cont->getBean ("foo");
        BOOST_CHECK (!v.isNone ());

        Foo *foo = vcast <Foo *> (v);

        BOOST_CHECK (foo->getCity ());
        BOOST_CHECK_EQUAL (foo->getCity ()->getName (), "Warszawa");

        BOOST_CHECK (foo->getCity2 ());
        BOOST_CHECK_EQUAL (foo->getCity2 ()->getName (), "Tokio");
}

BOOST_AUTO_TEST_SUITE_END ();
