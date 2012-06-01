/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONSTRUCTOR_VISITOR_H_
#define CONSTRUCTOR_VISITOR_H_

#include "IReflectionVisitor.h"

namespace Reflection {

class Class;

/**
 * Zwraca klase z managera, lub tworzy i dodaje, jeśli w mamagerze
 * jej nie ma.
 */
class ConstructorVisitor : public IReflectionVisitor {
public:

        virtual ~ConstructorVisitor () {}

        virtual Core::Variant visit (BaseClassAnnotation *a, const Core::Variant &arg) { return Core::Variant (); }
        virtual Core::Variant visit (MethodAnnotation *a, const Core::Variant &arg) {  return Core::Variant (); }
        virtual Core::Variant visit (ConstructorAnnotation *a, const Core::Variant &arg);
        virtual Core::Variant visit (ClassAnnotation *a, const Core::Variant &arg) { return Core::Variant (); }

};

}

#endif /* CLASSVISITOR_H_ */