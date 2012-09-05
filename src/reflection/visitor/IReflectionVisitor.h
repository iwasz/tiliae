/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IREFLECTIONVISITOR_H_
#define IREFLECTIONVISITOR_H_

#include "../../core/variant/Variant.h"

namespace Reflection {
class BaseClassAnnotation;
class ConstructorAnnotation;
class MethodAnnotation;
class FieldAnnotation;
class ClassAnnotation;
class Class;

/**
 * Kapsułkuje operacje na adnotacjach refleksyjnych.
 */
struct IReflectionVisitor {

        virtual ~IReflectionVisitor () {}

        virtual Core::Variant visit (BaseClassAnnotation *a, Class *cls) = 0;
        virtual Core::Variant visit (MethodAnnotation *a, Class *cls) = 0;
        virtual Core::Variant visit (FieldAnnotation *a, Class *cls) = 0;
        virtual Core::Variant visit (ConstructorAnnotation *a, Class *cls) = 0;
        virtual Core::Variant visit (ClassAnnotation *a, Class *cls) = 0;

};

}

#endif /* IREFLECTIONVISITOR_H_ */
