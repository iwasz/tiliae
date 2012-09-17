/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "beanWrapper/BeanWrapper.h"
#include "core/Pointer.h"
#include "testHelpers/Country.h"
#include "testHelpers/City.h"
#include "testHelpers/Address.h"
#include "core/variant/Variant.h"
#include "beanWrapper/plugins/PropertyRWBeanWrapperPlugin.h"
#include "core/DebugContext.h"

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (BWTest02);
using namespace Wrapper;
using namespace Core;
using namespace Common;

/****************************************************************************/

/**
 * Test, czy zrzucają się wyjątki tak jak trzeba.
 */
BOOST_AUTO_TEST_CASE (testExceptions)
{
        BeanWrapper *bw = BeanWrapper::create ();

        Country country;
        country.setName ("Polska");

        City city;
        city.setName ("Warszawa");

        Address address;
        address.setStreet ("katalonska");
        address.setPostalCode ("02-673");
        address.setCity (&city);
        address.setCountry (&country);

        bw->setWrappedObject (Core::Variant (&address));
        Variant vv = bw->getWrappedObject ();
        BOOST_REQUIRE (vv.isHandle ());
        Address *pa = vcast <Address *> (vv);
        BOOST_REQUIRE_EQUAL (pa, &address);

        bool err;
        bw->get ("kupaKupa", &err);
        BOOST_REQUIRE_EQUAL (err, true);

        bool success = bw->set ("kupaKupa", Core::Variant (123));
        BOOST_REQUIRE_EQUAL (success, false);

        delete bw;
}

/****************************************************************************/

/**
 * Test, czy pojawiają się poprawne informacjeo tym co poszło nie tak
 * w kontekście.
 */
BOOST_AUTO_TEST_CASE (testContext)
{
        Address address;
        BeanWrapper *bw = BeanWrapper::create (Core::Variant (&address));

        Variant vv = bw->getWrappedObject ();
        BOOST_REQUIRE (vv.isHandle());
        Address *pa = vcast <Address *> (vv);
        BOOST_REQUIRE_EQUAL (pa, &address);

        DebugContext ctx;
        bool err;
        bw->get ("kupaKupa", &err, &ctx);

        BOOST_REQUIRE (err);
        BOOST_REQUIRE (!ctx.getMessage().empty ());

        bool success = bw->set ("kupaKupa", Variant (), &ctx);

        BOOST_REQUIRE (!success);
        BOOST_REQUIRE (!ctx.getMessage().empty ());

        delete bw;
}

BOOST_AUTO_TEST_SUITE_END ();
