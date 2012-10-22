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
#include "core/variant/Cast.h"
#include "testHelpers/Address.h"
#include "testHelpers/City.h"
#include "testHelpers/Country.h"

BOOST_AUTO_TEST_SUITE (MethodTest);

using namespace boost;
using namespace Core;
using namespace Reflection;

/**
 * Probuje podbrac metode o zadanej nazwie z obiektu i wywołać ją.
 */
BOOST_AUTO_TEST_CASE (testGetMethod)
{
        Class *cls = Manager::classForName ("Address");
        BOOST_REQUIRE (cls);
        BOOST_REQUIRE_EQUAL (cls->getName (), "Address");

        BOOST_REQUIRE_EQUAL (12u, cls->getMethodList ().size ());

        Method *met1 = cls->getMethod ("getStreet", 0);
        Method *met2 = cls->getMethod ("getPostalCode", 0);

        BOOST_REQUIRE (met1);
        BOOST_REQUIRE (met2);

        Address a;
        a.setStreet ("ulica");
        a.setPostalCode ("02-763");

        Variant ret1 = met1->invoke (Core::Variant (a));
        Variant ret2 = met2->invoke (Core::Variant (a));

        BOOST_REQUIRE (ccast <std::string> (ret1));
        BOOST_REQUIRE (ccast <std::string> (ret2));
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret1), "ulica");
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret2), "02-763");

/*--------------------------------------------------------------------------*/

        cls = Manager::classForName ("City");
        BOOST_REQUIRE_EQUAL (3U, cls->getMethodList ().size ());
}

/**
 * Ten test wywolujac metody obiektu probuje zmienic jego
 * stan. Czyli ammy jakis obiekt i za pomoca refleksji
 * wuyolujemy jego setery, a potemsprawdzamy, czy stan
 * tego obiektu sie zmienil. Obiekt podajemy jako wariant-
 * uchwyt.
 */
BOOST_AUTO_TEST_CASE (testInvokeMethodOnHandleVariant)
{
        Class *cls = Manager::classForName ("Address");
        BOOST_REQUIRE (cls);
        BOOST_REQUIRE_EQUAL (cls->getName (), "Address");

        Method *met1 = cls->getMethod ("setStreet");
        Method *met2 = cls->getMethod ("setPostalCode");

        BOOST_REQUIRE (met1);
        BOOST_REQUIRE (met2);

        Address a;
        Variant object = Core::Variant (&a);

        VariantVector params;
        params.push_back (Core::Variant ("ulica"));
        met1->invoke (object, &params);

        params.clear ();
        params.push_back (Core::Variant ("02-763"));
        met2->invoke (object, &params);

        BOOST_REQUIRE_EQUAL (a.getStreet (), "ulica");
        BOOST_REQUIRE_EQUAL (a.getPostalCode (), "02-763");
}

/**
 * Ten test dubluje poprzednie. Kiedyś można było wrzucać do warianta wszystko co się
 * chciało przez wartość. Dziś już się nie da. Kod :
 *
 * <pre>
 * Address a;
 * Variant v (a);
 * </pre>
 *
 * Tworzy wariant o semantyce uchwytu, a nie jak dawniej wartości. I to uchwytu do stałej.
 */
BOOST_AUTO_TEST_CASE (testInvokeMethodOnVariantCreatedFromVal)
{
        Class *cls = Manager::classForName ("Address");
        BOOST_REQUIRE (cls);
        BOOST_REQUIRE_EQUAL (cls->getName (), "Address");

        Method *met1 = cls->getMethod ("setStreet", 1);
        Method *met2 = cls->getMethod ("setPostalCode", 1);

        BOOST_REQUIRE (met1);
        BOOST_REQUIRE (met2);

        Address a;
        Variant object = Core::Variant (&a);
        Address *pa = vcast <Address *> (object);
        BOOST_REQUIRE (pa == &a);

        VariantVector params;
        params.push_back (Core::Variant ("ulica"));
        met1->invoke (object, &params);

        params.clear ();
        params.push_back (Core::Variant ("02-763"));
        met2->invoke (object, &params);


        // pa musi być const, bo powyższy konstruktor własnie takie tworzy. Patrz tabelka w dokumantacji od Variant.
        Variant object2 = Core::Variant (a);

        met1 = cls->getMethod ("getStreet");
        met2 = cls->getMethod ("getPostalCode");
        BOOST_REQUIRE (met1);
        BOOST_REQUIRE (met2);

        BOOST_REQUIRE_EQUAL (vcast <std::string> (met1->invoke (object2)), "ulica");
        BOOST_REQUIRE_EQUAL (vcast <std::string> (met2->invoke (object2)), "02-763");
}

/**
 * Ten test wywolujac metody obiektu probuje zmienic jego
 * stan. Czyli ammy jakis obiekt i za pomoca refleksji
 * wuyolujemy jego setery, a potemsprawdzamy, czy stan
 * tego obiektu sie zmienil. Obiekt podajemy jako wariant-
 * uchwyt.
 */
BOOST_AUTO_TEST_CASE (testInvokeMethodNonConstVariant)
{
        Class *cls = Manager::classForName ("Address");
        BOOST_REQUIRE (cls);
        BOOST_REQUIRE_EQUAL (cls->getName (), "Address");

        Method *met1 = cls->getMethod ("setString", 1);
        Method *met2 = cls->getMethod ("setPostalCode", 1);

        BOOST_REQUIRE (met1);
        BOOST_REQUIRE (met2);

        Address a;
        /*
         * Nie jest const, wiec teoretycznie powinno sie dac
         * wywolac zarówno metody const jak i nie const.
         */
        Address *pa = &a;
        const Variant object = Core::Variant (pa);

        VariantVector params;
        params.push_back (Core::Variant ("ulica"));
        met1->invoke (object, &params);

        params.clear ();
        params.push_back (Core::Variant ("02-763"));
        met2->invoke (object, &params);

        BOOST_REQUIRE_EQUAL (a.getString (), "ulica");
        BOOST_REQUIRE_EQUAL (a.getPostalCode (), "02-763");
}

/*##########################################################################*/

/**
 *
 */
BOOST_AUTO_TEST_CASE (testInvokeMethodWithVariantArg)
{
        Class *cls = Manager::classForName ("Address");
        BOOST_REQUIRE (cls);
        BOOST_REQUIRE_EQUAL (cls->getName (), "Address");

        Method *met1 = cls->getMethod ("setProperty", 1);
        BOOST_REQUIRE (met1);

        Address a;
        Variant object = Core::Variant (&a);
        Address *pa = vcast <Address *> (object);
        BOOST_REQUIRE (pa == &a);

        VariantVector params;
        Variant tmp = Core::Variant ("ulica");
        params.push_back (tmp);
        met1->invoke (object, &params);

        Variant v2 = pa->getProperty ();
        BOOST_REQUIRE_EQUAL (vcast <std::string> (v2), "ulica");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testInheritedMethods)
{
        {
                Class *cls = Manager::classForName ("Address");
                BOOST_REQUIRE (cls);
                BOOST_REQUIRE_EQUAL (cls->getName (), "Address");

                // To jest metoda zaadnotowana w Address
                Method *met1 = cls->getMethod ("setProperty", 1);
                BOOST_REQUIRE (met1);
        }

        {
                Class *cls = Manager::classForName ("Place");
                BOOST_REQUIRE (cls);
                BOOST_REQUIRE_EQUAL (cls->getName (), "Place");

                // To jest metoda zaadnotowana w Place
                Method *met1 = cls->getMethod ("setPlace", 1);
                BOOST_REQUIRE (met1);
        }

        {
                Class *cls = Manager::classForName ("Address");
                BOOST_REQUIRE (cls);
                BOOST_REQUIRE_EQUAL (cls->getName (), "Address");

                // To jest metoda zaadnotowana w Place, ale wyciągana przez addres, który ją dziedziczy
                Method *met1 = cls->getMethod ("setPlace", 1);
                BOOST_REQUIRE (met1);

                met1 = cls->getMethod ("setProperty", 1);
                BOOST_REQUIRE (met1);
        }
}

BOOST_AUTO_TEST_SUITE_END ();
