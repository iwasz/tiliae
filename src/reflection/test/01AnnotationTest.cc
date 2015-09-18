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
#include "reflection/annotations/AnnotationManager.h"
#include <vector>
#include "reflection/reflectAnnotations/CollectionAnnotation.h"

#include "reflection/Reflection.h"

BOOST_AUTO_TEST_SUITE (AnnotationTest);

using namespace boost;
using namespace Core;
using namespace Reflection;

/**
 * Klasa testujaca mechanizmy okolo klasy Class.
 */
BOOST_AUTO_TEST_CASE (testNumberOfAnnotations)
{
        int noOfAnnotations = Annotations::AnnotationManager::instance ().getAnnotationList ().size ();
        BOOST_REQUIRE (noOfAnnotations > 0);
}

struct Obj {
        virtual ~Obj () {}
        void function () { d = 2.2; }
        double d;
};

class TestX : public Obj {
        TestX () {}
        TestX (int j) : i (j) {}
        virtual ~TestX () {}

        void method () { i = 1; }

        int i ;
        std::string s;
        float f;
};

BOOST_AUTO_TEST_CASE (testResearch)
{
        Class *clazz = new Class ("Obj", typeid (Obj &), new Reflection::PtrDeleter <Obj>);
        Manager::add (clazz);
        clazz->addMethod (new Method ("function", createMethodWrapper (&Obj::function)));
        clazz->addField (new Field ("d", Reflection::createFieldWrapper (&Obj::d)));

//        cls->addConstructor (new Constructor (a->getConstructorPointer()));
//        cls->addBaseClassNames (a->getBaseClassList ());
}

BOOST_AUTO_TEST_SUITE_END ();
