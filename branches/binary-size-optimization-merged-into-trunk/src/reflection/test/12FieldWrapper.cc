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
#include "../wrapper/FieldWrapper.h"

/*##########################################################################*/


BOOST_AUTO_TEST_SUITE (FieldWrapper12);

using namespace boost;
using namespace Core;
using namespace Reflection;

struct A {

};

class TestClass2 {
public:

        TestClass2 () : i (12), d (12.3), s ("Franek"), a (&x) {}

        double getD() const { return d; }
        void setD(double d) { this->d = d; }

        int getI() const { return i; }
        void setI(int i) { this->i = i; }

        std::string const &getS() const { return s; }
        void setS(std::string const &s) { this->s = s; }

//private:

        int i;
        double d;
        std::string s;
        A x;
        A *a;

};

/**
 *
 */
BOOST_AUTO_TEST_CASE (testGet)
{
        TestClass2 testClass;
        TestClass2 const testClassConst;

        Variant vo (&testClass);
        Variant const voc (&testClass);

        Variant vc (&testClassConst);
        Variant const vcc (&testClassConst);
        Variant ret;

        IFieldWrapper *fw = createFieldWrapper (&TestClass2::i);
        BOOST_REQUIRE_EQUAL (vcast <int> (fw->get (vo)), 12);
        BOOST_REQUIRE_EQUAL (vcast <int> (fw->get (voc)), 12);
        BOOST_REQUIRE_EQUAL (vcast <int> (fw->get (vc)), 12);
        BOOST_REQUIRE_EQUAL (vcast <int> (fw->get (vcc)), 12);

        fw = createFieldWrapper (&TestClass2::d);
        BOOST_REQUIRE_EQUAL (vcast <double> (fw->get (vo)), 12.3);
        BOOST_REQUIRE_EQUAL (vcast <double> (fw->get (voc)), 12.3);
        BOOST_REQUIRE_EQUAL (vcast <double> (fw->get (vc)), 12.3);
        BOOST_REQUIRE_EQUAL (vcast <double> (fw->get (vcc)), 12.3);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testSet)
{
        TestClass2 testClass;
        Variant vo (&testClass);
        Variant const voc (&testClass);
        Variant ret;

        IFieldWrapper *fw = createFieldWrapper (&TestClass2::i);
        fw->set (vo, Variant (13));
        BOOST_REQUIRE_EQUAL (testClass.i, 13);
        fw->set (voc, Variant (14));
        BOOST_REQUIRE_EQUAL (testClass.i, 14);

        fw = createFieldWrapper (&TestClass2::d);
        fw->set (vo, Variant (13.4));
        BOOST_REQUIRE_EQUAL (testClass.d, 13.4);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testString)
{
        TestClass2 testClass;
        Variant vo (&testClass);
        Variant ret;

        IFieldWrapper *fw = createFieldWrapper (&TestClass2::s);
        BOOST_REQUIRE_EQUAL (vcast <std::string> (fw->get (vo)), "Franek");

        fw->set (vo, Variant ("Asia"));
        BOOST_REQUIRE_EQUAL (testClass.s, "Asia");
}

BOOST_AUTO_TEST_SUITE_END ();
