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
#include "core/Pointer.h"
#include "testHelpers/TestHelpers.h"
#include "container/ContainerFactory.h"
#include "container/metaStructure/model/MetaStructure.h"
#include "container/common/testHelpers/ContainerTestFactory.h"
#include "common/collection/OrderedVariantMap.h"

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
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

        metaCont = ContainerTestFactory::createMetaStructure05 ();
        cont = ContainerFactory::createAndInit (metaCont);
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
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

        /*
         * Po pierwsze sprawdź, czy metaStruktura się dobrze poparentowała.
         * Sprawdz czy meta aska0, który dziedziczy z askaParent zawiera
         * pola swojego rodzica.
         */

        BOOST_CHECK_EQUAL (metaCont->getMetaMap ().size (), 5U);

        MetaObject const *syn = metaCont->get ("aska0");
        BOOST_CHECK (syn);

        DataKeyVector fields = syn->getFields ();
        BOOST_CHECK_EQUAL (fields.size (), 1U);

//        BOOST_CHECK (mSyn->getMapFields ().find ("name"));
//        BOOST_CHECK (mSyn->getMapField ("name")->getData () == "value0");

        /*
         * Udało się z parentowaniem, teraz bierzemy sie za temporaryMap i
         * sprawdzamy, czy pozakładały się tam odpowiednie obiekty (listy
         * dla indexedMeta i mapy dla mappedMeta) i czy mają ustawione dobre
         * pola i właściwe referencje do innych obiektów.
         *
         * EDIT : Już nie ma czegos takiego jak temporaryMap, tylko input jest
         * od razu ustawiany w BeanFactory.
         */

        BeanFactoryMap const &bm = cont->getBeanFactoryMap ();

        BOOST_CHECK_EQUAL (bm.size (), 5U);
        BOOST_CHECK (bm.find ("aska0") != bm.end ());
        BOOST_CHECK (bm.find ("askaParent") != bm.end ());
        BOOST_CHECK (bm.find ("aska") != bm.end ());
        BOOST_CHECK (bm.find ("aska2") != bm.end ());
        BOOST_CHECK (bm.find ("aska3") != bm.end ());

/*--------------------------------------------------------------------------*/

        Variant v;
        BeanFactory *bf = bm.find ("aska0")->second;
        BOOST_CHECK (bf);

        v = bf->getInput();
        BOOST_CHECK (ccast <OrderedVariantMap const *> (v));

        OrderedVariantMap const*aska0 = vcast <OrderedVariantMap const *> (v);

        BOOST_CHECK (aska0->size ());
        BOOST_CHECK (aska0->containsKey ("name"));
        BOOST_CHECK (ccast <std::string> (aska0->get ("name")));
        BOOST_CHECK (vcast <std::string> (aska0->get ("name")) == "value0");

/*--------------------------------------------------------------------------*/

        bf = bm.find ("aska")->second;
        BOOST_CHECK (bf);
        v = bf->getInput();
        BOOST_CHECK (ccast <OrderedVariantMap const *> (v));

        OrderedVariantMap const *aska = vcast <OrderedVariantMap const *> (v);

        BOOST_CHECK (aska->containsKey ("title"));
        BOOST_CHECK (ccast <std::string> (aska->get ("title")));
        BOOST_CHECK (vcast <std::string> (aska->get ("title")) == "value11");

        BOOST_CHECK (aska->containsKey ("body"));

/*--------------------------------------------------------------------------*/

        bf = bm.find ("aska2")->second;
        BOOST_CHECK (bf);
        v = bf->getInput();
        BOOST_CHECK (ccast <OrderedVariantMap const *> (v));

        OrderedVariantMap const *aska2 = vcast <OrderedVariantMap const *> (v);

        BOOST_CHECK (aska2->containsKey ("name"));
        BOOST_CHECK (ccast <std::string> (aska2->get ("name")));
        BOOST_CHECK (vcast <std::string> (aska2->get ("name")) == "value22");

/*--------------------------------------------------------------------------*/

        bf = bm.find ("aska3")->second;
        BOOST_CHECK (bf);
        v = bf->getInput();
        BOOST_CHECK (ccast <OrderedVariantMap const *> (v));

        OrderedVariantMap const *aska3 = vcast <OrderedVariantMap const *> (v);

        BOOST_CHECK (aska3->containsKey ("street"));
        BOOST_CHECK (ccast <std::string> (aska3->get ("street")));
        BOOST_CHECK (vcast <std::string> (aska3->get ("street")) == "value33");
}

BOOST_AUTO_TEST_SUITE_END ();
