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
#include "container/metaStructure/model/MetaStructure.h"
#include "container/common/testHelpers/ContainerTestFactory.h"
#include "container/metaStructure/model/MetaFactory.h"

/****************************************************************************/

using namespace Container;
using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerTest07);

/**
 * Przypadek testowy błędu, który pojawił się w bajce. Problem dotyczył wielokrotnego dziedziczenia, kiedy
 * rodziców było więcej niż 1. Czyli A <- B <- C. Bład pojawiał się przy konkretnym układzie ID tych 3 beanów.
 * Zostało to poprawione w ten sposób, ze ParentingService nie kopiuje danych z parent meta do child meta,
 * tylko podlinkowuje jeden do drugich. Powinno to też zmniejszyć zużycie pamięci.
 */
BOOST_AUTO_TEST_CASE (testParentsOrder)
{
/*------Meta struktura------------------------------------------------------*/

        Ptr <MetaContainer> metaCont = std::make_shared <MetaContainer> ();
        MetaFactory factory (metaCont->getMemoryAllocator ());

        MetaObject *meta = factory.newMetaObject ();
        meta->setId ("a_main");
        meta->setScope (MetaObject::SINGLETON);
        meta->setParent ("y_par");
        metaCont->add (meta);

        meta = factory.newMetaObject ();
        meta->setId ("x_parent");
        meta->setClass ("City");
        meta->setScope (MetaObject::SINGLETON);
        meta->addMapField (factory.newDataKey ("name", factory.newValueDataNewString ("Warszawa", "String")));
        metaCont->add (meta);

        meta = factory.newMetaObject ();
        meta->setId ("y_par");
        meta->setScope (MetaObject::SINGLETON);
        meta->setParent ("x_parent");
        metaCont->add (meta);

/*------Kontener------------------------------------------------------------*/

        bool exception = false;

        try {
                Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/*------Testy---------------------------------------------------------------*/


                Variant v = cont->getBean ("a_main");
                BOOST_CHECK (!v.isNone ());
        }
        catch (Core::Exception const &e) {
                std::cerr << e.getMessage () << std::endl;
                exception = true;
        }

        BOOST_REQUIRE (!exception);
}

BOOST_AUTO_TEST_SUITE_END ();
