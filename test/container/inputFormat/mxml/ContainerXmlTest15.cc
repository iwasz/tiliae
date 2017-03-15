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

#include "Conf.h"
#include "container/ContainerFactory.h"
#include "container/inputFormat/mxml/MXmlMetaService.h"
#include "container/metaStructure/model/MetaStructure.h"
#include "container/testHelpers/ContainerTestFactory.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerXmlTest15);

/**
 * Testuje ustawianie referencji do samego kontenera (smartPtr).
 */
BOOST_AUTO_TEST_CASE (test071ReferenceToContainerPtr)
{
        BeanFactoryContainer *cont = ContainerTestFactory::getContainer (PATH + "071-reference-to-container.xml");

        A03 *a = vcast<A03 *> (cont->getBean ("a"));
        BOOST_REQUIRE (a);

        BeanFactoryContainer *cont2 = a->cont;
        BOOST_REQUIRE_EQUAL (cont2, cont);
}

/**
 * Testuje ustawianie referencji do samego kontenera (zwykły wskaźnik BeanFactoryContainer *) - ten test się zdublował
 */
BOOST_AUTO_TEST_CASE (test072ReferenceToContainer)
{
        BeanFactoryContainer *cont = ContainerTestFactory::getContainer (PATH + "072-reference-to-container.xml");

        A04 *a = vcast<A04 *> (cont->getBean ("a"));
        BOOST_REQUIRE (a);

        BeanFactoryContainer *cont2 = a->cont;
        BOOST_REQUIRE_EQUAL (cont2, cont);
}

/**
 * Testuje referencję do singletonu, który ktoś ustawił z zewnątrz - czyli do takiego, do którego nie ma
 * definicji w XML i nie ma odpowiadającego mu BeanFactory.
 */
BOOST_AUTO_TEST_CASE (test073ReferenceToExternalSingleton)
{
        Ptr<MetaContainer> metaContainer = MXmlMetaService::parseFile (PATH + "073-reference-to-external.xml");
        BeanFactoryContainer *container = ContainerFactory::create (metaContainer);
        container->addSingleton ("external1", Core::Variant ("Benek pies"));
        container->addSingleton ("external2", Core::Variant ("Borys pies"));
        ContainerFactory::init (container, metaContainer.get ());

        Core::StringMap *map = vcast<Core::StringMap *> (container->getBean ("map"));

        BOOST_REQUIRE_EQUAL (map->operator[] ("ex1"), "Benek pies");
        BOOST_REQUIRE_EQUAL (map->operator[] ("ex2"), "Borys pies");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test074ExternalSourceOfSingletons)
{
        BeanFactoryContainer *cont = ContainerTestFactory::getContainer (PATH + "074-external-source.xml");

        Core::StringMap *map = vcast<Core::StringMap *> (cont->getBean ("map"));

        BOOST_REQUIRE_EQUAL (map->operator[] ("ex1"), "Benek pies");
        BOOST_REQUIRE_EQUAL (map->operator[] ("ex2"), "Borys pies");
}

BOOST_AUTO_TEST_CASE (test075DependsOn)
{
        Ptr<MetaContainer> mc = MXmlMetaService::parseFile (PATH + "075-depends-on.xml");
        MetaDeque sorted = mc->topologicalSort ();

        MetaDeque::const_iterator i = sorted.begin ();
        MetaObject const *cur = *i++;

        BOOST_REQUIRE_EQUAL (std::string (cur->getId ()), "a");
        BOOST_CHECK_EQUAL (cur->getDependsOn ().size (), 0U);
        cur = *i++;

        BOOST_REQUIRE_EQUAL (std::string (cur->getId ()), "b");
        BOOST_REQUIRE_EQUAL (cur->getDependsOn ().size (), 1U);
        cur = *i++;

        BOOST_REQUIRE_EQUAL (std::string (cur->getId ()), "c");
        BOOST_REQUIRE_EQUAL (cur->getDependsOn ().size (), 2U);
        cur = *i++;

        BOOST_REQUIRE_EQUAL (std::string (cur->getId ()), "d");
        BOOST_REQUIRE_EQUAL (cur->getDependsOn ().size (), 3U);
        cur = *i++;

        BOOST_REQUIRE_EQUAL (std::string (cur->getId ()), "e");
        BOOST_REQUIRE_EQUAL (cur->getDependsOn ().size (), 4U);

        Core::StringVector v = cur->getDependsOn ();
        Core::StringVector::const_iterator j = v.begin ();
        BOOST_CHECK_EQUAL (*j++, "a");
        BOOST_CHECK_EQUAL (*j++, "b");
        BOOST_CHECK_EQUAL (*j++, "c");
        BOOST_CHECK_EQUAL (*j, "d");
}

BOOST_AUTO_TEST_SUITE_END ();
