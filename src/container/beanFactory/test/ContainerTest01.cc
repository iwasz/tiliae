/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <iostream>
#include <Pointer.h>
#include <TestHelpers.h>
#include "ContainerFactory.h"
#include "metaStructure/model/MetaStructure.h"
#include "common/testHelpers/ContainerTestFactory.h"
#include "../../../common/collection/OrderedVariantMap.h"

/****************************************************************************/

using namespace Container;
using namespace Core;
using Common::OrderedVariantMap;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerTest01);

// To nawet działało (dla niektórych przypadków) ale stacktrace i tak był z boost::test a nie z miejsca zrzucenia.

//void my_exception1_translator (Core::Exception e)
//{
//    BOOST_TEST_MESSAGE( "Caught my_exception1" );
//    std::cerr << "Core::Exception : [" << e.getMessage() << "]" << std::endl;
//    abort ();
//}
//
//boost::unit_test::test_suite*
//init_unit_test_suite( int /*argc*/, char* /*argv*/[] ) {
//
//        boost::unit_test::test_suite* test = BOOST_TEST_SUITE("ContainerTest01");
//        boost::unit_test::unit_test_monitor.register_exception_translator<Core::Exception> (&my_exception1_translator);
//        return test;
//}

/**
 * Sprawdza jedynie czy dziala tworzenie kontenera (za pomocą
 * fabryki) i czy się samo z siebie nie wywali i czy kontener
 * nie jest null. Dosyć głupi test, który właściwie pokazuje
 * jak używać API kontenera.
 */
BOOST_AUTO_TEST_CASE (testCreateContainer)
{
//        boost::unit_test::unit_test_monitor.register_exception_translator<Core::Exception> (&my_exception1_translator);

        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure26 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createContainer (metaCont);

        metaCont = ContainerTestFactory::createMetaStructure05 ();
        cont = ContainerFactory::createContainer (metaCont);
        // Jeśli do tej pory się nie wywaliło, to test jest OK i test uważamy za zaliczony.
}

/**
 * Ten test jest rozwinięciem ContainerTest::testCreateContainer, to znaczy jest
 * tworzona prosta metastruktrura (zawierająca kilka MappedMeta), jest dziedziczenie,
 * proste wartosci (value) i referencje. Sprawdzamy, czy utworzyłyu się odpowiednie
 * obiekty w mapie temporary.
 */
BOOST_AUTO_TEST_CASE (testSimpleMetaStructure)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure05 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createContainer (metaCont);

        /*
         * Po pierwsze sprawdź, czy metaStruktura się dobrze poparentowała.
         * Sprawdz czy meta aska0, który dziedziczy z askaParent zawiera
         * pola swojego rodzica.
         */

        IMeta *syn = metaCont->get ("aska0");
        MappedMeta *mSyn = dynamic_cast <MappedMeta *> (syn);
        BOOST_CHECK (mSyn);

        BOOST_CHECK (mSyn->getField ("field0"));
        BOOST_CHECK (mSyn->getField ("field0")->getData () == "value0");

        BOOST_CHECK (mSyn->getField ("field00"));
        BOOST_CHECK (mSyn->getField ("field00")->getData () == "value00");

        /*
         * Udało się z parentowaniem, teraz bierzemy sie za temporaryMap i
         * sprawdzamy, czy pozakładały się tam odpowiednie obiekty (listy
         * dla indexedMeta i mapy dla mappedMeta) i czy mają ustawione dobre
         * pola i właściwe referencje do innych obiektów.
         *
         * EDIT : Już nie ma czegos takiego jak temporaryMap, tylko input jest
         * od razu ustawiany w BeanFactory.
         */

        Ptr <BeanFactoryMap> bm = cont->getBeanFactoryMap ();

        BOOST_CHECK (bm->size () == 5);
        BOOST_CHECK (bm->find ("aska0") != bm->end ());
        BOOST_CHECK (bm->find ("askaParent") != bm->end ());
        BOOST_CHECK (bm->find ("aska") != bm->end ());
        BOOST_CHECK (bm->find ("aska2") != bm->end ());
        BOOST_CHECK (bm->find ("aska3") != bm->end ());

/*--------------------------------------------------------------------------*/

        Variant v;
        Ptr <BeanFactory> bf = *(bm->get<0>().find ("aska0"));
        BOOST_CHECK (bf);

        v = bf->getInput();
        BOOST_CHECK (ccast <OrderedVariantMap const *> (v));

        OrderedVariantMap const*aska0 = vcast <OrderedVariantMap const *> (v);

        BOOST_CHECK (aska0->size ());
        BOOST_CHECK (aska0->containsKey ("field0"));
        BOOST_CHECK (ccast <Core::String> (aska0->get ("field0")));
        BOOST_CHECK (vcast <Core::String> (aska0->get ("field0")) == "value0");

/*--------------------------------------------------------------------------*/

        bf = *(bm->get<0>().find ("aska"));
        BOOST_CHECK (bf);
        v = bf->getInput();
        BOOST_CHECK (ccast <OrderedVariantMap const *> (v));

        OrderedVariantMap const *aska = vcast <OrderedVariantMap const *> (v);

        BOOST_CHECK (aska->containsKey ("field11"));
        BOOST_CHECK (ccast <Core::String> (aska->get ("field11")));
        BOOST_CHECK (vcast <Core::String> (aska->get ("field11")) == "value11");

        BOOST_CHECK (aska->containsKey ("field1"));

/*--------------------------------------------------------------------------*/

        bf = *(bm->get<0>().find ("aska2"));
        BOOST_CHECK (bf);
        v = bf->getInput();
        BOOST_CHECK (ccast <OrderedVariantMap const *> (v));

        OrderedVariantMap const *aska2 = vcast <OrderedVariantMap const *> (v);

        BOOST_CHECK (aska2->containsKey ("field22"));
        BOOST_CHECK (ccast <Core::String> (aska2->get ("field22")));
        BOOST_CHECK (vcast <Core::String> (aska2->get ("field22")) == "value22");

        BOOST_CHECK (aska2->containsKey ("field2"));

/*--------------------------------------------------------------------------*/

        bf = *(bm->get<0>().find ("aska3"));
        BOOST_CHECK (bf);
        v = bf->getInput();
        BOOST_CHECK (ccast <OrderedVariantMap const *> (v));

        OrderedVariantMap const *aska3 = vcast <OrderedVariantMap const *> (v);

        BOOST_CHECK (aska3->containsKey ("field33"));
        BOOST_CHECK (ccast <Core::String> (aska3->get ("field33")));
        BOOST_CHECK (vcast <Core::String> (aska3->get ("field33")) == "value33");

        BOOST_CHECK (aska3->containsKey ("field3"));

/****************************************************************************/

/*
 * Musiałem zakomentowac, bo meta mają poustawiane głupie pola.
 * Na przykład dla klasy City pole field00 etc. W następnym teście
 * pola są właściwe i testuje się już getBean.
 */

//        v = cont->getBean ("aska0");
//        BOOST_CHECK (!v.isNone ());
//        BOOST_CHECK (ccast <City *> (v));
//
//        v = cont->getBean ("aska");
//        BOOST_CHECK (!v.isNone ());
//        BOOST_CHECK (ccast <Note *> (v));
//
//        v = cont->getBean ("aska2");
//        BOOST_CHECK (!v.isNone ());
//        BOOST_CHECK (ccast <Country *> (v));
//
//        v = cont->getBean ("aska3");
//        BOOST_CHECK (!v.isNone ());
//        BOOST_CHECK (ccast <Address *> (v));
}

BOOST_AUTO_TEST_SUITE_END ();
