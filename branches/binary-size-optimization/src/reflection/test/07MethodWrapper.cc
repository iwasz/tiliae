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

#include "../../core/Pointer.h"
#include "../wrapper/ICallableWrapper.h"
#include "../wrapper/MethodWrapper.h"

BOOST_AUTO_TEST_SUITE (CallableWrapper);

using namespace boost;
using namespace Core;
using namespace Reflection;

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

//template <typename T>
//struct Moja { int i; };
//
//template <typename T>
//void moja (T t)
//{
//
//}
//
//struct T1 {
//
//	void f () {}
//
//	void fun ()
//	{
////        createMethodWrapper (f);
//		moja (&Me::f);
//	}
//
//	typedef T1 Me;
//
//};
//
//struct T2 : public T1 {
//
//	void g () {}
//
//	void fun ()
//	{
////        createMethodWrapper (f);
//		moja (&Me::g);
//	}
//
//	typedef T2 Me;
//};

/**
 * Testuje, czy uruchamia się właściwa metoda.
 */
BOOST_AUTO_TEST_CASE (testBasicCall0)
{
        Ptr <ICallableWrapper> wrp;
        VariantVector args;
        Variant ret;

        TestClass testClass;
        TestClass const testClassConst;

        Variant vo (&testClass);
        Variant const voc (&testClass);

        Variant vc (&testClassConst);
        Variant const vcc (&testClassConst);

/******* 0 argumentów *******************************************************/

        wrp = createMethodWrapper (&TestClass::a);
        ret = wrp->call (vo, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'a');
        ret = wrp->call (voc, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'a');
        BOOST_REQUIRE_THROW ((wrp->call (vc, &args)), VariantCastException);
        BOOST_REQUIRE_THROW ((wrp->call (vcc, &args)), VariantCastException);

        wrp = createMethodWrapper (&TestClass::b);
        ret = wrp->call (vo, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'b');
        ret = wrp->call (voc, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'b');

        wrp = createMethodWrapper (&TestClass::c);
        ret = wrp->call (vo, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'c');
        ret = wrp->call (voc, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'c');
        BOOST_REQUIRE_THROW ((wrp->call (vc, &args)), VariantCastException);
        BOOST_REQUIRE_THROW ((wrp->call (vcc, &args)), VariantCastException);

        wrp = createMethodWrapper (&TestClass::d);
        ret = wrp->call (vo, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'd');
        ret = wrp->call (voc, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'd');
}

/**
 * Testuje, czy uruchamia się właściwa metoda.
 */
BOOST_AUTO_TEST_CASE (testBasicCall1)
{
        Ptr <ICallableWrapper> wrp;
        VariantVector args;
        Variant ret;

        TestClass testClass;
        TestClass const testClassConst;

        Variant vo (&testClass);
        Variant const voc (&testClass);

        Variant vc (&testClassConst);
        Variant const vcc (&testClassConst);

/******* 1 argument *********************************************************/

        wrp = createMethodWrapper (&TestClass::e);
        args.clear ();
        // Czy ze złą ilością argumentów zrzuci wyjątek?
        BOOST_REQUIRE_THROW ((ret = wrp->call (vo, &args)), WrapperException);
        BOOST_REQUIRE_THROW ((ret = wrp->call (voc, &args)), WrapperException);
        args.clear ();
        args.push_back (Variant (123));
        ret = wrp->call (vo, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'e');
        ret = wrp->call (voc, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'e');
        BOOST_REQUIRE_THROW ((wrp->call (vc, &args)), VariantCastException);
        BOOST_REQUIRE_THROW ((wrp->call (vcc, &args)), VariantCastException);

        wrp = createMethodWrapper (&TestClass::f);
        args.clear ();
        BOOST_REQUIRE_THROW ((ret = wrp->call (vo, &args)), WrapperException);
        BOOST_REQUIRE_THROW ((ret = wrp->call (voc, &args)), WrapperException);
        args.clear ();
        args.push_back (Variant (123));
        ret = wrp->call (vo, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'f');
        ret = wrp->call (voc, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'f');

        wrp = createMethodWrapper (&TestClass::g);
        args.clear ();
        // Czy ze złą ilością argumentów zrzuci wyjątek?
        BOOST_REQUIRE_THROW ((ret = wrp->call (vo, &args)), WrapperException);
        BOOST_REQUIRE_THROW ((ret = wrp->call (voc, &args)), WrapperException);
        args.clear ();
        args.push_back (Variant (123));
        ret = wrp->call (vo, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'g');
        ret = wrp->call (voc, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'g');
        BOOST_REQUIRE_THROW ((wrp->call (vc, &args)), VariantCastException);
        BOOST_REQUIRE_THROW ((wrp->call (vcc, &args)), VariantCastException);

        wrp = createMethodWrapper (&TestClass::h);
        args.clear ();
        BOOST_REQUIRE_THROW ((ret = wrp->call (vo, &args)), WrapperException);
        BOOST_REQUIRE_THROW ((ret = wrp->call (voc, &args)), WrapperException);
        args.clear ();
        args.push_back (Variant (123));
        ret = wrp->call (vo, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'h');
        ret = wrp->call (voc, &args);
        BOOST_REQUIRE_EQUAL (testClass.value, 'h');

/*--------------------------------------------------------------------------*/




}

BOOST_AUTO_TEST_SUITE_END ();
