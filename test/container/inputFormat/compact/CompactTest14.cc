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
#include "container/inputFormat/compact/CompactMetaService.h"
#include "Conf.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (CompactXmlTest14);

/**
 * Testuje round-references, bo tak na prawdę, to sam nie wiem co się stanie.
 */
BOOST_AUTO_TEST_CASE (test066RoundReferences)
{
        BOOST_REQUIRE_THROW (ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "066-round-references.xml")), RoundReferenceException);
//        BeanFactoryContainer *cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "066-round-references.xml"));
//
//        BOOST_REQUIRE_THROW (vcast <A01c *> (cont->getBean ("a01")), RoundReferenceException);
//        BOOST_REQUIRE_THROW (vcast <A01c *> (cont->getBean ("a02")), RoundReferenceException);

//        A01c *a01 = vcast <A01c *> (cont->getBean ("a01"));
//        A02c *a02 = vcast <A02c *> (cont->getBean ("a02"));
//
//        BOOST_REQUIRE (a01);
//        BOOST_REQUIRE (a02);
//        BOOST_REQUIRE (a01->a02);
//        BOOST_REQUIRE_EQUAL (a01->a02, a02);
//        BOOST_REQUIRE_EQUAL (a02->a01, a01);
}

/**
 * Z lazy-init też powinno działać.
 */
BOOST_AUTO_TEST_CASE (test067RoundReferencesLazy)
{
        BOOST_REQUIRE_THROW (ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "067-round-references-lazy.xml")), RoundReferenceException);
//        BeanFactoryContainer *cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "067-round-references-lazy.xml"));
//
//        BOOST_REQUIRE_THROW (vcast <A01c *> (cont->getBean ("a01")), RoundReferenceException);
//        BOOST_REQUIRE_THROW (vcast <A01c *> (cont->getBean ("a02")), RoundReferenceException);

//        A01c *a01 = vcast <A01c *> (cont->getBean ("a01"));
//        A02c *a02 = vcast <A02c *> (cont->getBean ("a02"));
//
//        BOOST_REQUIRE (a01);
//        BOOST_REQUIRE (a02);
//        BOOST_REQUIRE (a01->a02);
//        BOOST_REQUIRE_EQUAL (a01->a02, a02);
//        BOOST_REQUIRE_EQUAL (a02->a01, a01);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test068RoundReferencesPrototype)
{
        BOOST_REQUIRE_THROW (ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "068-round-references-prototype.xml")), RoundReferenceException);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test069NestedParent)
{
        bool exception = false;

        try {
                BeanFactoryContainer *cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "069-parent-nested.xml"));
                cont->getBean ("a_main");
        }
        catch (Core::Exception const &e) {
                std::cerr << e.getMessage () << std::endl;
                exception = true;
        }

        BOOST_REQUIRE (!exception);
}

/**
 * Testuje, czy domyślnie tworzone są singletony (jak się w XML nie poda parametru singleton="true").
 */
BOOST_AUTO_TEST_CASE (test070DefaultSingleton)
{
        bool exception = false;

        try {
                BeanFactoryContainer *cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "001-simplest-bean.xml"));
                Core::Variant v1 = cont->getBean ("city");
                Core::Variant v2 = cont->getBean ("city");

                BOOST_REQUIRE_EQUAL (vcast <City *> (v1), vcast <City *> (v2));
        }
        catch (Core::Exception const &e) {
                std::cerr << e.getMessage () << std::endl;
                exception = true;
        }

        BOOST_REQUIRE (!exception);
}

BOOST_AUTO_TEST_SUITE_END ();
