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
#include "reflection/wrapper/ICallableWrapper.h"
#include "reflection/wrapper/MethodWrapper.h"
#include "reflection/wrapper/AddWrapper.h"

/*##########################################################################*/

BOOST_AUTO_TEST_SUITE (AddWrapper10);

using namespace boost;
using namespace Core;
using namespace Reflection;

/**
 *
 */
BOOST_AUTO_TEST_CASE (testAddVector)
{
        std::vector <std::string> v;
        AddWrapper <std::vector <std::string> > wrapper;

        VariantVector args;
        args.push_back (Variant ("ala"));
        Variant ret = wrapper.call (Variant (&v), &args);
        BOOST_REQUIRE_EQUAL (v[0], "ala");

        args.clear ();
        args.push_back (Variant ("ma"));
        ret = wrapper.call (Variant (&v), &args);
        BOOST_REQUIRE_EQUAL (v[1], "ma");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testAddList)
{
        std::list <std::string> v;
        AddWrapper <std::list <std::string> > wrapper;

        VariantVector args;
        args.push_back (Variant ("ala"));
        Variant ret = wrapper.call (Variant (&v), &args);
        BOOST_REQUIRE_EQUAL (v.front (), "ala");

        args.clear ();
        args.push_back (Variant ("ma"));
        ret = wrapper.call (Variant (&v), &args);
        std::list <std::string>::iterator i = v.begin ();
        ++i;
        BOOST_REQUIRE_EQUAL (*i, "ma");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testAddSet)
{
        std::set <std::string>v;
        AddWrapper <std::set <std::string> > wrapper;

        VariantVector args;
        args.push_back (Variant ("ala"));
        Variant ret = wrapper.call (Variant (&v), &args);
        BOOST_REQUIRE (v.count ("ala"));

        args.clear ();
        args.push_back (Variant ("ma"));
        ret = wrapper.call (Variant (&v), &args);
        BOOST_REQUIRE (v.count ("ma"));
}

BOOST_AUTO_TEST_SUITE_END ();
