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
 * Przypadek testowy błędu, który pojawił się w bajce. Problem dotyczył wielokrotnego dziedziczenia, kiedy
 * rodziców było więcej niż 1. Czyli A <- B <- C. Bład pojawiał się przy konkretnym układzie ID tych 3 beanów.
 * Zostało to poprawione w ten sposób, ze ParentingService nie kopiuje danych z parent meta do child meta,
 * tylko podlinkowuje jeden do drugich. Powinno to też zmniejszyć zużycie pamięci.
 */
BOOST_AUTO_TEST_CASE (testParentsOrder)
{
/*------Meta struktura------------------------------------------------------*/

        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

        MappedMeta *meta = new MappedMeta ();
        meta->setId ("a_main");
        meta->setScope (IMeta::SINGLETON);
        meta->setParent ("y_par");
        metaCont->add (meta);

        meta = new MappedMeta ();
        meta->setId ("x_parent");
        meta->setClass ("City");
        meta->setScope (IMeta::SINGLETON);
        meta->addField (DataKey ("name", new ValueData ("Warszawa", "String")));
        metaCont->add (meta);

        meta = new MappedMeta ();
        meta->setId ("y_par");
        meta->setScope (IMeta::SINGLETON);
        meta->setParent ("x_parent");
        metaCont->add (meta);

/*------Kontener------------------------------------------------------------*/

        bool exception = false;

        try {
                Ptr <BeanFactoryContainer> cont = ContainerFactory::createContainer (metaCont);

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
