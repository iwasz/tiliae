/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>

#include "core/variant/Cast.h"
#include "core/Object.h"
#include <boost/make_shared.hpp>
#include "core/Typedefs.h"

BOOST_AUTO_TEST_SUITE (Variant07);

using namespace boost;
using namespace Core;

struct TestClass {

        TestClass () : value (0) {}

        // 0
        void a () { value ='a'; }
        void b () const { value ='b'; }
        int c () { value ='c'; return 0; }
        int d () const { value ='d'; return 0; }

        // 1
        void e (int) { value ='e'; }
        void f (int) const { value ='f'; }
        int g (int) { value ='g'; return 0; }
        int h (int) const  { value ='h'; return 0; }

        // 2
        void i (int, int) { value ='i'; }
        void j (int, int) const { value ='j'; }
        int k (int, int) { value ='k'; return 0; }
        int l (int, int) const  { value ='l'; return 0; }

        mutable char value;
};


/**
 *
 */
BOOST_AUTO_TEST_CASE (testBasic)
{
//        std::cerr << sizeof (Variant) << std::endl;
//        BOOST_REQUIRE (sizeof (Variant) <= 48);
        BOOST_REQUIRE (sizeof (Variant) <= 64);
}

BOOST_AUTO_TEST_CASE (testConstCorrectnessPointer)
{
        TestClass a;
        TestClass const c;

        Variant va (&a);              // Odpowiednik A*
        Variant const vac (&a);       // Odpowiednik A * const
        Variant vc (&c);              // Odpowiednik A const *
        Variant const vcc (&c);       // Odpowiednik A const * const

        // Uruchamiamy niestałą metodę - to się skompiluje tylko dla va i vac
        BOOST_REQUIRE_NO_THROW (vcast <TestClass *> (va)->a ());
        BOOST_REQUIRE_NO_THROW (vcast <TestClass *> (vac)->a ()); // Powinno się skompilować i zadziałać.
        BOOST_REQUIRE_THROW (vcast <TestClass *> (vc)->a (), VariantCastException); // powinien być Wyjątek z powodu złego castu z TestClass const * do TestClass *
        BOOST_REQUIRE_THROW (vcast <TestClass *> (vcc)->a (), VariantCastException); // BŁĄD! powonno się skompilować, ale zrzucić wyjątek z powodu złego castu z TestClass const * do TestClass *

        BOOST_REQUIRE_NO_THROW (vcast <TestClass *> (va)->b ());
        BOOST_REQUIRE_NO_THROW (vcast <TestClass *> (vac)->b ()); // Powinno się skompilować i zadziałać.
        BOOST_REQUIRE_THROW (vcast <TestClass *> (vc)->b (), VariantCastException); // powinien być Wyjątek z powodu złego castu z TestClass const * do TestClass *
        BOOST_REQUIRE_THROW (vcast <TestClass *> (vcc)->a (), VariantCastException); // BŁĄD! powonno się skompilować, ale zrzucić wyjątek z powodu złego castu z TestClass const * do TestClass *

// A to się nie skompiluje, bo nie można uruchomić niestałej metody dla stałego obiektu!
//        vcast <TestClass const *> (va)->a ();
//        vcast <TestClass const *> (vac)->a ();
//        vcast <TestClass const *> (vc)->a ();
//        vcast <TestClass const *> (vcc)->a ();

        BOOST_REQUIRE_NO_THROW (vcast <TestClass const *> (va)->b ());   // OK - powinno się skompilować i zadziałać.
        BOOST_REQUIRE_NO_THROW (vcast <TestClass const *> (vac)->b ());  // OK - powinno się skompilować i zadziałać.
        BOOST_REQUIRE_NO_THROW (vcast <TestClass const *> (vc)->b ());   // OK - powinno się skompilować i zadziałać.
        BOOST_REQUIRE_NO_THROW (vcast <TestClass const *> (vcc)->b ());  // OK - powinno się skompilować i zadziałać.
}

BOOST_AUTO_TEST_CASE (testConstCorrectnessRef)
{
        TestClass a;
        TestClass const c;

        Variant va (&a);              // Odpowiednik A*
        Variant const vac (&a);       // Odpowiednik A * const
        Variant vc (&c);              // Odpowiednik A const *
        Variant const vcc (&c);       // Odpowiednik A const * const

        // Uruchamiamy niestałą metodę - to się skompiluje tylko dla va i vac
        BOOST_REQUIRE_NO_THROW (vcast <TestClass &> (va).a ());
        BOOST_REQUIRE_NO_THROW (vcast <TestClass &> (vac).a ()); // Powinno się skompilować i zadziałać.
        BOOST_REQUIRE_THROW (vcast <TestClass &> (vc).a (), VariantCastException); // powinien być Wyjątek z powodu złego castu z TestClass const * do TestClass *
        BOOST_REQUIRE_THROW (vcast <TestClass &> (vcc).a (), VariantCastException); // BŁĄD! powonno się skompilować, ale zrzucić wyjątek z powodu złego castu z TestClass const * do TestClass *

        BOOST_REQUIRE_NO_THROW (vcast <TestClass &> (va).b ());
        BOOST_REQUIRE_NO_THROW (vcast <TestClass &> (vac).b ()); // Powinno się skompilować i zadziałać.
        BOOST_REQUIRE_THROW (vcast <TestClass &> (vc).b (), VariantCastException); // powinien być Wyjątek z powodu złego castu z TestClass const * do TestClass *
        BOOST_REQUIRE_THROW (vcast <TestClass &> (vcc).a (), VariantCastException); // BŁĄD! powonno się skompilować, ale zrzucić wyjątek z powodu złego castu z TestClass const * do TestClass *

// A to się nie skompiluje, bo nie można uruchomić niestałej metody dla stałego obiektu!
//        vcast <TestClass const *> (va)->a ();
//        vcast <TestClass const *> (vac)->a ();
//        vcast <TestClass const *> (vc)->a ();
//        vcast <TestClass const *> (vcc)->a ();

        BOOST_REQUIRE_NO_THROW (vcast <TestClass const &> (va).b ());   // OK - powinno się skompilować i zadziałać.
        BOOST_REQUIRE_NO_THROW (vcast <TestClass const &> (vac).b ());  // OK - powinno się skompilować i zadziałać.
        BOOST_REQUIRE_NO_THROW (vcast <TestClass const &> (vc).b ());   // OK - powinno się skompilować i zadziałać.
        BOOST_REQUIRE_NO_THROW (vcast <TestClass const &> (vcc).b ());  // OK - powinno się skompilować i zadziałać.
}

BOOST_AUTO_TEST_CASE (testConstCorrectnessSmartPtr)
{
        Ptr <TestClass> a = make_shared <TestClass> ();
        Ptr <TestClass const> c = make_shared <TestClass const> ();

        Variant va (a);              // Odpowiednik A*
        Variant const vac (a);       // Odpowiednik A * const
        Variant vc (c);              // Odpowiednik A const *
        Variant const vcc (c);       // Odpowiednik A const * const

        BOOST_REQUIRE_NO_THROW (vcast <TestClass *> (va)->a ());
        BOOST_REQUIRE_NO_THROW (vcast <TestClass *> (vac)->a ());
        BOOST_REQUIRE_THROW (vcast <TestClass *> (vc)->a (), VariantCastException);
        BOOST_REQUIRE_THROW (vcast <TestClass *> (vcc)->a (), VariantCastException);

        BOOST_REQUIRE_NO_THROW (vcast <TestClass *> (va)->b ());
        BOOST_REQUIRE_NO_THROW (vcast <TestClass *> (vac)->b ());
        BOOST_REQUIRE_THROW (vcast <TestClass *> (vc)->b (), VariantCastException);
        BOOST_REQUIRE_THROW (vcast <TestClass *> (vcc)->a (), VariantCastException);

        BOOST_REQUIRE_NO_THROW (vcast <TestClass const *> (va)->b ());
        BOOST_REQUIRE_NO_THROW (vcast <TestClass const *> (vac)->b ());
        BOOST_REQUIRE_NO_THROW (vcast <TestClass const *> (vc)->b ());
        BOOST_REQUIRE_NO_THROW (vcast <TestClass const *> (vcc)->b ());

/*--------------------------------------------------------------------------*/

         BOOST_REQUIRE_NO_THROW (vcast <Ptr <TestClass> > (va)->a ());
         BOOST_REQUIRE_NO_THROW (vcast <Ptr <TestClass> > (vac)->a ());
         BOOST_REQUIRE_THROW (vcast <Ptr <TestClass> > (vc)->a (), VariantCastException);
         BOOST_REQUIRE_THROW (vcast <Ptr <TestClass> > (vcc)->a (), VariantCastException);

         BOOST_REQUIRE_NO_THROW (vcast <Ptr <TestClass> > (va)->b ());
         BOOST_REQUIRE_NO_THROW (vcast <Ptr <TestClass> > (vac)->b ());
         BOOST_REQUIRE_THROW (vcast <Ptr <TestClass> > (vc)->b (), VariantCastException);
         BOOST_REQUIRE_THROW (vcast <Ptr <TestClass> > (vcc)->a (), VariantCastException);

         BOOST_REQUIRE_NO_THROW (vcast <Ptr <TestClass const> > (va)->b ());
         BOOST_REQUIRE_NO_THROW (vcast <Ptr <TestClass const> > (vac)->b ());
         BOOST_REQUIRE_NO_THROW (vcast <Ptr <TestClass const> > (vc)->b ());
         BOOST_REQUIRE_NO_THROW (vcast <Ptr <TestClass const> > (vcc)->b ());

 /*--------------------------------------------------------------------------*/

         BOOST_REQUIRE_NO_THROW (vcast <TestClass &> (va).a ());
         BOOST_REQUIRE_NO_THROW (vcast <TestClass &> (vac).a ());
         BOOST_REQUIRE_THROW (vcast <TestClass &> (vc).a (), VariantCastException);
         BOOST_REQUIRE_THROW (vcast <TestClass &> (vcc).a (), VariantCastException);

         BOOST_REQUIRE_NO_THROW (vcast <TestClass &> (va).b ());
         BOOST_REQUIRE_NO_THROW (vcast <TestClass &> (vac).b ());
         BOOST_REQUIRE_THROW (vcast <TestClass &> (vc).b (), VariantCastException);
         BOOST_REQUIRE_THROW (vcast <TestClass &> (vcc).a (), VariantCastException);

         BOOST_REQUIRE_NO_THROW (vcast <TestClass const &> (va).b ());
         BOOST_REQUIRE_NO_THROW (vcast <TestClass const &> (vac).b ());
         BOOST_REQUIRE_NO_THROW (vcast <TestClass const &> (vc).b ());
         BOOST_REQUIRE_NO_THROW (vcast <TestClass const &> (vcc).b ());
}

/**
 * Sprawdza, czy da się zmienić wariantom to co jest w ich środku. Na tej zasadzie
 * działają edytory - zakładają, że to co jest w wariancie można zmienić i w ten
 * sposób dostają obiekty wyjściowe.
 */
BOOST_AUTO_TEST_CASE (testHandleAndValue)
{
        {
                // INT - Variant-value
                Variant v (10);
                int *pi = vcast <int *> (v);
                BOOST_CHECK_EQUAL (*pi, 10);

                // 1. Zmieniłem wartość obiektu na który wskazuje *pi
                *pi = 11;
                // 2. A to był int w unii w wariancie i teraz wariant ma wartość 11.
                BOOST_CHECK_EQUAL (vcast <int> (v), 11);
        }

        {
                // STD_STRING - variant-handle stworzony ze stałej napisowej.
                Variant v ("kupa kupa");
                std::string *ps = vcast <std::string *> (v);
                BOOST_CHECK_EQUAL (*ps, "kupa kupa");

                // Zmieniłem wartość obiektu na który wskazuje *ps
                *ps = std::string ("ala ma kota");
                BOOST_CHECK_EQUAL (vcast <std::string> (v), "ala ma kota");
        }

        {
                // STD_STRING - variant-handle stworzony ze wskaźnika.
                std::string str ("kupa kupa");
                Variant v (&str);
                std::string *ps = vcast <std::string *> (v);
                BOOST_CHECK_EQUAL (ps, &str);
                BOOST_CHECK_EQUAL (*ps, "kupa kupa");

                // Zmieniłem wartość obiektu na który wskazuje *ps
                *ps = std::string ("ala ma kota");
                BOOST_CHECK_EQUAL (vcast <std::string> (v), "ala ma kota");
                BOOST_CHECK_EQUAL (str, "ala ma kota");
        }
}

struct A { int i; };

BOOST_AUTO_TEST_CASE (testTypeId)
{
        std::type_info const &ti = typeid (A&);

        {
                A a;
                Variant v (a);
                BOOST_REQUIRE (v.getTypeInfo () == ti);
        }

        {
                A const a = {1};
                Variant v (a); // Tworzy handler POINTER_CONST
                BOOST_REQUIRE (v.getTypeInfo () == ti);
        }

        {
                A a;
                A *pa = &a;
                Variant v (pa); // Tworzy handler POINTER
                BOOST_REQUIRE (v.getTypeInfo () == ti);
        }

        {
                A const a = {2};
                A const *cpa = &a;
                Variant v (cpa); // Tworzy handler POINTER_CONST
                BOOST_REQUIRE (v.getTypeInfo () == ti);
        }

        {
                A a;
                A &ra = a;
                Variant v (ra); // Tworzy handler POINTER_CONST
                BOOST_REQUIRE (v.getTypeInfo () == ti);
        }

        {
                A const a = {3};
                A const *cpa = &a;
                Variant v (cpa); // Tworzy handler POINTER_CONST
                BOOST_REQUIRE (v.getTypeInfo () == ti);
        }

        {
                shared_ptr <A> a (new A);
                Variant v (a); // Tworzy handler SMART
                BOOST_REQUIRE (v.getTypeInfo () == ti);
        }

        {
                shared_ptr <A const> a (new A);
                Variant v (a); // Tworzy handler SMART_CONST
                BOOST_REQUIRE (v.getTypeInfo () == ti);
        }
}

BOOST_AUTO_TEST_CASE (testLCast)
{
        {
                Variant v ("666");
                BOOST_CHECK_EQUAL (lcast <int> (v), 666);
                BOOST_CHECK_EQUAL (lcast <unsigned int> (v), 666U);
                BOOST_CHECK_EQUAL (lcast <double> (v), 666.0);
                BOOST_CHECK_EQUAL (lcast <float> (v), 666.0);
                BOOST_CHECK_EQUAL (lcast <long double> (v), 666.0);
                BOOST_CHECK_EQUAL (lcast <std::string> (v), "666");
#ifdef WITH_CORE_STRING
                BOOST_CHECK_EQUAL (lcast <Core::String> (v), "666");
#endif
        }

        {
                Variant v ("1");
                BOOST_CHECK_EQUAL (lcast <bool> (v), true);
        }

        {
                Variant v (667);
                BOOST_CHECK_EQUAL (lcast <std::string> (v), "667");
#ifdef WITH_CORE_STRING
                BOOST_CHECK_EQUAL (lcast <Core::String> (v), "667");
#endif
        }
}

VariantList func ()
{
        VariantList ret;
        ret.push_back (Variant ("abc"));
        ret.push_back (Variant ("cab"));
        return ret;
}

struct Type {
        int i;

        ~Type () { i = 0; }
};

/**
 * Zmienne tymczasowe
 */
BOOST_AUTO_TEST_CASE (testRvalue)
{
        Variant v = Variant (func ());
        BOOST_REQUIRE_EQUAL (v.getType (), Variant::SMART);

        {
                Type t = {78943};
                v = Variant (t);
        }

        Type const *tt = vcast <Type const *> (v);
        BOOST_REQUIRE_EQUAL (tt->i, 78943);
}

/**
 * Na void * etc.
 */
BOOST_AUTO_TEST_CASE (testVoidPtr)
{
        std::string str = "slkjfuioewui3";
        int i = 7908;
        int const *pi = &i;
        Ptr <int> si = boost::make_shared <int> (98734);
        Ptr <int const> csi = boost::make_shared <int const> (98734);

        {
                Variant v (&str);
                void *p = vcast <void *> (v);
                BOOST_REQUIRE_EQUAL (p, &str);
                void const *cp = vcast <void const *> (v);
                BOOST_REQUIRE_EQUAL (cp, &str);
        }

        {
                Variant v (&str);
                void const *p = vcast <void const *> (v);
                BOOST_REQUIRE_EQUAL (p, &str);
        }

        {
                Variant v (pi);
                void const *p = vcast <void const *> (v);
                BOOST_REQUIRE_EQUAL (p, pi);
        }

        {
                Variant v (si);
                Ptr <void> p = vcast <Ptr <void> > (v);
                BOOST_REQUIRE_EQUAL (p, si);
        }
}

#ifdef ALLOW_CAST_TO_SMART

/**
 *
 */
BOOST_AUTO_TEST_CASE (testCastToSmart)
{
        int *i = new int;
        Variant v (i);
        BOOST_REQUIRE (ccast <Ptr <int> > (v));
}

#endif


#ifndef ALLOW_CAST_TO_SMART

BOOST_AUTO_TEST_CASE (testConvertToPtr)
{
        int *i = new int;
        Variant v (i);
        BOOST_REQUIRE (!ccast <Ptr <int> > (v));

        Variant v2 = Core::convertVariantToSmart (v);
        BOOST_REQUIRE (ccast <Ptr <int> > (v2));

        Ptr <int> i2 = vcast <Ptr <int> > (v2);
        BOOST_REQUIRE_EQUAL (i2.get (), i);
}

#endif

BOOST_AUTO_TEST_CASE (testNulls)
{
        Variant v;
        v.setNull ();
        v.setTypeInfo(typeid (double)); // Niezależnie od tego co tu jest, konwersja powinna zadziałać.

        {
        int *i = vcast <int *> (v);
        BOOST_REQUIRE (!i);

        Ptr <int> i2 = vcast <Ptr <int> > (v);
        BOOST_REQUIRE (!i2);
        }

        {
        int *i = ocast <int *> (v);
        BOOST_REQUIRE (!i);

        Ptr <int> i2 = ocast <Ptr <int> > (v);
        BOOST_REQUIRE (!i2);
        }

        {
        TestClass *i = vcast <TestClass *> (v);
        BOOST_REQUIRE (!i);

        Ptr <TestClass > i2 = vcast <Ptr <TestClass > > (v);
        BOOST_REQUIRE (!i2);
        }

        {
        TestClass *i = ocast <TestClass *> (v);
        BOOST_REQUIRE (!i);

        Ptr <TestClass > i2 = ocast <Ptr <TestClass > > (v);
        BOOST_REQUIRE (!i2);
        }

}


BOOST_AUTO_TEST_SUITE_END ();
