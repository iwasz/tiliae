/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>

#include <iostream>
#include "core/Pointer.h"

#include "container/ContainerFactory.h"
#include "container/metaStructure/model/MetaStructure.h"
#include "container/testHelpers/ContainerTestFactory.h"
#include "container/inputFormat/compact/CompactMetaService.h"
#include "Conf.h"
#include "testHelpers/TestHelpers.h"
#include "editor/ListToStringEditor.h"

/****************************************************************************/

using namespace Core;
using namespace Container;
using namespace boost::unit_test;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (CompactXmlTest01);

BOOST_AUTO_TEST_CASE (test001SimplestBeanFirst)
{
        try {
                Ptr <BeanFactoryContainer> beanContainer = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "001-simplest-bean.xml"));
                Variant v = beanContainer->getBean ("city");

                BOOST_REQUIRE (!v.isNone ());
        }
        catch (Core::Exception const &e) {
                std::cerr << e.getMessage () << std::endl;
        }
}

BOOST_AUTO_TEST_CASE (test001SimplestBean)
{
        Ptr <BeanFactoryContainer> beanContainer = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "002-simplest-bean-value-string.xml"));

        City *c = vcast <City *> (beanContainer->getBean ("city1"));
        BOOST_REQUIRE_EQUAL (c->getName (), "Warszawa");

        c = vcast <City *> (beanContainer->getBean ("city3"));
        BOOST_REQUIRE_EQUAL (c->getName (), "Paris france a b c");
}

BOOST_AUTO_TEST_CASE (test003SimplestBeanValueText)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "003-simplest-bean-value-text.xml"));

        Variant vB = cont->getBean ("city");
        BOOST_CHECK (ccast <City *> (vB));

        City *cit = vcast <City *> (vB);
        BOOST_CHECK (cit);
        BOOST_CHECK (cit->getName () == "Warszawa");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test004SimplestBeanValueEmpty)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "004-simplest-bean-value-empty.xml"));

        Variant vB = cont->getBean ("city");
        BOOST_CHECK (ccast <City *> (vB));

        City *cit = vcast <City *> (vB);
        BOOST_CHECK (cit);
        BOOST_CHECK_EQUAL (cit->getName (), "");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test005LittleBitMoreComplicatedBean)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "005-little-more-complicated-bean.xml"));

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Foo *> (v));

        Foo *foo = vcast <Foo *> (v);

        BOOST_CHECK (foo->getField0 () == "value0");
        BOOST_CHECK (foo->getField1 () == "value1");
        BOOST_CHECK (foo->getField2 () == 6678);
        BOOST_CHECK (foo->getField3 () == 12.34);
        BOOST_CHECK (foo->getField4 () == 'g');
        BOOST_CHECK (foo->getField5 () == true);
        BOOST_CHECK (foo->getField6 () == 0);
}

BOOST_AUTO_TEST_SUITE_END ();
