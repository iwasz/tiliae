/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "reflection/Reflection.h"
#include "core/Core.h"
#include "testHelpers/TestHelpers"

BOOST_AUTO_TEST_SUITE (ClassTest);

using namespace boost;
using namespace Core;
using namespace Reflection;

/**
 * Probuje podbrac metode o zadanej nazwie z obiektu i wywołać ją.
 */
BOOST_AUTO_TEST_CASE (testGetClassForName)
{
        Class *cls = Manager::classForName ("Address");
#if 0
        std::cerr << Manager::instance().toString() << std::endl;
#endif
        BOOST_REQUIRE (cls);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testBaseClassTest)
{
        Class *cls = Manager::classForName ("Address");
        BOOST_REQUIRE (cls);

        ClassList list = cls->getBaseClassList();
        BOOST_REQUIRE_EQUAL (list.size (), 1U);

        Class *cls2 = list.front ();
        BOOST_REQUIRE_EQUAL (cls2->getName (), "Place");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testTwoClasesSameName)
{
        Class *cls = Manager::classForType (typeid (A::Testowa));
        BOOST_REQUIRE (cls);

        Class *cls2 = Manager::classForType (typeid (B::Testowa));
        BOOST_REQUIRE (cls2);

        BOOST_REQUIRE (cls != cls2);

        cls = Manager::classForName ("Testowa");
        BOOST_REQUIRE (cls);

        cls2 = Manager::classForName ("B::Testowa");
        BOOST_REQUIRE (cls2);

        cls2 = Manager::classForName ("C::Testowa");
        BOOST_REQUIRE (cls2);

        cls2 = Manager::classForName ("D::Testowa");
        BOOST_REQUIRE (cls2);

        BOOST_REQUIRE (cls != cls2);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testVirtualClass)
{
        {
                Class *cls = Manager::classForType (typeid (E::Testowa01));
                BOOST_REQUIRE (cls);

                cls = Manager::classForName ("Testowa01");
                BOOST_REQUIRE (cls);
        }

/*--------------------------------------------------------------------------*/

        {
                Class *cls = Manager::classForType (typeid (E::Testowa02));
                BOOST_REQUIRE (cls);

                cls = Manager::classForName ("Testowa02");
                BOOST_REQUIRE (cls);

                Method *met1 = cls->getMethod ("f", 0);
                BOOST_REQUIRE (met1);
        }

/*--------------------------------------------------------------------------*/

        {
                Class *cls = Manager::classForType (typeid (E::Testowa03));
                BOOST_REQUIRE (cls);

                cls = Manager::classForName ("Testowa03");
                BOOST_REQUIRE (cls);

                Method *met1 = cls->getMethod ("f", 0);
                BOOST_REQUIRE (met1);

                E::Testowa03 t;
                BOOST_REQUIRE_NO_THROW (met1->invoke (Variant (&t)));

                met1 = cls->getMethod ("g", 0);
                BOOST_REQUIRE (met1);

                BOOST_REQUIRE_NO_THROW (met1->invoke (Variant (&t)));
        }

/*--------------------------------------------------------------------------*/

        {
                Class *cls = Manager::classForType (typeid (E::Testowa04));
                BOOST_REQUIRE (cls);

                cls = Manager::classForName ("Testowa04");
                BOOST_REQUIRE (cls);

                Method *met1 = cls->getMethod ("f", 0);
                BOOST_REQUIRE (met1);

                E::Testowa04 t;
                BOOST_REQUIRE_NO_THROW (met1->invoke (Variant (&t)));

                met1 = cls->getMethod ("g", 0);
                BOOST_REQUIRE (met1);
                BOOST_REQUIRE_NO_THROW (met1->invoke (Variant (&t)));

                met1 = cls->getMethod ("h", 0);
                BOOST_REQUIRE (met1);
                BOOST_REQUIRE_NO_THROW (met1->invoke (Variant (&t)));
        }
}

/*##########################################################################*/

#if 0
/**
 *
 */
BOOST_AUTO_TEST_CASE (testTemplateClass)
{
        {
                Class *cls;
                cls = Manager::classForType (typeid (F::Template<int>));
                BOOST_REQUIRE (cls);

                cls = Manager::classForName ("Template<int>");
                BOOST_REQUIRE (cls);
        }

/*--------------------------------------------------------------------------*/

        {
                Class *cls;
                cls = Manager::classForType (typeid (F::Template01<int>));
                BOOST_REQUIRE (cls);

                cls = Manager::classForName ("Template01<int>");
                BOOST_REQUIRE (cls);

                Ptr<Method> get = cls->getMethod ("getT", 0);
                BOOST_REQUIRE (get);

                Ptr<Method> set = cls->getMethod ("setT", 1);
                BOOST_REQUIRE (set);

                F::Template01<int> tmpl;
                VariantVector params;
                params.push_back (Variant (667));
                Variant ret1 = set->invoke (Core::Variant (&tmpl), &params);

                BOOST_REQUIRE_EQUAL (tmpl.t, 667);

                ret1 = get->invoke (Core::Variant (&tmpl));
                BOOST_REQUIRE_EQUAL (vcast <int> (ret1), 667);
        }

/*##########################################################################*/

        {
                Class *cls;
                cls = Manager::classForType (typeid (F::Template02<int>));
                BOOST_REQUIRE (cls);

                cls = Manager::classForName ("Template02<int>");
                BOOST_REQUIRE (cls);

                Ptr<Method> get = cls->getMethod ("getT", 0);
                BOOST_REQUIRE (get);

                Ptr<Method> set = cls->getMethod ("setT", 1);
                BOOST_REQUIRE (set);

                F::Template02<int> tmpl;
                VariantVector params;
                params.push_back (Variant (667));
                Variant ret1 = set->invoke (Core::Variant (&tmpl), &params);

                BOOST_REQUIRE_EQUAL (tmpl.t, 667);

                ret1 = get->invoke (Core::Variant (&tmpl));
                BOOST_REQUIRE_EQUAL (vcast <int> (ret1), 667);
        }

/*--------------------------------------------------------------------------*/

        {
                Class *cls;
                cls = Manager::classForType (typeid (F::Template02<double>));
                BOOST_REQUIRE (cls);

                cls = Manager::classForName ("Template02<double>");
                BOOST_REQUIRE (cls);

                Ptr<Method> get = cls->getMethod ("getT", 0);
                BOOST_REQUIRE (get);

                Ptr<Method> set = cls->getMethod ("setT", 1);
                BOOST_REQUIRE (set);

                F::Template02<double> tmpl;
                VariantVector params;
                params.push_back (Variant (667.8));
                Variant ret1 = set->invoke (Core::Variant (&tmpl), &params);

                BOOST_REQUIRE_EQUAL (tmpl.t, 667.8);

                ret1 = get->invoke (Core::Variant (&tmpl));
                BOOST_REQUIRE_EQUAL (vcast <double> (ret1), 667.8);
        }
}
#endif

BOOST_AUTO_TEST_SUITE_END ();
