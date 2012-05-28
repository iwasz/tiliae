/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../../core/DebugContext.h"
#include "../../core/Exception.h"


BOOST_AUTO_TEST_SUITE (ContextTest);

using namespace Core;


BOOST_AUTO_TEST_CASE (testListHelper)
{
        DebugContext c;
        DebugContext *context = &c;

        dcError (context, "message");

#if defined (TILIAE_DEBUG)
        BOOST_REQUIRE_EQUAL (c.getMessage(), "message");
#else
        BOOST_REQUIRE_EQUAL (c.getMessage(), "1");
#endif
}

BOOST_AUTO_TEST_SUITE_END ();
