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

        return Core::Variant (static_cast <unsigned int> (t));
}

struct Dummy3 {

        REFLECTION_CONSTRUCTOR_ (void)
        Dummy3 () {}

        REFLECTION_CONSTRUCTOR (Dummy3 *)
        Dummy3 (Dummy3 *d) : field1 (d) {}

        Dummy3 *REFLECTION_FIELD_VALUE_INPLACE (field1);
        Dummy3 *REFLECTION_FIELD_VALUE_INPLACE (field2);
        Dummy3 *REFLECTION_FIELD_VALUE_INPLACE (field3);

        REFLECTION_END (Dummy3)
};

/**
 *
 */
BOOST_AUTO_TEST_CASE (test081TEnum)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit ();


        Ptr <MetaContainer> metaContainer = CompactMetaService::parseFile (PATH + "076-add-to.xml")
        Ptr <BeanFactoryContainer> container = ContainerFactory::create (metaContainer, true);
        container->addConversion (typeid (Geometry::Point), Geometry::stringToPointVariant);
        container->addConversion (typeid (Geometry::LineString), Geometry::stringToLineStringVariant);
        ContainerFactory::init (container.get (), metaContainer.get ());

        container->addConversion (typeid (Geometry::Point), Geometry::stringToPointVariant);

}


BOOST_AUTO_TEST_SUITE_END ();
