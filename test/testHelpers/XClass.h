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
#include "reflection/annotations/Annotations.h"
#include "reflection/reflectAnnotations/MethodAnnotation.h"
#include "reflection/reflectAnnotations/FieldAnnotation.h"
#include "reflection/reflectAnnotations/ConstructorAnnotation.h"
#include "reflection/reflectAnnotations/FactoryMethodAnnotation.h"

struct X0 {};

/**
 *
 */
struct __tiliae_reflect__ X {

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

//private:

        REFLECTION_FIELD_REFERENCE (x0);
        X0 x0;

        // Adnotacja inicjująca
        REFLECTION_END(X)
};

typedef std::list <X *> XList;
typedef std::vector <X *> XVector;
typedef std::set <X *> XSet;
typedef std::stack <X *> XStack;
typedef std::map <std::string, X *> XMap;

#endif /* XCLASS_H_ */
