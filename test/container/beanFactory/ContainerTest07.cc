/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>

#include "core/Pointer.h"
#include "testHelpers/TestHelpers.h"
#include <iostream>

#include "container/ContainerFactory.h"
#include "container/metaStructure/model/MetaFactory.h"
#include "container/metaStructure/model/MetaStructure.h"
#include "container/testHelpers/ContainerTestFactory.h"

/****************************************************************************/

using namespace Container;
using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerTest07);

/**
 * Przypadek testowy błędu, który pojawił się w bajce. Problem dotyczył wielokrotnego dziedziczenia, kiedy
 * rodziców było więcej niż 1. Czyli A <- B <- C. Bład pojawiał się przy konkretnym układzie ID tych 3 beanów.
 * Zostało to poprawione w ten sposób, ze ParentingService nie kopiuje danych z parent meta do child meta,
 * tylko podlinkowuje jeden do drugich. Powinno to też zmniejszyć zużycie pamięci.
 */
BOOST_AUTO_TEST_CASE (testParentsOrder)
{
        /*------Meta struktura------------------------------------------------------*/

        Ptr<MetaContainer> metaCont = std::make_shared<MetaContainer> ();
        MetaFactory factory (metaCont->getMemoryAllocator ());

        MetaObject *meta = factory.newMetaObject ();
        meta->setId ("a_main");
        meta->setScope (MetaObject::SINGLETON);
        meta->setParent ("y_par");
        metaCont->add (meta);

        meta = factory.newMetaObject ();
        meta->setId ("x_parent");
        meta->setClass ("City");
        meta->setScope (MetaObject::SINGLETON);
        meta->addMapField (factory.newDataKey ("name", factory.newValueDataNewString ("Warszawa", "String")));
        metaCont->add (meta);

        meta = factory.newMetaObject ();
        meta->setId ("y_par");
        meta->setScope (MetaObject::SINGLETON);
        meta->setParent ("x_parent");
        metaCont->add (meta);

        /*------Kontener------------------------------------------------------------*/

        bool exception = false;

        try {
                BeanFactoryContainer *cont = ContainerFactory::createAndInit (metaCont);

                /*------Testy---------------------------------------------------------------*/

                Variant v = cont->getBean ("a_main");
                BOOST_CHECK (!v.isNone ());
        }
        catch (Core::Exception const &e) {
                std::cerr << e.getMessage () << std::endl;
                exception = true;
        }

        BOOST_REQUIRE (!exception);
}

/**
 * Test globalnej init-metody. Pierwszeństwo ma metoda skonfigurowana bezpośrednio w beanie za pomocą
 * atrybutu init-method w XML. Jeśli nie jest konfigurowana, system patrzy czy podano globalInitMethod
 * w tagu <beans> (atrybut init-method dla <beans>). Jeśli tak, to próbue ją odpalić dla każdego beana,
 * ale jesli jej nie ma, to nie zgłasza błędu.
 */
BOOST_AUTO_TEST_CASE (testGlobalInitMethod)
{
        /*------Meta struktura------------------------------------------------------*/

        Ptr<MetaContainer> metaCont = std::make_shared<MetaContainer> ();
        metaCont->setGlobalInitMethod ("init");
        MetaFactory factory (metaCont->getMemoryAllocator ());

        MetaObject *meta = factory.newMetaObject ();
        meta->setId ("bean");
        meta->setClass ("City");
        meta->setScope (MetaObject::SINGLETON);
        meta->addMapField (factory.newDataKey ("name", factory.newValueDataNewString ("Warszawa", "String")));
        metaCont->add (meta);

        /*------Kontener------------------------------------------------------------*/

        BeanFactoryContainer *cont = ContainerFactory::createAndInit (metaCont);

        /*------Testy---------------------------------------------------------------*/

        Variant v = cont->getBean ("bean");
        BOOST_CHECK (!v.isNone ());

        City *c = vcast<City *> (v);
        BOOST_CHECK_EQUAL (c->getName (), "Warszawa_INIT");

        delete cont;
}

/**
 * Testowanie zachowania gdy global init method jest wadliwa (zrzuca wyjątek). Proram
 * powinien zrzucić ładny wyjątek też.
 */
BOOST_AUTO_TEST_CASE (testFaultyGlobalInitMethod)
{
        /*------Meta struktura------------------------------------------------------*/

        Ptr<MetaContainer> metaCont = std::make_shared<MetaContainer> ();
        metaCont->setGlobalInitMethod ("initThrow");
        MetaFactory factory (metaCont->getMemoryAllocator ());

        MetaObject *meta = factory.newMetaObject ();
        meta->setId ("bean");
        meta->setClass ("City");
        meta->setScope (MetaObject::SINGLETON);
        meta->addMapField (factory.newDataKey ("name", factory.newValueDataNewString ("Warszawa", "String")));
        metaCont->add (meta);

        /*------Kontener------------------------------------------------------------*/

        BOOST_CHECK_THROW (ContainerFactory::createAndInit (metaCont), Core::Exception);

        /*------Testy---------------------------------------------------------------*/
}

/**
 * Jeśli ustawiono globalną metodę init-method (w tagu <beans>), to kazdy bean jest
 * testowany pod kątem występowania tej metody i jesli system ją znajdzie, to ją wywołuje.
 * Natomiast jesli jej nie znajdzie, to nic się nie powinno stać i to testuje ten test.
 */
BOOST_AUTO_TEST_CASE (testNoInitMethodFound)
{
        /*------Meta struktura------------------------------------------------------*/

        Ptr<MetaContainer> metaCont = std::make_shared<MetaContainer> ();
        metaCont->setGlobalInitMethod ("initAaaaa");
        MetaFactory factory (metaCont->getMemoryAllocator ());

        MetaObject *meta = factory.newMetaObject ();
        meta->setId ("bean");
        meta->setClass ("City");
        meta->setScope (MetaObject::SINGLETON);
        meta->addMapField (factory.newDataKey ("name", factory.newValueDataNewString ("Warszawa", "String")));
        metaCont->add (meta);

        /*------Kontener------------------------------------------------------------*/

        BOOST_REQUIRE_NO_THROW (ContainerFactory::createAndInit (metaCont));
        BeanFactoryContainer *cont = ContainerFactory::createAndInit (metaCont);

        /*------Testy---------------------------------------------------------------*/

        Variant v = cont->getBean ("bean");
        BOOST_CHECK (!v.isNone ());

        City *c = vcast<City *> (v);
        BOOST_CHECK_EQUAL (c->getName (), "Warszawa");
}

/**
 * Za pomocą id-aware-method ustawia się metodę, która jest wywoływana dla kazdego stworzonego beana
 * (gdy jej nie ma, to nie szkodzi, nei bedzie błędu). Ta metda jest uruchamiana i dostaje jeden
 * argument typu std::string z ID danego beana.
 */
BOOST_AUTO_TEST_CASE (testGlobalIdAwareMethod)
{
        /*------Meta struktura------------------------------------------------------*/

        Ptr<MetaContainer> metaCont = std::make_shared<MetaContainer> ();
        metaCont->setGlobalIdAwareMethod ("setName");
        MetaFactory factory (metaCont->getMemoryAllocator ());

        MetaObject *meta = factory.newMetaObject ();
        meta->setId ("beanWwa");
        meta->setClass ("City");
        meta->setScope (MetaObject::SINGLETON);
        metaCont->add (meta);

        /*------Kontener------------------------------------------------------------*/

        BeanFactoryContainer *cont = ContainerFactory::createAndInit (metaCont);

        /*------Testy---------------------------------------------------------------*/

        Variant v = cont->getBean ("beanWwa");
        BOOST_CHECK (!v.isNone ());

        City *c = vcast<City *> (v);
        BOOST_CHECK_EQUAL (c->getName (), "beanWwa");
}

/**
 * Testuje co się stanie, gdy bean nie ma metody ustawionej w setGlobalIdAwareMethod. Powinno przejść
 * bez żadnego błędu.
 */
BOOST_AUTO_TEST_CASE (testGlobalIdAwareMethodNonExistent)
{
        /*------Meta struktura------------------------------------------------------*/

        Ptr<MetaContainer> metaCont = std::make_shared<MetaContainer> ();
        metaCont->setGlobalIdAwareMethod ("setNameAaaa");
        MetaFactory factory (metaCont->getMemoryAllocator ());

        MetaObject *meta = factory.newMetaObject ();
        meta->setId ("bean");
        meta->setClass ("City");
        meta->setScope (MetaObject::SINGLETON);
        meta->addMapField (factory.newDataKey ("name", factory.newValueDataNewString ("Warszawa", "String")));
        metaCont->add (meta);

        /*------Kontener------------------------------------------------------------*/

        BOOST_REQUIRE_NO_THROW (ContainerFactory::createAndInit (metaCont));
        BeanFactoryContainer *cont = ContainerFactory::createAndInit (metaCont);

        /*------Testy---------------------------------------------------------------*/

        Variant v = cont->getBean ("bean");
        BOOST_CHECK (!v.isNone ());

        City *c = vcast<City *> (v);
        BOOST_CHECK_EQUAL (c->getName (), "Warszawa");
}

BOOST_AUTO_TEST_SUITE_END ();
