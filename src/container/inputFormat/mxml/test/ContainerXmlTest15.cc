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

BOOST_AUTO_TEST_SUITE (ContainerXmlTest15);

struct A03 {
        REFLECTION_CONSTRUCTOR_ (void)

        REFLECTION_METHOD (setCont)
        void setCont (Ptr <BeanFactoryContainer> c) { cont = c; }

        Ptr <BeanFactoryContainer> cont;

        REFLECTION_END (A03)
};

/**
 * Testuje ustawianie referencji do samego kontenera (smartPtr).
 */
BOOST_AUTO_TEST_CASE (test071ReferenceToContainerPtr)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "071-reference-to-container.xml");

        Ptr <A03> a = vcast <Ptr <A03> > (cont->getBean ("a"));
        BOOST_REQUIRE (a);

        Ptr <BeanFactoryContainer> cont2 = a->cont;
        BOOST_REQUIRE_EQUAL (cont2, cont);
}

struct A04 {
        REFLECTION_CONSTRUCTOR_ (void)

        REFLECTION_METHOD (setCont)
        void setCont (BeanFactoryContainer *c) { cont = c; }

        BeanFactoryContainer *cont;

        REFLECTION_END (A04)
};

/**
 * Testuje ustawianie referencji do samego kontenera (zwykły wskaźnik BeanFactoryContainer *).
 */
BOOST_AUTO_TEST_CASE (test072ReferenceToContainer)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "072-reference-to-container.xml");

        Ptr <A04> a = vcast <Ptr <A04> > (cont->getBean ("a"));
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
        Ptr <MetaContainer> metaContainer = MXmlMetaService::parseFile (PATH + "073-reference-to-external.xml");
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
 *
 */
BOOST_AUTO_TEST_CASE (test074ExternalSourceOfSingletons)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "074-external-source.xml");

        Core::StringMap *map = vcast <Core::StringMap *> (cont->getBean ("map"));

        BOOST_REQUIRE_EQUAL (map->operator [] ("ex1"), "Benek pies");
        BOOST_REQUIRE_EQUAL (map->operator [] ("ex2"), "Borys pies");
}

BOOST_AUTO_TEST_SUITE_END ();
