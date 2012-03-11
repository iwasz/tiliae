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

BOOST_AUTO_TEST_SUITE (ContainerTest07);

/**
 * Przypadek testowy błędu, który pojawił się w bajce.
 */
BOOST_AUTO_TEST_CASE (testParentsOrder)
{
/*------Meta struktura------------------------------------------------------*/

        Ptr <MetaContainer> metaCont = MetaContainer::create ();

        Ptr <MappedMeta> meta = boost::make_shared <MappedMeta> ();
        meta->setId ("a_main");
        meta->setScope (IMeta::SINGLETON);
        meta->setParent ("y_par");
        metaCont->add (meta);

        meta = boost::make_shared <MappedMeta> ();
        meta->setId ("x_parent");
        meta->setClass ("City");
        meta->setScope (IMeta::SINGLETON);
        meta->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
        metaCont->add (meta);

        meta = boost::make_shared <MappedMeta> ();
        meta->setId ("y_par");
        meta->setScope (IMeta::SINGLETON);
        meta->setParent ("x_parent");
        metaCont->add (meta);

/*------Kontener------------------------------------------------------------*/

        try {
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createContainer (metaCont);

/*------Testy---------------------------------------------------------------*/


        Variant v = cont->getBean ("a_main");
        BOOST_CHECK (!v.isNone ());
        }
        catch (Core::Exception const &e) {
                std::cerr << e.getMessage () << std::endl;
        }
//        BOOST_CHECK (ccast <City *> (v));
}

BOOST_AUTO_TEST_SUITE_END ();
