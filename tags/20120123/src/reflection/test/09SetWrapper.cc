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

#include "../../core/Pointer.h"
#include "../wrapper/ICallableWrapper.h"
#include "../wrapper/MethodWrapper.h"
#include "../wrapper/SetWrapper.h"

/*##########################################################################*/

BOOST_AUTO_TEST_SUITE (SetWrapper09);

using namespace boost;
using namespace Core;
using namespace Reflection;

/**
 *
 */
BOOST_AUTO_TEST_CASE (testSetVector)
{
        std::vector <std::string> v (10);
        SetWrapper <std::vector <std::string> > wrapper;


        VariantVector args;
        args.push_back (Variant (0U));
        args.push_back (Variant ("ala"));
        Variant ret = wrapper.call (Variant (&v), &args);
        BOOST_REQUIRE_EQUAL (v[0], "ala");

        args.clear ();
        args.push_back (Variant (1U));
        args.push_back (Variant ("ma"));
        ret = wrapper.call (Variant (&v), &args);
        BOOST_REQUIRE_EQUAL (v[1], "ma");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testSetList)
{
        std::list <std::string> v (10);
        SetWrapper <std::list <std::string> > wrapper;


        VariantVector args;
        args.push_back (Variant (0U));
        args.push_back (Variant ("ala"));
        Variant ret = wrapper.call (Variant (&v), &args);
        BOOST_REQUIRE_EQUAL (v.front (), "ala");

        args.clear ();
        args.push_back (Variant (1U));
        args.push_back (Variant ("ma"));
        ret = wrapper.call (Variant (&v), &args);
        std::list <std::string>::iterator i = v.begin ();
        ++i;
        BOOST_REQUIRE_EQUAL (*i, "ma");
}

BOOST_AUTO_TEST_CASE (testSetMap)
{
        std::map <std::string, int>v;
        SetWrapper <std::map <std::string, int> > wrapper;

        VariantVector args;
        args.push_back (Variant ("ala"));
        args.push_back (Variant (667));
        Variant ret = wrapper.call (Variant (&v), &args);
        BOOST_REQUIRE_EQUAL (v["ala"], 667);

        args.clear ();
        args.push_back (Variant ("ma"));
        args.push_back (Variant (666));
        ret = wrapper.call (Variant (&v), &args);
        BOOST_REQUIRE_EQUAL (v["ma"], 666);
}

BOOST_AUTO_TEST_SUITE_END ();
