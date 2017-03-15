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
#include "container/metaStructure/model/MetaContainer.h"

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/erase.hpp>
/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (CompactXmlTest16);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test076AddTo)
{
        BeanFactoryContainer *cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "076-add-to.xml"));
        Bar *bar = vcast <Bar *> (cont->getBean ("bar"));
        StringVector *vec = vcast <StringVector *> (bar->getButter ());

        BOOST_REQUIRE_EQUAL (vec->size (), 3u);
        BOOST_REQUIRE_EQUAL (vec->operator [] (0), "test1");
        BOOST_REQUIRE_EQUAL (vec->operator [] (1), "test2");
        BOOST_REQUIRE_EQUAL (vec->operator [] (2), "test3");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test077AddTo)
{
        BeanFactoryContainer *cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "077-add-to.xml"));
        Bar *bar = vcast <Bar *> (cont->getBean ("bar"));
        VariantMap *vec1 = vcast <VariantMap *> (bar->getButter ());
        VariantMap *vec2 = vcast <VariantMap *> (vec1->operator[] ("a"));
        VariantMap *vec3 = vcast <VariantMap *> (vec2->operator[] ("b"));
        StringVector *vec4 = vcast <StringVector *> (vec3->operator[] ("c"));

        BOOST_REQUIRE_EQUAL (vec4->size (), 3u);
        BOOST_REQUIRE_EQUAL (vec4->operator [] (0), "test1");
        BOOST_REQUIRE_EQUAL (vec4->operator [] (1), "test2");
        BOOST_REQUIRE_EQUAL (vec4->operator [] (2), "test3");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test078Abstract)
{
        BeanFactoryContainer *cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "078-abstract.xml"));
        BOOST_REQUIRE_THROW (cont->getBean ("bar"), Core::Exception);
}

BOOST_AUTO_TEST_CASE (test079AddToWithRef)
{
        BeanFactoryContainer *cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "079-add-to-with-ref.xml"));
        Bar *bar = vcast <Bar *> (cont->getBean ("bar"));
        VariantVector *vec = vcast <VariantVector *> (bar->getButter ());

        BOOST_REQUIRE_EQUAL (vec->size (), 3u);
        BOOST_REQUIRE (!vec->operator [] (0).isNone ());
        BOOST_REQUIRE (!vec->operator [] (1).isNone ());
        BOOST_REQUIRE (!vec->operator [] (2).isNone ());

        Bar *bar1 = vcast <Bar *> (vec->operator [] (0));
        Bar *bar2 = vcast <Bar *> (vec->operator [] (1));
        Bar *bar3 = vcast <Bar *> (vec->operator [] (2));

        BOOST_REQUIRE_NE (bar1, bar2);
        BOOST_REQUIRE_NE (bar1, bar3);
        BOOST_REQUIRE_NE (bar2, bar3);
}

BOOST_AUTO_TEST_CASE (test080AddToWithRef)
{
        BeanFactoryContainer *cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "080-add-to-with-ref.xml"));
        Dummy1 *bar = vcast <Dummy1 *> (cont->getBean ("bar"));

        BOOST_REQUIRE_EQUAL (bar->vector.size (), 5u);
        BOOST_REQUIRE (bar->vector.operator [] (0));
        BOOST_REQUIRE (bar->vector.operator [] (1));
        BOOST_REQUIRE (bar->vector.operator [] (2));
}

BOOST_AUTO_TEST_SUITE_END ();
