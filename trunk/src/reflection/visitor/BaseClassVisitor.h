/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BASE_CLASS_VISITOR_H_
#define BASE_CLASS_VISITOR_H_

#include "IReflectionVisitor.h"

namespace Reflection {

class Class;

/**
 * Zwraca klase z managera, lub tworzy i dodaje, jeśli w mamagerze
 * jej nie ma.
 */
class BaseClassVisitor : public IReflectionVisitor {
public:

        virtual ~BaseClassVisitor () {}

        virtual Core::Variant visit (BaseClassAnnotation *a, const Core::Variant &arg);
        virtual Core::Variant visit (MethodAnnotation *a, const Core::Variant &arg) { return Core::Variant (); }
        virtual Core::Variant visit (ConstructorAnnotation *a, const Core::Variant &arg) { return Core::Variant (); }
        virtual Core::Variant visit (ClassAnnotation *a, const Core::Variant &arg) { return Core::Variant (); }

};

}

#endif /* CLASSVISITOR_H_ */
