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

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (CompactXmlTest15);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test071TopologicalSort)
{
        Ptr <MetaContainer> m = CompactMetaService::parseFile (PATH + "071-topological-sort.xml");
        std::cerr << *m << std::endl;

        MetaDeque sorted = m->topologicalSort ();
        std::cerr << sorted << std::endl;
}


BOOST_AUTO_TEST_SUITE_END ();
