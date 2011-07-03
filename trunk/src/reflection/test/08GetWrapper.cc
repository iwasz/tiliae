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
#include "../wrapper/GetWrapper.h"

/*
 * Potrzebne:
 * - Klasa
 * - Konstruktor bezarg
 * - push_back / add
 * - get.
 *
 * Żeby to działało przynajmniej dla:
 * std::list, std::vector, std::map.
 *
 * 1. Zaimplementować specjalne wrappery dla pojedynczych metod list i map. Na przykład:
 */

/*
 * Z powyższego utworzy się metody i doda je do obiektu Class.
 * 2. Potrzebne specjalne adnotacje - można użyć tego co już jest w _f
 */


/*##########################################################################*/


BOOST_AUTO_TEST_SUITE (GetWrapper07);

using namespace boost;
using namespace Core;
using namespace Reflection;

/**
 *
 */
BOOST_AUTO_TEST_CASE (testGetVector)
{
        std::vector <std::string> v;
        v.push_back ("ala");
        v.push_back ("ma");
        v.push_back ("kota");

        GetWrapper <std::vector <std::string> > wrapper;

        VariantVector args;
        args.push_back (Variant (0U));
        Variant ret = wrapper.call (Variant (v), &args);
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret), "ala");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testGetList)
{
        std::list <std::string> v;
        v.push_back ("ala");
        v.push_back ("ma");
        v.push_back ("kota");

        GetWrapper <std::list <std::string> > wrapper;

        VariantVector args;
        args.push_back (Variant (0U));
        Variant ret = wrapper.call (Variant (v), &args);
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret), "ala");

        args.clear ();
        args.push_back (Variant (1U));
        ret = wrapper.call (Variant (v), &args);
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret), "ma");

        args.clear ();
        args.push_back (Variant (2U));
        ret = wrapper.call (Variant (v), &args);
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret), "kota");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testGetMap)
{
        std::map <std::string, int> m;
        m["ala"] = 3;
        m["ma"] = 4;
        m["kota"] = 5;

        GetWrapper <std::map <std::string, int> > wrapper;

        VariantVector args;
        args.push_back (Variant ("ala"));
        Variant ret = wrapper.call (Variant (m), &args);
        BOOST_REQUIRE_EQUAL (vcast <int> (ret), 3);

        args.clear ();
        args.push_back (Variant ("ma"));
        ret = wrapper.call (Variant (m), &args);
        BOOST_REQUIRE_EQUAL (vcast <int> (ret), 4);

        args.clear ();
        args.push_back (Variant ("kota"));
        ret = wrapper.call (Variant (m), &args);
        BOOST_REQUIRE_EQUAL (vcast <int> (ret), 5);
}

BOOST_AUTO_TEST_CASE (testGetSet)
{
        std::set <std::string> v;
        v.insert ("ala");
        v.insert ("ma");
        v.insert ("kota");

        GetWrapper <std::set <std::string> > wrapper;

        VariantVector args;
        args.push_back (Variant ("ala"));
        Variant ret = wrapper.call (Variant (v), &args);
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret), "ala");

        args.clear ();
        args.push_back (Variant ("ma"));
        ret = wrapper.call (Variant (v), &args);
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret), "ma");

        args.clear ();
        args.push_back (Variant ("kota"));
        ret = wrapper.call (Variant (v), &args);
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret), "kota");
}

BOOST_AUTO_TEST_SUITE_END ();
