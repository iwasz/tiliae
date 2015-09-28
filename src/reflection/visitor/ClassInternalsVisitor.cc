/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef WITH_ANNOTATIONS
#include <boost/make_shared.hpp>
#include "ClassInternalsVisitor.h"
#include "reflection/reflectAnnotations/MethodAnnotation.h"
#include "reflection/reflectAnnotations/FieldAnnotation.h"
#include "reflection/reflectAnnotations/BaseClassAnnotation.h"
#include "reflection/reflectAnnotations/ConstructorAnnotation.h"
#include "reflection/model/Method.h"
#include "reflection/model/Field.h"
#include "reflection/model/Class.h"
#include "reflection/Manager.h"
#include "reflection/model/Constructor.h"
#include "core/Pointer.h"

namespace Reflection {
using namespace Core;

Core::Variant ClassInternalsVisitor::visit (MethodAnnotation *a, Class *cls)
{
        cls->addMethod (new Method (a->getMethodName (), a->getWrapper ()));
        return Variant ();
}

Core::Variant ClassInternalsVisitor::visit (FieldAnnotation *a, Class *cls)
{
        cls->addField (new Field (a->getFielddName(), a->getWrapper ()));
        return Variant ();
}

Core::Variant ClassInternalsVisitor::visit (ConstructorAnnotation *a, Class *cls)
{
        cls->addConstructor (new Constructor (a->getConstructorPointer()));
        return Variant ();
}

Core::Variant ClassInternalsVisitor::visit (BaseClassAnnotation *a, Class *cls)
{
        cls->addBaseClassNames (a->getBaseClassList ());
        return Core::Variant ();
}

}
#endif
