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

#include "Reflection.h"
#include "Core.h"
#include "../../testHelpers/Address.h"
#include "../../testHelpers/City.h"
#include "../../testHelpers/Country.h"

BOOST_AUTO_TEST_SUITE (ClassTest);

using namespace boost;
using namespace Core;
using namespace Reflection;

/**
 * Probuje podbrac metode o zadanej nazwie z obiektu i wywołać ją.
 */
BOOST_AUTO_TEST_CASE (testGetClassForName)
{
        Ptr <Class> cls = Manager::classForName ("Address");
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
        Ptr <Class> cls = Manager::classForName ("Address");
        BOOST_REQUIRE (cls);

        ClassList list = cls->getBaseClassList();
        BOOST_REQUIRE_EQUAL (list.size (), 1);

        Ptr <Class> cls2 = list.front ();
        BOOST_REQUIRE_EQUAL (cls2->getName (), "Place");
}

namespace A {

        struct Testowa {
                e__ (Testowa)
        };

}

namespace B {

        struct Testowa {
//                __ne (B::Testowa, BTestowa)
                e__ (B::Testowa)
        };

}

namespace C {

        struct Testowa {
//                __ne (C::Testowa, CTestowa)
                e__ (C::Testowa)
        };

}

namespace D {

        struct Testowa {
                c__ (void)
                m_ (f) void f () {}
                e_ (D::Testowa)
        };

}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testTwoClasesSameName)
{
        Ptr <Class> cls = Manager::classForType (typeid (A::Testowa));
        BOOST_REQUIRE (cls);

        Ptr <Class> cls2 = Manager::classForType (typeid (B::Testowa));
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

namespace E {

        struct Testowa01 {
                d__
                e_ (Testowa01)
        };

        struct Testowa02 {
                d__
                virtual ~Testowa02 () {}

                m_ (f) virtual void f () = 0;

                e_ (Testowa02)
        };

        struct Testowa03 : public Testowa02 {
                c__ (void)
                b_ ("Testowa02")

                virtual ~Testowa03 () {}

                virtual void f () {}
                m_ (g) virtual void g () {}

                e_ (Testowa03)
        };

        struct Testowa04 : public Testowa03 {
                c__ (void)
                b_ ("Testowa03")

                virtual ~Testowa04 () {}

                m_ (h) virtual void h () {}

                e_ (Testowa04)
        };

}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testVirtualClass)
{
        {
                Ptr <Class> cls = Manager::classForType (typeid (E::Testowa01));
                BOOST_REQUIRE (cls);

                cls = Manager::classForName ("Testowa01");
                BOOST_REQUIRE (cls);
        }

/*--------------------------------------------------------------------------*/

        {
                Ptr <Class> cls = Manager::classForType (typeid (E::Testowa02));
                BOOST_REQUIRE (cls);

                cls = Manager::classForName ("Testowa02");
                BOOST_REQUIRE (cls);

                Ptr<Method> met1 = cls->getMethod ("f", 0);
                BOOST_REQUIRE (met1);
        }

/*--------------------------------------------------------------------------*/

        {
                Ptr <Class> cls = Manager::classForType (typeid (E::Testowa03));
                BOOST_REQUIRE (cls);

                cls = Manager::classForName ("Testowa03");
                BOOST_REQUIRE (cls);

                Ptr<Method> met1 = cls->getMethod ("f", 0);
                BOOST_REQUIRE (met1);

                met1 = cls->getMethod ("g", 0);
                BOOST_REQUIRE (met1);
        }

/*--------------------------------------------------------------------------*/

        {
                Ptr <Class> cls = Manager::classForType (typeid (E::Testowa04));
                BOOST_REQUIRE (cls);

                cls = Manager::classForName ("Testowa04");
                BOOST_REQUIRE (cls);

                Ptr<Method> met1 = cls->getMethod ("f", 0);
                BOOST_REQUIRE (met1);

                met1 = cls->getMethod ("g", 0);
                BOOST_REQUIRE (met1);

                met1 = cls->getMethod ("h", 0);
                BOOST_REQUIRE (met1);
        }
}

/*##########################################################################*/

namespace F {

        template <typename T>
        struct Template {

                c__ (void)

                virtual ~Template () {}

                m_ (f) virtual void f () {}

        private:

                T t;

                e_ (Template<int>)
        };

/*--------------------------------------------------------------------------*/

        template <typename T>
        struct Template01 {

                c__ (void)

                virtual ~Template01 () {}

                m_ (setT) void setT (const T &t) { this->t = t; }
                m_ (getT) const T &getT () const { return t; }

                T t;

                e_ (Template01<int>)
        };

/*--------------------------------------------------------------------------*/

#if 1
        template <typename T>
        struct Template02 {

                c__ (void)

                virtual ~Template02 () {}

                m_ (setT) void setT (const T &t) { this->t = t; }
                m_ (getT) const T &getT () const { return t; }

                T t;

                tb_
                t_ (Template02<int>)
                t_ (Template02<double>)
                te_
        };
#endif
}

#if 1
/**
 *
 */
BOOST_AUTO_TEST_CASE (testTemplateClass)
{
        {
                Ptr <Class> cls;
                cls = Manager::classForType (typeid (F::Template<int>));
                BOOST_REQUIRE (cls);

                cls = Manager::classForName ("Template<int>");
                BOOST_REQUIRE (cls);
        }

/*--------------------------------------------------------------------------*/

        {
                Ptr <Class> cls;
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
                Ptr <Class> cls;
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
                Ptr <Class> cls;
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
