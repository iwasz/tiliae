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
#include "../CompactMetaService.h"
#include "Conf.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (CommonXmlTest15);

struct A03 {
        REFLECTION_CONSTRUCTOR_ (void)

        REFLECTION_METHOD (setCont)
        void setCont (BeanFactoryContainer *c) { cont = c; }

        BeanFactoryContainer *cont;

        REFLECTION_END (A03)
};

/**
 * Testuje ustawianie referencji do samego kontenera (smartPtr).
 */
BOOST_AUTO_TEST_CASE (test071ReferenceToContainerPtr)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "071-reference-to-container.xml"));

        A03 *a = vcast <A03 *> (cont->getBean ("a"));
        BOOST_REQUIRE (a);

        BeanFactoryContainer *cont2 = a->cont;
        BOOST_REQUIRE_EQUAL (cont2, cont.get ());
}

struct A04 {
        REFLECTION_CONSTRUCTOR_ (void)

        REFLECTION_METHOD (setCont)
        void setCont (BeanFactoryContainer *c) { cont = c; }

        BeanFactoryContainer *cont;

        REFLECTION_END (A04)
};

/**
 * Testuje ustawianie referencji do samego kontenera (zwykły wskaźnik BeanFactoryContainer *) - ten test się zdublował
 */
BOOST_AUTO_TEST_CASE (test072ReferenceToContainer)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "072-reference-to-container.xml"));

        A04 *a = vcast <A04 *> (cont->getBean ("a"));
        BOOST_REQUIRE (a);

        BeanFactoryContainer *cont2 = a->cont;
        BOOST_REQUIRE_EQUAL (cont2, cont.get ());
}

/**
 * Testuje referencję do singletonu, który ktoś ustawił z zewnątrz - czyli do takiego, do którego nie ma
 * definicji w XML i nie ma odpowiadającego mu BeanFactory.
 */
BOOST_AUTO_TEST_CASE (test073ReferenceToExternalSingleton)
{
        Ptr <MetaContainer> metaContainer = CompactMetaService::parseFile (PATH + "073-reference-to-external.xml");
        Ptr <BeanFactoryContainer> container = ContainerFactory::create (metaContainer);
        container->addSingleton ("external1", Core::Variant ("Benek pies"));
        container->addSingleton ("external2", Core::Variant ("Borys pies"));
        ContainerFactory::init (container.get (), metaContainer.get ());

        Core::StringMap *map = vcast <Core::StringMap *> (container->getBean ("map"));

        BOOST_REQUIRE_EQUAL (map->operator [] ("ex1"), "Benek pies");
        BOOST_REQUIRE_EQUAL (map->operator [] ("ex2"), "Borys pies");
}

struct Source {
        REFLECTION_CONSTRUCTOR_ (void)

        REFLECTION_METHOD (setCont)
        void setCont (BeanFactoryContainer *c) { cont = c; }

        BeanFactoryContainer *cont;

        REFLECTION_METHOD (init)
        void init ()
        {
                cont->addSingleton ("external1", Core::Variant ("Benek pies"));
                cont->addSingleton ("external2", Core::Variant ("Borys pies"));
        }

        REFLECTION_END (Source)
};

/**
 * Ten test nie działa, bo singletony instancjonują się w następnym kroku po sparsowaniu XML.
 * Żey zadziałał, trzebaby instancjonować kazdy singleton podczas parsowania, najszybciej jak
 * to tylko możliwe (czyli kiedy wszystkie zależności danego singletonu zostały już sparsowane).
 */
//BOOST_AUTO_TEST_CASE (test074ExternalSourceOfSingletons)
//{
//        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "074-external-source.xml");
//
//        Core::StringMap *map = vcast <Core::StringMap *> (cont->getBean ("map"));
//
//        BOOST_REQUIRE_EQUAL (map->operator [] ("ex1"), "Benek pies");
//        BOOST_REQUIRE_EQUAL (map->operator [] ("ex2"), "Borys pies");
//}

BOOST_AUTO_TEST_SUITE_END ();
