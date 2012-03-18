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
#include <TestHelpers.h>
#include "../MXmlMetaService.h"
#include "Conf.h"
#include "../../../ContainerFactory.h"
#include "../../../metaStructure/model/MetaContainer.h"
#include "../../../beanFactory/BeanFactory.h"

/****************************************************************************/

using namespace Core;
using namespace Container;
using namespace boost::unit_test;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (MXmlTest01);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test001SimplestBean)
{
        try {
                Ptr <MetaContainer> metaContainer = boost::make_shared <MetaContainer> ();
                MXmlMetaService mService;
                mService.parse (PATH + "001-simplest-bean.xml", metaContainer.get ());

//                std::cout << metaContainer->getMetaMap ().size () << std::endl;

                Ptr <BeanFactoryContainer> beanContainer = ContainerFactory::createContainer (metaContainer);
                Variant v = beanContainer->getBean ("city");

                BOOST_REQUIRE (!v.isNone ());

        }
        catch (Core::Exception const &e) {
                std::cerr << e.getMessage () << std::endl;
        }
}

BOOST_AUTO_TEST_SUITE_END ();
