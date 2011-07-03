/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../../common/Context.h"
#include "../../core/Exception.h"


BOOST_AUTO_TEST_SUITE (ContextTest);

using namespace Common;


BOOST_AUTO_TEST_CASE (testListHelper)
{
        Context c;
        Context *context = &c;

        fatal (context, Core::Exception, UNDEFINED_ERROR, "message");

#if defined (TILIAE_DEBUG)
        BOOST_REQUIRE_EQUAL (c.getMessage(), "1. FATAL: message");
#else
        BOOST_REQUIRE_EQUAL (c.getMessage(), "1");
#endif
}

BOOST_AUTO_TEST_SUITE_END ();
