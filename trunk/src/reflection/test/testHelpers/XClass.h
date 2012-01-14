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
        c__ (void);

        // Metody
        m_(getChar)
        char getChar () const { return 'a'; }

        m_(setChar)
        void setChar (char c) {}

        m_(getInt)
        int getInt () const { return 1; }

        m_(setInt)
        void setInt (int i) {}

        // Adnotacja inicjująca
        e_(X)
};

typedef std::list <X *> XList;
// TODO
//f_ (XList);

typedef std::vector <X *> XVector;
// TODO
//f_ (XVector);

typedef std::set <X *> XSet;
// TODO
//f_ (XSet);

typedef std::stack <X *> XStack;
// TODO
//f_ (XStack);

typedef std::map <Core::String, X *> XMap;
// TODO
//f_ (XMap);

#endif /* XCLASS_H_ */
