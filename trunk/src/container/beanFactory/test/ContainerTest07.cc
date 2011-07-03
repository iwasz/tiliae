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
 *
 */
BOOST_AUTO_TEST_CASE (testMetaStructureInnerOuter)
{
//        Ptr <Container> cont = ContainerTestFactory::getContainer ();
//        BOOST_CHECK (cont);
//
//        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure23 ();
//        cont->setMetaContainer (metaCont);
//
//        cont->init ();
//
//        /*
//         * Po pierwsze sprawdź, czy metaStruktura się dobrze poparentowała.
//         * Sprawdz czy meta aska0, który dziedziczy z askaParent zawiera
//         * pola swojego rodzica.
//         */
//
//        Ptr <IMeta> syn = metaCont->get ("mainBean");
//        MappedMeta *mSyn = dynamic_cast <MappedMeta *> (syn.get ());
//        BOOST_CHECK (mSyn);
//
//        BOOST_CHECK (mSyn->getInnerMetas ().size () == 1);
//        BOOST_CHECK (mSyn->getInnerMetas ().containsKey ("city"));
}

BOOST_AUTO_TEST_SUITE_END ();
