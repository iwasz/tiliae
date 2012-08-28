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
#include "metaStructure/model/MetaContainer.h"

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
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "076-add-to.xml"));
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
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "077-add-to.xml"));
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

BOOST_AUTO_TEST_SUITE_END ();
