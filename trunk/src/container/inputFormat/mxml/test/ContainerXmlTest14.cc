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

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerXmlTest14);

class A02;

struct A01 {
        REFLECTION_CONSTRUCTOR_ (void)
        Ptr <A02> a02;
        REFLECTION_METHOD (setA02) void setA02 (Ptr <A02> a) { a02 = a; }
        REFLECTION_END (A01)
};

struct A02 {
        REFLECTION_CONSTRUCTOR_ (void)
        Ptr <A01> a01;
        REFLECTION_METHOD (setA01) void setA01 (Ptr <A01> a) { a01 = a; }
        REFLECTION_END (A02)
};

/**
 * Testuje round-references, bo tak na prawdę, to sam nie wiem co się stanie.
 */
BOOST_AUTO_TEST_CASE (test066RoundReferences)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "066-round-references.xml");

        Ptr <A01> a01 = vcast <Ptr <A01> > (cont->getBean ("a01"));
        Ptr <A02> a02 = vcast <Ptr <A02> > (cont->getBean ("a02"));

        BOOST_REQUIRE (a01);
        BOOST_REQUIRE (a02);
        BOOST_REQUIRE (a01->a02);
        BOOST_REQUIRE_EQUAL (a01->a02, a02);
        BOOST_REQUIRE_EQUAL (a02->a01, a01);
}

/**
 * Z lazy-init też powinno działać.
 */
BOOST_AUTO_TEST_CASE (test067RoundReferencesLazy)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "067-round-references-lazy.xml");

        Ptr <A01> a01 = vcast <Ptr <A01> > (cont->getBean ("a01"));
        Ptr <A02> a02 = vcast <Ptr <A02> > (cont->getBean ("a02"));

        BOOST_REQUIRE (a01);
        BOOST_REQUIRE (a02);
        BOOST_REQUIRE (a01->a02);
        BOOST_REQUIRE_EQUAL (a01->a02, a02);
        BOOST_REQUIRE_EQUAL (a02->a01, a01);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test068RoundReferencesPrototype)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "068-round-references-prototype.xml");

        BOOST_REQUIRE_THROW (vcast <Ptr <A01> > (cont->getBean ("a01")), TooDeepNestingException);
        BOOST_REQUIRE_THROW (vcast <Ptr <A01> > (cont->getBean ("a02")), TooDeepNestingException);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test069NestedParent)
{
        bool exception = false;

        try {
                Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "069-parent-nested.xml");
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
                Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "001-simplest-bean.xml");
                Core::Variant v1 = cont->getBean ("city");
                Core::Variant v2 = cont->getBean ("city");

                BOOST_REQUIRE_EQUAL (vcast <Ptr <City> > (v1), vcast <Ptr <City> > (v2));
        }
        catch (Core::Exception const &e) {
                std::cerr << e.getMessage () << std::endl;
                exception = true;
        }

        BOOST_REQUIRE (!exception);
}

BOOST_AUTO_TEST_SUITE_END ();
