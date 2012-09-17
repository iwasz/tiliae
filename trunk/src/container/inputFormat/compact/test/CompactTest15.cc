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

BOOST_AUTO_TEST_CASE (test074AbstractMeta)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "074-abstract-meta.xml"));
        BOOST_REQUIRE_THROW (cont->getBean ("a"), Core::Exception);
        cont->getBean ("b");
}

BOOST_AUTO_TEST_CASE (test075DependsOn)
{
        Ptr <MetaContainer> mc = CompactMetaService::parseFile (PATH + "075-depends-on.xml");
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
