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
#include "factory/ProxyFactory.h"
#include "container/ContainerFactory.h"
#include "container/metaStructure/model/MetaStructure.h"
#include "container/common/testHelpers/ContainerTestFactory.h"
#include "Conf.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerXmlTest05);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test021CArgsAndRefArgs)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "021-cargs-and-ref-args.xml");

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Bar *> (v));

        Bar *foo = vcast <Bar *> (v);

        BOOST_CHECK (foo->getField0 () == "value0");
        BOOST_CHECK (foo->getField1 () == "value1");

        BOOST_CHECK (foo->getCity ());
        BOOST_CHECK (foo->getCity ()->getName () == "Tokio");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test022ListWithCustomEditor)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "022-list-with-custom-editor.xml");

        Variant v = cont->getBean ("mojString");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <std::string> (v));

        std::string s = vcast <std::string> (v);
        BOOST_CHECK (s == "\"value0\",\"value1\",\"value2\",\"value3\",\"value4\"");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test023BeanWithCustomFactory)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "023-bean-with-custom-factory.xml");

        Variant v = cont->getBean ("city");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <City *> (v));

        City *a = vcast <City *> (v);

        BOOST_CHECK (a);
        BOOST_CHECK (a->getName () == "Warszawa");
}

/**
 * Używana w następnym tescie.
 */
class TestFactory : public Factory::IFactory {
public:

        virtual ~TestFactory () {}
        Core::Variant create (const Core::VariantMap &parameters, Core::DebugContext *context = NULL) const { return Core::Variant (new Core::StringMap); }
        REFLECTION_END_(TestFactory)
};

/**
 *
 */
BOOST_AUTO_TEST_CASE (test024MapAndListWithCustomFactory)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "024-map-and-list-with-custom-factory.xml");

        Variant v = cont->getBean ("myMap");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <StringMap *> (v));

        StringMap *a = vcast <StringMap *> (v);
        BOOST_CHECK (a->size () == 4);

        BOOST_CHECK (a->operator[] ("k1") == "v1");
        BOOST_CHECK (a->operator[] ("k2") == "v2");
        BOOST_CHECK (a->operator[] ("k3") == "v3");
        BOOST_CHECK (a->operator[] ("k4") == "v4");

// ---------------------
//
//        v = cont->getBean ("myList");
//        BOOST_CHECK (!v.isNone ());
//        BOOST_CHECK (ccast <StringVector *> (v));
//
//        StringVector *b = vcast <StringVector *> (v);
//        BOOST_CHECK (b->size () == 4);
//
//        BOOST_CHECK (b->operator[] (0) == "v1");
//        BOOST_CHECK (b->operator[] (1) == "v2");
//        BOOST_CHECK (b->operator[] (2) == "v3");
//        BOOST_CHECK (b->operator[] (3) == "v4");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test025ValueWithCustomEditor)
{
        Ptr <BeanFactoryContainer> cont = ContainerTestFactory::getContainer (PATH + "025-value-with-custom-editor.xml");

        Variant v = cont->getBean ("mojaMapa");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <StringMap *> (v));

        StringMap *map = vcast <StringMap *> (v);

        BOOST_CHECK (map->operator[] ("k0") == "(value1)");
        BOOST_CHECK (map->operator[] ("k1") == "(value2)");
        BOOST_CHECK (map->operator[] ("k2") == "(value3)");
}

BOOST_AUTO_TEST_SUITE_END ();
