/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef METHOD_VISITOR_H_
#define METHOD_VISITOR_H_

#include "IReflectionVisitor.h"
#include "../../core/variant/Variant.h"

namespace Reflection {
class Class;

/**
 *
 */
class MethodVisitor : public IReflectionVisitor {
public:

        virtual ~MethodVisitor () {}

        virtual Core::Variant visit (BaseClassAnnotation *a, const Core::Variant &arg) { return Core::Variant (); }
        virtual Core::Variant visit (MethodAnnotation *a, const Core::Variant &arg);
        virtual Core::Variant visit (ConstructorAnnotation *a, const Core::Variant &arg)  { return Core::Variant (); }
        virtual Core::Variant visit (ClassAnnotation *a, const Core::Variant &arg) { return Core::Variant (); }

};

}

#endif /* CLASSVISITOR_H_ */
