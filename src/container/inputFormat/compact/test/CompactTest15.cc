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

        MetaMap &mm = const_cast <MetaMap &> (m->getMetaMap ());
        BOOST_CHECK_EQUAL (mm.size (), 9U);

        BOOST_CHECK (mm.find ("a") != mm.end ());
        BOOST_CHECK (mm["a"]);

        BOOST_CHECK (m->get ("a"));
        BOOST_CHECK (m->get ("b"));
        BOOST_CHECK (m->get ("c"));
}

BOOST_AUTO_TEST_CASE (test072TopologicalSort)
{
        Ptr <MetaContainer> m = CompactMetaService::parseFile (PATH + "071-topological-sort.xml");
//        std::cerr << *m << std::endl;

        MetaDeque sorted = m->topologicalSort ();
        BOOST_CHECK_EQUAL (sorted.size (), 9U);
//        std::cerr << sorted << std::endl;
}

struct Dummy {

        REFLECTION_CONSTRUCTOR_ (void)
        Dummy () {}

        REFLECTION_CONSTRUCTOR (Dummy *)
        Dummy (Dummy *d) : field1 (d) {}

        Dummy *REFLECTION_FIELD_VALUE_INPLACE (field1);
        Dummy *REFLECTION_FIELD_VALUE_INPLACE (field2);
        Dummy *REFLECTION_FIELD_VALUE_INPLACE (field3);

        REFLECTION_END (Dummy)
};

BOOST_AUTO_TEST_CASE (test073TopologicalSort)
{
        Ptr <MetaContainer> m = CompactMetaService::parseFile (PATH + "073-topological-sort.xml");
//        std::cerr << *m << std::endl;

        MetaDeque sorted = m->topologicalSort ();
//        std::cerr << sorted << std::endl;
}

BOOST_AUTO_TEST_SUITE_END ();
