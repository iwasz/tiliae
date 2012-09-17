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
#include "core/variant/Variant.h"

namespace Reflection {
class Class;

/**
 * Wizytujący tworzączy metod, pola, i inne składniki obiektu Class. Za usuwanie ich z pamieci
 * jest odpowiedzialny sam obiekt Class.
 */
class ClassInternalsVisitor : public IReflectionVisitor {
public:

        virtual ~ClassInternalsVisitor () {}

        virtual Core::Variant visit (BaseClassAnnotation *a, Class *cls);
        virtual Core::Variant visit (MethodAnnotation *a, Class *cls);
        virtual Core::Variant visit (FieldAnnotation *a, Class *cls);
        virtual Core::Variant visit (ConstructorAnnotation *a, Class *cls);
        virtual Core::Variant visit (ClassAnnotation *a, Class *cls) { return Core::Variant (); }

};

}

#endif /* CLASSVISITOR_H_ */
