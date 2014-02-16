/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/assign/std/vector.hpp> // for 'operator+=()'
#include <boost/assign/std/list.hpp>
#include <boost/assert.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <utility>
#include "core/Iterator.h"
#include "core/Pointer.h"
#include "core/variant/Cast.h"

BOOST_AUTO_TEST_SUITE (IterTest09);

using namespace boost;
using namespace Core;
using namespace boost::assign;

/**
 *
 */
BOOST_AUTO_TEST_CASE (testVector)
{
        std::vector <int> v;
        v += 6,7,8,9,10,11,12;

        BOOST_REQUIRE_EQUAL (v.size (), 7U);

        Ptr <IIterator> i = std::make_shared <TIterator<std::vector <int> > > (v.begin (), v.end ());

        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 6);
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 7);
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 8);
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 9);
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 10);
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 11);
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 12);
        BOOST_REQUIRE (!i->hasNext ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testList)
{
        std::list <int> l;
        l += 6,7,8,9,10,11,12;

        BOOST_REQUIRE_EQUAL (l.size (), 7U);

        Ptr <IIterator> i = std::make_shared <TIterator<std::list <int> > > (l.begin (), l.end ());

        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 6);
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 7);
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 8);
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 9);
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 10);
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 11);
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <int> (i->next ()), 12);
        BOOST_REQUIRE (!i->hasNext ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testMap)
{
        std::map <std::string, int> m;
        m["a"] = 1;
        m["b"] = 2;
        m["c"] = 3;

        Ptr <IIterator> i = std::make_shared <TIterator<std::map <std::string, int> > > (m.begin (), m.end ());

        BOOST_REQUIRE (i->hasNext ());
        std::pair <std::string const, int> p = vcast <std::pair <std::string const, int> > (i->next ());
        BOOST_REQUIRE_EQUAL (p.first, "a");
        BOOST_REQUIRE_EQUAL (p.second, 1);

        BOOST_REQUIRE (i->hasNext ());
        std::pair <std::string const, int> p2 = vcast <std::pair <std::string const, int> > (i->next ());
        BOOST_REQUIRE_EQUAL (p2.first, "b");
        BOOST_REQUIRE_EQUAL (p2.second, 2);

        BOOST_REQUIRE (i->hasNext ());
        std::pair <std::string const, int> p3 = vcast <std::pair <std::string const, int> > (i->next ());
        BOOST_REQUIRE_EQUAL (p3.first, "c");
        BOOST_REQUIRE_EQUAL (p3.second, 3);

        BOOST_REQUIRE (!i->hasNext ());
}

BOOST_AUTO_TEST_SUITE_END ();
