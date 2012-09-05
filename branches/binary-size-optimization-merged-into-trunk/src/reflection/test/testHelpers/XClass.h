/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef XCLASS_H_
#define XCLASS_H_

#include <list>
#include <map>
#include <vector>
#include <set>
#include <stack>
#include "annotations/Annotations.h"
#include "reflectAnnotations/MethodAnnotation.h"
#include "reflectAnnotations/FieldAnnotation.h"
#include "reflectAnnotations/ConstructorAnnotation.h"
#include "reflectAnnotations/FactoryMethodAnnotation.h"
#include "reflectAnnotations/DefaultAnnotationMacros.h"

struct X0 {};

/**
 *
 */
struct X {

        // Konstruktor bezargumentowy.
        REFLECTION_CONSTRUCTOR_ (void);
        X () : d (1.2), s ("franio") {}


        // Metody
        REFLECTION_METHOD(getChar)
        char getChar () const { return 'a'; }

        REFLECTION_METHOD(setChar)
        void setChar (char c) {}

        REFLECTION_METHOD(getInt)
        int getInt () const { return 1; }

        REFLECTION_METHOD(setInt)
        void setInt (int i) {}

        REFLECTION_FIELD_VALUE (d);
        double d;

        REFLECTION_FIELD_VALUE (ii);
        double ii;

        std::string REFLECTION_FIELD_VALUE_INPLACE (s);

        X0 *getX0 () { return &x0; }

private:

        REFLECTION_FIELD_REFERENCE (x0);
        X0 x0;

        // Adnotacja inicjująca
        REFLECTION_END(X)
};

typedef std::list <X *> XList;
// TODO
//REFLECTION_FACTORY (XList);

typedef std::vector <X *> XVector;
// TODO
//REFLECTION_FACTORY (XVector);

typedef std::set <X *> XSet;
// TODO
//REFLECTION_FACTORY (XSet);

typedef std::stack <X *> XStack;
// TODO
//REFLECTION_FACTORY (XStack);

typedef std::map <Core::String, X *> XMap;
// TODO
//REFLECTION_FACTORY (XMap);

#endif /* XCLASS_H_ */
