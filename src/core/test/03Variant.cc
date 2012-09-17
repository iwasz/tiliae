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

BOOST_AUTO_TEST_SUITE (Variant03);

using namespace boost;
using namespace Core;

struct A {
        A (int j = 0) : i (j) {}
        bool operator == (A const &a) const { return a.i == i; }
        int i;
};

std::ostream &operator << (std::ostream &s, A const &a) { s << "A(" << a.i << ")"; return s; }

// Niekompletny, zdefiniowany dopiero na końcu.
class I;
extern I globalI;
extern shared_ptr <I> globalP;

struct B : public Object {
        virtual ~B () {}
        B (int j = 0) : i (j) {}
        bool operator == (B const &a) const { return a.i == i; }
        int i;
};

std::ostream &operator << (std::ostream &s, B const &a) { s << "B(" << a.i << ")"; return s; }

struct C : public B {
        virtual ~C () {}
        C (int j = 0) : i (j) {}
        bool operator == (C const &a) const { return a.i == i; }
        int i;
};

std::ostream &operator << (std::ostream &s, C const &a) { s << "C(" << a.i << ")"; return s; }

/**
 *
 */
BOOST_AUTO_TEST_CASE (testBasic)
{
        A *pa = (A *) 0x01;
        I *pi = (I *) 0x01;
        int i = 12;
        shared_ptr<A> sa;
        shared_ptr<I> si;

        {
                Variant v (pa);
                BOOST_REQUIRE_EQUAL (vcast <A *> (v), (A *)0x01);
        }
        {
                Variant v (pi);
                BOOST_REQUIRE_EQUAL (vcast <I *> (v), (I *)0x01);
        }
        {
                Variant v (i);
                BOOST_REQUIRE_EQUAL (vcast <int> (v), 12);
        }
        {
                Variant v (sa);
                BOOST_REQUIRE_EQUAL (vcast <shared_ptr <A> > (v).get (), (A*)0);
                BOOST_REQUIRE_EQUAL (vcast <A *> (v), (A*)0);
        }
        {
                Variant v (si);
                BOOST_REQUIRE_EQUAL (vcast <shared_ptr <I> > (v).get (), (I*)0);
                BOOST_REQUIRE_EQUAL (vcast <I *> (v), (I*)0);

                // Tu zrobić asercję na zrzucanie wyjątku.
                //assert (vcast <shared_ptr <A> > (v) == 0);
                //std::clog << "OK" << std::endl;
        }

//        std::cout << sizeof (Variant) << std::endl;
}

/**
 * Wszystkie możliwe kasty do i z warianta. Typ kompletny.
 */
BOOST_AUTO_TEST_CASE (testCustomCompleteType)
{
        {
                A a (668);
                Variant v (a); // Tworzy handler POINTER_CONST
                BOOST_REQUIRE_EQUAL (vcast <A> (v), A (668));
//                BOOST_REQUIRE_THROW ((vcast <A *> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (*(vcast <A *> (v)), A (668));
                BOOST_REQUIRE_EQUAL (*(vcast <A const *> (v)), A (668));
//                BOOST_REQUIRE_THROW ((vcast <A &> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <A &> (v), A (668));
                BOOST_REQUIRE_EQUAL (vcast <A const &> (v), A (668));
//                BOOST_REQUIRE_THROW ((vcast <shared_ptr<A> > (v)), Core::VariantCastException);
//                BOOST_REQUIRE_THROW ((vcast <shared_ptr<A const> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (*(vcast <shared_ptr<A> > (v)), A (668));
                BOOST_REQUIRE_EQUAL (*(vcast <shared_ptr<A const> > (v)), A (668));
        }

        {
                A const a (668);
                Variant v (a);
                BOOST_REQUIRE_EQUAL (vcast <A> (v), A (668));
                BOOST_REQUIRE_EQUAL (*(vcast <A *> (v)), A (668));
                BOOST_REQUIRE_EQUAL (*(vcast <A const *> (v)), A (668));
                BOOST_REQUIRE_EQUAL (vcast <A &> (v), A (668));
                BOOST_REQUIRE_EQUAL (vcast <A const &> (v), A (668));
                BOOST_REQUIRE_EQUAL (*(vcast <shared_ptr<A> > (v)), A (668));
                BOOST_REQUIRE_EQUAL (*(vcast <shared_ptr<A const> > (v)), A (668));
        }

        {
                A a (668);
                A *pa = &a;
                Variant v (pa); // Tworzy handler POINTER
                BOOST_REQUIRE_EQUAL (vcast <A> (v), A (668));
                BOOST_REQUIRE_EQUAL (vcast <A *> (v), pa);
                BOOST_REQUIRE_EQUAL (vcast <A const *> (v), pa);
                BOOST_REQUIRE_EQUAL (vcast <A &> (v), A (668));
                BOOST_REQUIRE_EQUAL (vcast <A const &> (v), A (668));
#ifndef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<A> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<A const> > (v)), Core::VariantCastException);
#endif
        }

        {
                A const a (668);
                A const *cpa = &a;
                Variant v (cpa); // Tworzy handler POINTER_CONST
                BOOST_REQUIRE_EQUAL (vcast <A> (v), A (668));
                BOOST_REQUIRE_THROW ((vcast <A *> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <A const *> (v), cpa);
                BOOST_REQUIRE_THROW ((vcast <A &> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <A const &> (v), A (668));
#ifndef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<A> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<A const> > (v)), Core::VariantCastException);
#endif
        }

        {
                A a (668);
                A &ra = a;
                Variant v (ra); // Tworzy handler POINTER_CONST
                BOOST_REQUIRE_EQUAL (vcast <A> (v), A (668));
                BOOST_REQUIRE_EQUAL (*(vcast <A *> (v)), A (668));
                BOOST_REQUIRE_EQUAL (*(vcast <A const *> (v)), A (668));
                BOOST_REQUIRE_EQUAL (vcast <A &> (v), A (668));
                BOOST_REQUIRE_EQUAL (vcast <A const &> (v), A (668));
                BOOST_REQUIRE_EQUAL (*(vcast <shared_ptr<A> > (v)), A (668));
                BOOST_REQUIRE_EQUAL (*(vcast <shared_ptr<A const> > (v)), A (668));
        }

        {
                A const a (668);
                A const *cpa = &a;
                Variant v (cpa); // Tworzy handler POINTER_CONST
                BOOST_REQUIRE_EQUAL (vcast <A> (v), A (668));
                BOOST_REQUIRE_THROW ((vcast <A *> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <A const *> (v), &a);
                BOOST_REQUIRE_THROW ((vcast <A &> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <A const &> (v), A (668));
#ifndef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<A> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<A const> > (v)), Core::VariantCastException);
#endif
        }

        {
                shared_ptr <A> a (new A (668));
//                std::cerr << a.use_count () << std::endl;
                Variant v (a); // Tworzy handler SMART
//                std::cerr << a.use_count () << std::endl;
                BOOST_REQUIRE_EQUAL (vcast <A> (v), A (668));
                BOOST_REQUIRE_EQUAL (vcast <A *> (v), a.get ());
                BOOST_REQUIRE_EQUAL (vcast <A const *> (v), a.get ());
                BOOST_REQUIRE_EQUAL (vcast <A &> (v), A (668));
                BOOST_REQUIRE_EQUAL (vcast <A const &> (v), A (668));
                BOOST_REQUIRE_EQUAL ((vcast <shared_ptr<A> > (v)), a);
                BOOST_REQUIRE_EQUAL ((vcast <shared_ptr<A const> > (v)), a);
        }

        {
                shared_ptr <A const> a (new A (668));
                Variant v (a); // Tworzy handler SMART_CONST
                BOOST_REQUIRE_EQUAL (vcast <A> (v), A (668));
                BOOST_REQUIRE_THROW ((vcast <A *> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <A const *> (v), a.get ());
                BOOST_REQUIRE_THROW ((vcast <A &> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <A const &> (v), A (668));
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<A> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL ((vcast <shared_ptr<A const> > (v)), a);
        }
}

/**
 * Wszystkie możliwe kasty do i z warianta. Typ NIE kompletny.
 */
BOOST_AUTO_TEST_CASE (testCustomINCompleteType)
{
        {
                I *pa = (I *)0x01;
                Variant v (pa); // Tworzy handler POINTER
                BOOST_REQUIRE_EQUAL (vcast <I *> (v), pa);
                BOOST_REQUIRE_EQUAL (vcast <I const *> (v), pa);
                BOOST_REQUIRE_EQUAL (&(vcast <I &> (v)), pa);
                BOOST_REQUIRE_EQUAL (&(vcast <I const &> (v)), pa);
#ifndef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<I> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<I const> > (v)), Core::VariantCastException);
#endif
        }

        {
                I const*pa = (I *)0x01;
                Variant v (pa); // Tworzy handler CONST_POINTER
                BOOST_REQUIRE_THROW ((vcast <I *> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <I const *> (v), pa);
                BOOST_REQUIRE_THROW ((vcast <I &> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (&(vcast <I const &> (v)), pa);
#ifndef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<I> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<I const> > (v)), Core::VariantCastException);
#endif
        }

        {
                extern I &func (void);
                Variant v (func ());
                BOOST_REQUIRE_NE (vcast <I const *> (v), &globalI); // Bo tu jest kopia
                BOOST_REQUIRE_NO_THROW (vcast <I &> (v));
                BOOST_REQUIRE_NE (&(vcast <I const &> (v)), &globalI);
                BOOST_REQUIRE_NO_THROW ((vcast <shared_ptr<I> > (v)));
                BOOST_REQUIRE_NO_THROW ((vcast <shared_ptr<I const> > (v)));
        }

        {
                extern I const &func2 (void);
                Variant v (func2 ());
                BOOST_REQUIRE_NO_THROW ((vcast <I *> (v)));
                BOOST_REQUIRE_NE (vcast <I const *> (v), &globalI);
                BOOST_REQUIRE_NO_THROW ((vcast <I &> (v)));
                BOOST_REQUIRE_NE (&(vcast <I const &> (v)), &globalI);
                BOOST_REQUIRE_NO_THROW ((vcast <shared_ptr<I> > (v)));
                BOOST_REQUIRE_NO_THROW ((vcast <shared_ptr<I const> > (v)));
        }

        {
                extern shared_ptr<I> func3 ();
                Variant v (func3 ()); // Tworzy handler SMART
                BOOST_REQUIRE_EQUAL (vcast <I *> (v), globalP.get ());
                BOOST_REQUIRE_EQUAL (vcast <I const *> (v), globalP.get ());
                BOOST_REQUIRE_EQUAL (&(vcast <I &> (v)), globalP.get ());
                BOOST_REQUIRE_EQUAL (&(vcast <I const &> (v)), globalP.get ());
                BOOST_REQUIRE_EQUAL ((vcast <shared_ptr<I> > (v)), globalP);
                BOOST_REQUIRE_EQUAL ((vcast <shared_ptr<I const> > (v)), globalP);
        }

        {
                extern shared_ptr<I const> func4 ();
                Variant v (func4 ()); // Tworzy handler CONST_SMART
                BOOST_REQUIRE_THROW (vcast <I *> (v), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <I const *> (v), globalP.get ());
                BOOST_REQUIRE_THROW ((vcast <I &> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (&(vcast <I const &> (v)), globalP.get ());
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<I> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL ((vcast <shared_ptr<I const> > (v)), globalP);
        }
}

/**
 * Wszystkie możliwe kasty do i z warianta. Typ kompletny polimorficzny kast, OCAST.
 */
BOOST_AUTO_TEST_CASE (testCustomPolymorphic)
{
        {
                C a (668);
                Variant v (a);
                BOOST_REQUIRE_NE (&(ocast <B> (v)), &a);
                BOOST_REQUIRE_NO_THROW ((ocast <B *> (v)));
                BOOST_REQUIRE_NE (ocast <B const *> (v), &a);
                BOOST_REQUIRE_NO_THROW ((ocast <B &> (v)));
                BOOST_REQUIRE_NE (&(ocast <B const &> (v)), &a);
                BOOST_REQUIRE_NO_THROW ((ocast <shared_ptr<B> > (v)));
                BOOST_REQUIRE_NO_THROW ((ocast <shared_ptr<B const> > (v)));
        }

        {
                C const a (668);
                Variant v (a); // Tworzy handler OBJECT_CONST
                BOOST_REQUIRE_EQUAL (ocast <B> (v), C (668));
                BOOST_REQUIRE_EQUAL (*(ocast <B *> (v)), C (668));
                BOOST_REQUIRE_EQUAL (*ocast <B const *> (v), C (668));
                BOOST_REQUIRE_NO_THROW ((ocast <B &> (v)));
                BOOST_REQUIRE_EQUAL ((ocast <B const &> (v)), C (668));
                BOOST_REQUIRE_NO_THROW ((ocast <shared_ptr<B> > (v)));
                BOOST_REQUIRE_NO_THROW ((ocast <shared_ptr<B const> > (v)));
        }

        {
                C c (668);
                C *pa = &c;
                Variant v (pa); // Tworzy handler OBJECT
                BOOST_REQUIRE_EQUAL (&(ocast <B> (v)), &c);
                BOOST_REQUIRE_EQUAL (ocast <B *> (v), &c);
                BOOST_REQUIRE_EQUAL (ocast <B const *> (v), &c);
                BOOST_REQUIRE_EQUAL (&(ocast <B &> (v)), &c);
                BOOST_REQUIRE_EQUAL (&(ocast <B const &> (v)), &c);
#ifndef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE_THROW ((ocast <shared_ptr<B> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_THROW ((ocast <shared_ptr<B const> > (v)), Core::VariantCastException);
#endif
        }

        {
                C const c (668);
                C const *cpa = &c;
                Variant v (cpa); // Tworzy handler OBJECT_CONST
                BOOST_REQUIRE_EQUAL (&(ocast <B> (v)), &c);
                BOOST_REQUIRE_THROW (ocast <B *> (v), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (ocast <B const *> (v), &c);
                BOOST_REQUIRE_THROW (ocast <B &> (v), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (&(ocast <B const &> (v)), &c);
#ifndef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE_THROW ((ocast <shared_ptr<B> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_THROW ((ocast <shared_ptr<B const> > (v)), Core::VariantCastException);
#endif
        }

        {
                C c (668);
                C &ra = c;
                Variant v (ra); // Tworzy handler OBJECT_CONST
                BOOST_REQUIRE_EQUAL ((ocast <B> (v)), c);
                BOOST_REQUIRE_NO_THROW (ocast <B *> (v));
                BOOST_REQUIRE_EQUAL (*ocast <B const *> (v), c);
                BOOST_REQUIRE_NO_THROW (ocast <B &> (v));
                BOOST_REQUIRE_EQUAL ((ocast <B const &> (v)), c);
                BOOST_REQUIRE_NO_THROW ((ocast <shared_ptr<B> > (v)));
                BOOST_REQUIRE_NO_THROW ((ocast <shared_ptr<B const> > (v)));
        }

        {
                C const c (668);
                C const &cpa = c;
                Variant v (cpa); // Tworzy handler OBJECT_CONST
                BOOST_REQUIRE_EQUAL ((ocast <B> (v)), c);
                BOOST_REQUIRE_NO_THROW (ocast <B *> (v));
                BOOST_REQUIRE_EQUAL (*ocast <B const *> (v), c);
                BOOST_REQUIRE_NO_THROW (ocast <B &> (v));
                BOOST_REQUIRE_EQUAL ((ocast <B const &> (v)), c);
                BOOST_REQUIRE_NO_THROW ((ocast <shared_ptr<B> > (v)));
                BOOST_REQUIRE_NO_THROW ((ocast <shared_ptr<B const> > (v)));
        }

        {
                shared_ptr <C> a (new C (668));
                Variant v (a); // Tworzy handler SMART_OBJECT
                BOOST_REQUIRE_EQUAL (&(ocast <B> (v)), a.get ());
                BOOST_REQUIRE_EQUAL (ocast <B *> (v), a.get ());
                BOOST_REQUIRE_EQUAL (ocast <B const *> (v), a.get ());
                BOOST_REQUIRE_EQUAL (&(ocast <B &> (v)), a.get ());
                BOOST_REQUIRE_EQUAL (&(ocast <B const &> (v)), a.get ());
                BOOST_REQUIRE_EQUAL ((ocast <shared_ptr<B> > (v)), a);
                BOOST_REQUIRE_EQUAL ((ocast <shared_ptr<B const> > (v)), a);
        }

        {
                shared_ptr <C const> a (new C (668));
                Variant v (a); // Tworzy handler SMART_OBJECT
                BOOST_REQUIRE_EQUAL (&(ocast <B> (v)), a.get ());
                BOOST_REQUIRE_THROW ((ocast <B *> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (ocast <B const *> (v), a.get ());
                BOOST_REQUIRE_THROW ((ocast <B &> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (&(ocast <B const &> (v)), a.get ());
                BOOST_REQUIRE_THROW ((ocast <shared_ptr<B> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL ((ocast <shared_ptr<B const> > (v)), a);
        }

/****************************************************************************/

        {
                C c (668);
                Variant v (&c); // Tworzy handler OBJECT
                BOOST_REQUIRE_EQUAL (&(ocast <B> (v)), &c);
//                BOOST_REQUIRE_THROW ((ocast <B *> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (ocast <B *> (v), &c);
                BOOST_REQUIRE_EQUAL (ocast <B const *> (v), &c);
                BOOST_REQUIRE_EQUAL (&(ocast <B &> (v)), &c);
                BOOST_REQUIRE_EQUAL (&(ocast <B const &> (v)), &c);
#ifndef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE_THROW ((ocast <shared_ptr<B> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_THROW ((ocast <shared_ptr<B const> > (v)), Core::VariantCastException);
#endif
        }

        {
                C c (668);
                B &b = c;
                Variant v (&b);
                BOOST_REQUIRE_EQUAL (&(ocast <C> (v)), &c);
        }

}

/**
 * Kast polimorficzny w drugą stronę.
 */
BOOST_AUTO_TEST_CASE (testCustomPolymorphic2)
{
    {
            C c (668);
            B *pa = &c;
            Variant v (pa); // Tworzy handler OBJECT
            BOOST_REQUIRE_EQUAL (&(ocast <C> (v)), &c);
            BOOST_REQUIRE_EQUAL (ocast <C *> (v), &c);
            BOOST_REQUIRE_EQUAL (ocast <C const *> (v), &c);
            BOOST_REQUIRE_EQUAL (&(ocast <C &> (v)), &c);
            BOOST_REQUIRE_EQUAL (&(ocast <C const &> (v)), &c);
#ifndef ALLOW_CAST_TO_SMART
            BOOST_REQUIRE_THROW ((ocast <shared_ptr<C> > (v)), Core::VariantCastException);
            BOOST_REQUIRE_THROW ((ocast <shared_ptr<C const> > (v)), Core::VariantCastException);
#endif
    }
}

/**
 * Wszystkie możliwe kasty do i z warianta. Typ dziedziczący z Object, ale
 * kasty statyczne vcast.
 */
BOOST_AUTO_TEST_CASE (testVCastObject)
{
        {
                C a (668);
                Variant v (a);
                BOOST_REQUIRE_EQUAL (vcast <C> (v), C (668));
//                BOOST_REQUIRE_THROW ((vcast <C *> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (*(vcast <C*> (v)), C (668));
                BOOST_REQUIRE_EQUAL (*(vcast <C const *> (v)), C (668));
//                BOOST_REQUIRE_THROW ((vcast <C &> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <C const &> (v), C (668));
                BOOST_REQUIRE_EQUAL (vcast <C &> (v), C (668));
//                BOOST_REQUIRE_THROW ((vcast <shared_ptr<C> > (v)), Core::VariantCastException);
//                BOOST_REQUIRE_THROW ((vcast <shared_ptr<C const> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (*(vcast <shared_ptr<C> > (v)), C (668));
                BOOST_REQUIRE_EQUAL (*(vcast <shared_ptr<C const> > (v)), C (668));
        }

        {
                C const a (668);
                Variant v (a);
                BOOST_REQUIRE_EQUAL (vcast <C> (v), C (668));
                BOOST_REQUIRE_EQUAL (*(vcast <C*> (v)), C (668));
                BOOST_REQUIRE_EQUAL (*(vcast <C const *> (v)), C (668));
                BOOST_REQUIRE_EQUAL (vcast <C const &> (v), C (668));
                BOOST_REQUIRE_EQUAL (vcast <C &> (v), C (668));
                BOOST_REQUIRE_EQUAL (*(vcast <shared_ptr<C> > (v)), C (668));
                BOOST_REQUIRE_EQUAL (*(vcast <shared_ptr<C const> > (v)), C (668));
        }

        {
                C a (668);
                C *pa = &a;
                Variant v (pa); // Tworzy handler POINTER
                BOOST_REQUIRE_EQUAL (vcast <C> (v), C (668));
                BOOST_REQUIRE_EQUAL (vcast <C *> (v), pa);
                BOOST_REQUIRE_EQUAL (vcast <C const *> (v), pa);
                BOOST_REQUIRE_EQUAL (vcast <C &> (v), C (668));
                BOOST_REQUIRE_EQUAL (vcast <C const &> (v), C (668));
#ifndef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<C> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<C const> > (v)), Core::VariantCastException);
#endif
        }

        {
                C const a (668);
                C const *cpa = &a;
                Variant v (cpa); // Tworzy handler POINTER_CONST
                BOOST_REQUIRE_EQUAL (vcast <C> (v), C (668));
                BOOST_REQUIRE_THROW ((vcast <C *> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <C const *> (v), cpa);
                BOOST_REQUIRE_THROW ((vcast <C &> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <C const &> (v), C (668));
#ifndef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<C> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<C const> > (v)), Core::VariantCastException);
#endif
        }

        {
                C a (668);
                C &ra = a;
                Variant v (ra); // Tworzy handler POINTER_CONST
                BOOST_REQUIRE_EQUAL (vcast <C> (v), C (668));
                BOOST_REQUIRE_EQUAL (vcast <C> (v), C (668));
                BOOST_REQUIRE_EQUAL (*(vcast <C*> (v)), C (668));
                BOOST_REQUIRE_EQUAL (*(vcast <C const *> (v)), C (668));
                BOOST_REQUIRE_EQUAL (vcast <C const &> (v), C (668));
                BOOST_REQUIRE_EQUAL (vcast <C &> (v), C (668));
                BOOST_REQUIRE_EQUAL (*(vcast <shared_ptr<C> > (v)), C (668));
                BOOST_REQUIRE_EQUAL (*(vcast <shared_ptr<C const> > (v)), C (668));
        }

        {
                C const a (668);
                C const *cpa = &a;
                Variant v (cpa); // Tworzy handler POINTER_CONST
                BOOST_REQUIRE_EQUAL (vcast <C> (v), C (668));
                BOOST_REQUIRE_THROW ((vcast <C *> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <C const *> (v), &a);
                BOOST_REQUIRE_THROW ((vcast <C &> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <C const &> (v), C (668));
#ifndef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<C> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<C const> > (v)), Core::VariantCastException);
#endif
        }

        {
                shared_ptr <C> a (new C (668));
//                std::cerr << a.use_count () << std::endl;
                Variant v (a); // Tworzy handler SMART
//                std::cerr << a.use_count () << std::endl;
                BOOST_REQUIRE_EQUAL (vcast <C> (v), C (668));
                BOOST_REQUIRE_EQUAL (vcast <C *> (v), a.get ());
                BOOST_REQUIRE_EQUAL (vcast <C const *> (v), a.get ());
                BOOST_REQUIRE_EQUAL (vcast <C &> (v), C (668));
                BOOST_REQUIRE_EQUAL (vcast <C const &> (v), C (668));
                BOOST_REQUIRE_EQUAL ((vcast <shared_ptr<C> > (v)), a);
                BOOST_REQUIRE_EQUAL ((vcast <shared_ptr<C const> > (v)), a);
        }

        {
                shared_ptr <C const> a (new C (668));
                Variant v (a); // Tworzy handler SMART_CONST
                BOOST_REQUIRE_EQUAL (vcast <C> (v), C (668));
                BOOST_REQUIRE_THROW ((vcast <C *> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <C const *> (v), a.get ());
                BOOST_REQUIRE_THROW ((vcast <C &> (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL (vcast <C const &> (v), C (668));
                BOOST_REQUIRE_THROW ((vcast <shared_ptr<C> > (v)), Core::VariantCastException);
                BOOST_REQUIRE_EQUAL ((vcast <shared_ptr<C const> > (v)), a);
        }
}


class I { int i; };
I globalI;
shared_ptr <I> globalP (new I);

I &func () { return globalI; }
I const &func2 () { return globalI; }
shared_ptr<I> func3 () { return globalP; }
shared_ptr<I const> func4 () { return globalP; }

BOOST_AUTO_TEST_SUITE_END ();
