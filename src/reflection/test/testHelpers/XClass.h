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
#include "reflectAnnotations/ConstructorAnnotation.h"
#include "reflectAnnotations/FactoryMethodAnnotation.h"
#include "reflectAnnotations/DefaultAnnotationMacros.h"

/**
 *
 */
struct X {

        // Konstruktor bezargumentowy.
        __c (void);

        // Metody
        _m(getChar)
        char getChar () const { return 'a'; }

        _m(setChar)
        void setChar (char c) {}

        _m(getInt)
        int getInt () const { return 1; }

        _m(setInt)
        void setInt (int i) {}

        // Adnotacja inicjująca
        _e(X)
};

typedef std::list <X *> XList;
// TODO
//_f (XList);

typedef std::vector <X *> XVector;
// TODO
//_f (XVector);

typedef std::set <X *> XSet;
// TODO
//_f (XSet);

typedef std::stack <X *> XStack;
// TODO
//_f (XStack);

typedef std::map <Core::String, X *> XMap;
// TODO
//_f (XMap);

#endif /* XCLASS_H_ */
