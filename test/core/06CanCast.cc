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

BOOST_AUTO_TEST_SUITE (CanCast06);

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
extern std::shared_ptr <I> globalP;

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
 * Wszystkie możliwe kasty do i z warianta. Typ kompletny.
 */
BOOST_AUTO_TEST_CASE (testCustomCompleteType)
{
        {
                A a (668);
                Variant v (a); // Tworzy handler SMART, bo v zawiera teraz kopię a.
                BOOST_REQUIRE (ccast <A> (v));
                BOOST_REQUIRE (ccast <A *> (v));
                BOOST_REQUIRE (ccast <A const *> (v));
                BOOST_REQUIRE (ccast <A &> (v));
                BOOST_REQUIRE (ccast <A const &> (v));
                BOOST_REQUIRE (ccast <std::shared_ptr<A> > (v));
                BOOST_REQUIRE (ccast <std::shared_ptr<A const> > (v));
        }

        {
                A const a (668);
                Variant v (a); // Tworzy handler SMART, bo v zawiera teraz kopię a.
                BOOST_REQUIRE (ccast <A> (v));
                BOOST_REQUIRE (ccast <A *> (v));
                BOOST_REQUIRE (ccast <A const *> (v));
                BOOST_REQUIRE (ccast <A &> (v));
                BOOST_REQUIRE (ccast <A const &> (v));
                BOOST_REQUIRE (ccast <std::shared_ptr<A> > (v));
                BOOST_REQUIRE (ccast <std::shared_ptr<A const> > (v));
        }

        {
                A a (668);
                A *pa = &a;
                Variant v (pa); // Tworzy handler POINTER
                BOOST_REQUIRE (ccast <A> (v));
                BOOST_REQUIRE (ccast <A *> (v));
                BOOST_REQUIRE (ccast <A const *> (v));
                BOOST_REQUIRE (ccast <A &> (v));
                BOOST_REQUIRE (ccast <A const &> (v));
#ifdef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE (ccast <std::shared_ptr<A> > (v));
                BOOST_REQUIRE (ccast <std::shared_ptr<A const> > (v));
#else
                BOOST_REQUIRE (!(ccast <std::shared_ptr<A> > (v)));
                BOOST_REQUIRE (!(ccast <std::shared_ptr<A const> > (v)));
#endif
        }

        {
                A const a (668);
                A const *cpa = &a;
                Variant v (cpa); // Tworzy handler POINTER_CONST
                BOOST_REQUIRE (ccast <A> (v));
                BOOST_REQUIRE (!(ccast <A *> (v)));
                BOOST_REQUIRE (ccast <A const *> (v));
                BOOST_REQUIRE (!(ccast <A &> (v)));
                BOOST_REQUIRE (ccast <A const &> (v));
#ifdef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE (!ccast <std::shared_ptr<A> > (v));
                BOOST_REQUIRE (ccast <std::shared_ptr<A const> > (v));
#else
                BOOST_REQUIRE (!(ccast <std::shared_ptr<A> > (v)));
                BOOST_REQUIRE (!(ccast <std::shared_ptr<A const> > (v)));
#endif
        }

        {
                A a (668);
                A &ra = a;
                Variant v (ra); // Tworzy handler SMART, bo v zawiera teraz kopię a.
                BOOST_REQUIRE (ccast <A> (v));
                BOOST_REQUIRE (ccast <A *> (v));
                BOOST_REQUIRE (ccast <A const *> (v));
                BOOST_REQUIRE (ccast <A &> (v));
                BOOST_REQUIRE (ccast <A const &> (v));
                BOOST_REQUIRE (ccast <std::shared_ptr<A> > (v));
                BOOST_REQUIRE (ccast <std::shared_ptr<A const> > (v));
        }

        {
                A const a (668);
                A const *cpa = &a;
                Variant v (cpa); // Tworzy handler SMART, bo v zawiera teraz kopię a.
                BOOST_REQUIRE (ccast <A> (v));
                BOOST_REQUIRE (!(ccast <A *> (v)));
                BOOST_REQUIRE (ccast <A const *> (v));
                BOOST_REQUIRE (!(ccast <A &> (v)));
                BOOST_REQUIRE (ccast <A const &> (v));
#ifdef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE (!ccast <std::shared_ptr<A> > (v));
                BOOST_REQUIRE (ccast <std::shared_ptr<A const> > (v));
#else
                BOOST_REQUIRE (!(ccast <std::shared_ptr<A> > (v)));
                BOOST_REQUIRE (!(ccast <std::shared_ptr<A const> > (v)));
#endif
        }

        {
                std::shared_ptr <A> a (new A (668));
//                std::cerr << a.use_count () << std::endl;
                Variant v (a); // Tworzy handler SMART
//                std::cerr << a.use_count () << std::endl;
                BOOST_REQUIRE (ccast <A> (v));
                BOOST_REQUIRE (ccast <A *> (v));
                BOOST_REQUIRE (ccast <A const *> (v));
                BOOST_REQUIRE (ccast <A &> (v));
                BOOST_REQUIRE (ccast <A const &> (v));
                BOOST_REQUIRE ((ccast <std::shared_ptr<A> > (v)));
                BOOST_REQUIRE ((ccast <std::shared_ptr<A const> > (v)));
        }

        {
                std::shared_ptr <A const> a (new A (668));
                Variant v (a); // Tworzy handler SMART_CONST
                BOOST_REQUIRE (ccast <A> (v));
                BOOST_REQUIRE (!(ccast <A *> (v)));
                BOOST_REQUIRE (ccast <A const *> (v));
                BOOST_REQUIRE (!(ccast <A &> (v)));
                BOOST_REQUIRE (ccast <A const &> (v));
                BOOST_REQUIRE (!(ccast <std::shared_ptr<A> > (v)));
                BOOST_REQUIRE ((ccast <std::shared_ptr<A const> > (v)));
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
                BOOST_REQUIRE (ccast <I *> (v));
                BOOST_REQUIRE (ccast <I const *> (v));
                BOOST_REQUIRE ((ccast <I &> (v)));
                BOOST_REQUIRE ((ccast <I const &> (v)));
#ifdef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE (ccast <std::shared_ptr<I> > (v));
                BOOST_REQUIRE (ccast <std::shared_ptr<I const> > (v));
#else
                BOOST_REQUIRE (!(ccast <std::shared_ptr<I> > (v)));
                BOOST_REQUIRE (!(ccast <std::shared_ptr<I const> > (v)));
#endif
        }

        {
                I const*pa = (I *)0x01;
                Variant v (pa); // Tworzy handler CONST_POINTER
                BOOST_REQUIRE (!(ccast <I *> (v)));
                BOOST_REQUIRE (ccast <I const *> (v));
                BOOST_REQUIRE (!(ccast <I &> (v)));
                BOOST_REQUIRE ((ccast <I const &> (v)));
                BOOST_REQUIRE (!(ccast <std::shared_ptr<I> > (v)));
#ifdef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE (ccast <std::shared_ptr<I const> > (v));
#else
                BOOST_REQUIRE (!(ccast <std::shared_ptr<I const> > (v)));
#endif
        }

        {
                extern I &func (void);
                Variant v (func ()); // Tworzy handler SMART zawierający kopię wartości zwr.
                BOOST_REQUIRE ((ccast <I *> (v)));
                BOOST_REQUIRE (ccast <I const *> (v));
                BOOST_REQUIRE (ccast <I &> (v));
                BOOST_REQUIRE ((ccast <I const &> (v)));
                BOOST_REQUIRE ((ccast <std::shared_ptr<I> > (v)));
                BOOST_REQUIRE ((ccast <std::shared_ptr<I const> > (v)));
        }

        {
                extern I const &func2 (void);
                Variant v (func2 ()); // Tworzy handler SMART zawierający kopię wartości zwr.
                BOOST_REQUIRE ((ccast <I *> (v)));
                BOOST_REQUIRE (ccast <I const *> (v));
                BOOST_REQUIRE ((ccast <I &> (v)));
                BOOST_REQUIRE ((ccast <I const &> (v)));
                BOOST_REQUIRE ((ccast <std::shared_ptr<I> > (v)));
                BOOST_REQUIRE ((ccast <std::shared_ptr<I const> > (v)));
        }

        {
                extern std::shared_ptr<I> func3 ();
                Variant v (func3 ()); // Tworzy handler SMART
                BOOST_REQUIRE (ccast <I *> (v));
                BOOST_REQUIRE (ccast <I const *> (v));
                BOOST_REQUIRE ((ccast <I &> (v)));
                BOOST_REQUIRE ((ccast <I const &> (v)));
                BOOST_REQUIRE ((ccast <std::shared_ptr<I> > (v)));
                BOOST_REQUIRE ((ccast <std::shared_ptr<I const> > (v)));
        }

        {
                extern std::shared_ptr<I const> func4 ();
                Variant v (func4 ()); // Tworzy handler CONST_SMART
                BOOST_REQUIRE (!ccast <I *> (v));
                BOOST_REQUIRE (ccast <I const *> (v));
                BOOST_REQUIRE (!(ccast <I &> (v)));
                BOOST_REQUIRE ((ccast <I const &> (v)));
                BOOST_REQUIRE (!(ccast <std::shared_ptr<I> > (v)));
                BOOST_REQUIRE ((ccast <std::shared_ptr<I const> > (v)));
        }
}

/**
 * Wszystkie możliwe kasty do i z warianta. Typ kompletny polimorficzny kast, OCAST.
 */
BOOST_AUTO_TEST_CASE (testCustomPolymorphic)
{
        {
                C a (668);
                Variant v (a); // Tworzy handler z kopią.
                BOOST_REQUIRE ((occast <B> (v)));
                BOOST_REQUIRE ((occast <B *> (v)));
                BOOST_REQUIRE (occast <B const *> (v));
                BOOST_REQUIRE ((occast <B &> (v)));
                BOOST_REQUIRE ((occast <B const &> (v)));
                BOOST_REQUIRE ((occast <std::shared_ptr<B> > (v)));
                BOOST_REQUIRE ((occast <std::shared_ptr<B const> > (v)));
        }

        {
                C const a (668);
                Variant v (a); // Tworzy handler z kopią.
                BOOST_REQUIRE (occast <B> (v));
                BOOST_REQUIRE ((occast <B *> (v)));
                BOOST_REQUIRE (occast <B const *> (v));
                BOOST_REQUIRE ((occast <B &> (v)));
                BOOST_REQUIRE ((occast <B const &> (v)));
                BOOST_REQUIRE ((occast <std::shared_ptr<B> > (v)));
                BOOST_REQUIRE ((occast <std::shared_ptr<B const> > (v)));
        }

        {
                C c (668);
                C *pa = &c;
                Variant v (pa); // Tworzy handler OBJECT
                BOOST_REQUIRE ((occast <B> (v)));
                BOOST_REQUIRE (occast <B *> (v));
                BOOST_REQUIRE (occast <B const *> (v));
                BOOST_REQUIRE ((occast <B &> (v)));
                BOOST_REQUIRE ((occast <B const &> (v)));
#ifdef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE (occast <std::shared_ptr<B> > (v));
                BOOST_REQUIRE (occast <std::shared_ptr<B const> > (v));
#else
                BOOST_REQUIRE (!(occast <std::shared_ptr<B> > (v)));
                BOOST_REQUIRE (!(occast <std::shared_ptr<B const> > (v)));
#endif
        }

        {
                C const c (668);
                C const *cpa = &c;
                Variant v (cpa); // Tworzy handler OBJECT_CONST
                BOOST_REQUIRE ((occast <B> (v)));
                BOOST_REQUIRE (!occast <B *> (v));
                BOOST_REQUIRE (occast <B const *> (v));
                BOOST_REQUIRE (!occast <B &> (v));
                BOOST_REQUIRE ((occast <B const &> (v)));
#ifdef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE (!occast <std::shared_ptr<B> > (v));
                BOOST_REQUIRE (occast <std::shared_ptr<B const> > (v));
#else
                BOOST_REQUIRE (!(occast <std::shared_ptr<B> > (v)));
                BOOST_REQUIRE (!(occast <std::shared_ptr<B const> > (v)));
#endif
        }

        {
                C c (668);
                C &ra = c;
                Variant v (ra); // Tworzy handler
                BOOST_REQUIRE ((occast <B> (v)));
                BOOST_REQUIRE (occast <B *> (v));
                BOOST_REQUIRE (occast <B const *> (v));
                BOOST_REQUIRE (occast <B &> (v));
                BOOST_REQUIRE ((occast <B const &> (v)));
                BOOST_REQUIRE ((occast <std::shared_ptr<B> > (v)));
                BOOST_REQUIRE ((occast <std::shared_ptr<B const> > (v)));
        }

        {
                C const c (668);
                C const &cpa = c;
                Variant v (cpa); // Tworzy handler
                BOOST_REQUIRE ((occast <B> (v)));
                BOOST_REQUIRE (occast <B *> (v));
                BOOST_REQUIRE (occast <B const *> (v));
                BOOST_REQUIRE (occast <B &> (v));
                BOOST_REQUIRE ((occast <B const &> (v)));
                BOOST_REQUIRE ((occast <std::shared_ptr<B> > (v)));
                BOOST_REQUIRE ((occast <std::shared_ptr<B const> > (v)));
        }

        {
                std::shared_ptr <C> a (new C (668));
                Variant v (a); // Tworzy handler SMART_OBJECT
                BOOST_REQUIRE ((occast <B> (v)));
                BOOST_REQUIRE (occast <B *> (v));
                BOOST_REQUIRE (occast <B const *> (v));
                BOOST_REQUIRE ((occast <B &> (v)));
                BOOST_REQUIRE ((occast <B const &> (v)));
                BOOST_REQUIRE ((occast <std::shared_ptr<B> > (v)));
                BOOST_REQUIRE ((occast <std::shared_ptr<B const> > (v)));
        }

        {
                std::shared_ptr <C const> a (new C (668));
                Variant v (a); // Tworzy handler SMART_OBJECT
                BOOST_REQUIRE ((occast <B> (v)));
                BOOST_REQUIRE (!(occast <B *> (v)));
                BOOST_REQUIRE (occast <B const *> (v));
                BOOST_REQUIRE (!(occast <B &> (v)));
                BOOST_REQUIRE ((occast <B const &> (v)));
                BOOST_REQUIRE (!(occast <std::shared_ptr<B> > (v)));
                BOOST_REQUIRE ((occast <std::shared_ptr<B const> > (v)));
        }

/****************************************************************************/

        {
                C c (668);
                Variant v (&c); // Tworzy handler OBJECT
                BOOST_REQUIRE ((occast <B> (v)));
                BOOST_REQUIRE (occast <B *> (v));
                BOOST_REQUIRE (occast <B const *> (v));
                BOOST_REQUIRE ((occast <B &> (v)));
                BOOST_REQUIRE ((occast <B const &> (v)));
#ifdef ALLOW_CAST_TO_SMART
                BOOST_REQUIRE (occast <std::shared_ptr<B> > (v));
                BOOST_REQUIRE (occast <std::shared_ptr<B const> > (v));
#else
                BOOST_REQUIRE (!(occast <std::shared_ptr<B> > (v)));
                BOOST_REQUIRE (!(occast <std::shared_ptr<B const> > (v)));
#endif
        }

        {
                C c (668);
                B &b = c;
                Variant v (&b);
                BOOST_REQUIRE ((occast <C> (v)));
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
            BOOST_REQUIRE ((occast <C> (v)));
            BOOST_REQUIRE (occast <C *> (v));
            BOOST_REQUIRE (occast <C const *> (v));
            BOOST_REQUIRE ((occast <C &> (v)));
            BOOST_REQUIRE ((occast <C const &> (v)));
#ifdef ALLOW_CAST_TO_SMART
            BOOST_REQUIRE (occast <std::shared_ptr<C> > (v));
            BOOST_REQUIRE (occast <std::shared_ptr<C const> > (v));
#else
            BOOST_REQUIRE (!occast <std::shared_ptr<C> > (v));
            BOOST_REQUIRE (!occast <std::shared_ptr<C const> > (v));
#endif
    }

    {
            C c (668);
            B *pa = &c;
            Variant v (pa); // Tworzy handler OBJECT
            BOOST_REQUIRE (!occast <A> (v));
            BOOST_REQUIRE (!occast <A *> (v));
            BOOST_REQUIRE (!occast <I const *> (v));
            BOOST_REQUIRE (!occast <A &> (v));
            BOOST_REQUIRE (!occast <A const &> (v));
            BOOST_REQUIRE (!occast <std::shared_ptr<A> > (v));
            BOOST_REQUIRE (!occast <std::shared_ptr<A const> > (v));
    }

}

class I { int i; };
I globalI;
std::shared_ptr <I> globalP (new I);

I &func () { return globalI; }
I const &func2 () { return globalI; }
std::shared_ptr<I> func3 () { return globalP; }
std::shared_ptr<I const> func4 () { return globalP; }

BOOST_AUTO_TEST_SUITE_END ();
