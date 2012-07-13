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
#include <Pointer.h>

#include "ContainerFactory.h"
#include "metaStructure/model/MetaStructure.h"
#include "common/testHelpers/ContainerTestFactory.h"
#include "../CompactMetaService.h"
#include "Conf.h"
#include "../../../../testHelpers/City.h"

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
//        Ptr <BeanFactoryContainer> beanContainer = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "002-simplest-bean-value-string.xml"));
//
//        Ptr <City> c = vcast <Ptr <City> > (beanContainer->getBean ("city1"));
//        BOOST_REQUIRE_EQUAL (c->getName (), "Warszawa");
//
//        c = vcast <Ptr <City> > (beanContainer->getBean ("city2"));
//        BOOST_REQUIRE_EQUAL (c->getName (), "Kraków");
//
//        c = vcast <Ptr <City> > (beanContainer->getBean ("city3"));
//        BOOST_REQUIRE_EQUAL (c->getName (), "Paris");
}


BOOST_AUTO_TEST_SUITE_END ();
