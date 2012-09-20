/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <iostream>
#include "core/Pointer.h"
#include "testHelpers/TestHelpers.h"
#include "container/ContainerFactory.h"
#include "container/inputFormat/compact/CompactMetaService.h"
#include "Conf.h"
#include "container/metaStructure/model/MetaContainer.h"
#include "container/ContainerFactory.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (CompactXmlTest17);

enum Type { TYPE1, TYPE2, TYPE3 };

Core::Variant toType (std::string const &s)
{
        Type t;

        if (s == "TYPE1") {
                t = TYPE1;
        }
        else if (s == "TYPE2") {
                t = TYPE2;
        }
        else if (s == "TYPE3") {
                t = TYPE3;
        }
        else {
                throw 1;
        }

        return Core::Variant (static_cast <unsigned int> (t));
}

struct Dummy3 {

        REFLECTION_CONSTRUCTOR_ (void)
        Dummy3 () {}

        Type REFLECTION_FIELD_ENUM_INPLACE (field1);
        Type REFLECTION_FIELD_ENUM_INPLACE (field2);
        Type REFLECTION_FIELD_ENUM_INPLACE (field3);

        REFLECTION_END (Dummy3)
};

/**
 *
 */
BOOST_AUTO_TEST_CASE (test081TEnum)
{
        Ptr <MetaContainer> metaContainer = CompactMetaService::parseFile (PATH + "081-enum.xml");
        Ptr <BeanFactoryContainer> container = ContainerFactory::create (metaContainer, true);
        container->addConversion (typeid (Type), toType);
        ContainerFactory::init (container.get (), metaContainer.get ());

        Dummy3 *test1 = vcast <Dummy3 *> (container->getBean ("test1"));
        BOOST_REQUIRE_EQUAL (test1->field1, TYPE1);
        BOOST_REQUIRE_EQUAL (test1->field2, TYPE2);
        BOOST_REQUIRE_EQUAL (test1->field3, TYPE3);

        Dummy3 *test2 = vcast <Dummy3 *> (container->getBean ("test2"));
        BOOST_REQUIRE_EQUAL (test2->field1, TYPE3);
        BOOST_REQUIRE_EQUAL (test2->field2, TYPE2);
        BOOST_REQUIRE_EQUAL (test2->field3, TYPE1);

        Dummy3 *test3 = vcast <Dummy3 *> (container->getBean ("test3"));
        BOOST_REQUIRE_EQUAL (test3->field1, TYPE3);
        BOOST_REQUIRE_EQUAL (test3->field2, TYPE3);
        BOOST_REQUIRE_EQUAL (test3->field3, TYPE3);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test082ParentWithInner)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "082-parent-with-inner.xml"));
        Foo *foo1 = vcast <Foo *> (cont->getBean ("childBean1"));
        Foo *foo2 = vcast <Foo *> (cont->getBean ("childBean2"));

        BOOST_REQUIRE_NE (foo1->getCity (), foo2->getCity ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test083PropAlias)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "083-prop-alias.xml"));
        Foo *foo1 = vcast <Foo *> (cont->getBean ("childBean1"));
        Foo *foo2 = vcast <Foo *> (cont->getBean ("childBean2"));

        BOOST_REQUIRE_EQUAL (foo1->getCity ()->getName (), "Częstochowa");
        BOOST_REQUIRE_EQUAL (foo2->getCity ()->getName (), "Szczebrzeszyn");
}

BOOST_AUTO_TEST_SUITE_END ();
