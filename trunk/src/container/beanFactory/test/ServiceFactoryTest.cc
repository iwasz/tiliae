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

/****************************************************************************/

using namespace Container;
using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ServiceFactoryTest);

/**
 *
 */
BOOST_AUTO_TEST_CASE (testValueService)
{
//        ValueService valueService;
//        Ptr <VariantMap> singletons = ServiceFactory::createSingletons ();
//        valueService.setSingletonMap (singletons);
//
//        Variant out = valueService.create ("text", "ala");
//        BOOST_CHECK (vcast <String> (out) == "ala");
}

BOOST_AUTO_TEST_SUITE_END ();
