/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/make_shared.hpp>
#include "ClassInternalsVisitor.h"
#include "reflectAnnotations/MethodAnnotation.h"
#include "reflectAnnotations/FieldAnnotation.h"
#include "reflectAnnotations/BaseClassAnnotation.h"
#include "reflectAnnotations/ConstructorAnnotation.h"
#include "model/Method.h"
#include "model/Field.h"
#include "model/Class.h"
#include "Manager.h"
#include "Pointer.h"
#include "model/Constructor.h"

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
