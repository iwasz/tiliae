/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <boost/any.hpp>
#include <vector>

#include "core/Pointer.h"
#include "reflection/model/Class.h"
#include "reflection/Manager.h"
#include "testHelpers/XClass.h"

/*##########################################################################*/


BOOST_AUTO_TEST_SUITE (Field13);

using namespace boost;
using namespace Core;
using namespace Reflection;

/**
 *
 */
BOOST_AUTO_TEST_CASE (testGet)
{
        X testClass;
        Variant vo (&testClass);

        Class *cls = Manager::classForName ("X");
        BOOST_REQUIRE (cls);

        Field *f = cls->getField ("d");
        BOOST_REQUIRE (f);
        BOOST_REQUIRE_EQUAL (vcast <double> (f->get (vo)), 1.2);

        f = cls->getField ("s");
        BOOST_REQUIRE (f);
        BOOST_REQUIRE_EQUAL (vcast <std::string> (f->get (vo)), "franio");

        f = cls->getField ("niemapola");
        BOOST_REQUIRE (!f);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testSet)
{
        X testClass;
        Variant vo (&testClass);

        Class *cls = Manager::classForName ("X");
        BOOST_REQUIRE (cls);

        Field *f = cls->getField ("d");
        BOOST_REQUIRE (f);
        f->set (vo, Variant (2345.56));
        BOOST_REQUIRE_EQUAL (testClass.d, 2345.56);

        f = cls->getField ("s");
        BOOST_REQUIRE (f);
        f->set (vo, Variant ("Asiunia"));
        BOOST_REQUIRE_EQUAL (testClass.s, "Asiunia");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testSetAndGetReferenceAnnotation)
{
        X testClass;
        Variant vo (&testClass);

        Class *cls = Manager::classForName ("X");
        BOOST_REQUIRE (cls);

        Field *f = cls->getField ("x0");
        BOOST_REQUIRE (f);
        Variant ret = f->get (vo);
        BOOST_REQUIRE (!ret.isNone ());
        BOOST_REQUIRE_EQUAL (vcast <X0 *> (ret), testClass.getX0 ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testPolymorphic)
{
        Y y;
        IY *py = &y;
        Variant vo (py);

        Y2 y2;
        IY *py2 = &y2;

        Class *cls = Manager::classForName ("Y");
        BOOST_REQUIRE (cls);

        Field *f = cls->getField ("y");
        BOOST_REQUIRE (f);

        f->set (vo, Variant (py2));
        BOOST_REQUIRE_EQUAL (py2, y.getY ());

        Variant ret = f->get (vo);
        BOOST_REQUIRE_EQUAL (py2, vcast <Y2 *> (ret));
}

BOOST_AUTO_TEST_SUITE_END ();
