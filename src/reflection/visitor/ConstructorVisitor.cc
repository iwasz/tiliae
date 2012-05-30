/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/make_shared.hpp>

#include "ConstructorVisitor.h"
#include "reflectAnnotations/ConstructorAnnotation.h"
#include "model/Constructor.h"
#include "Manager.h"
#include "../../core/Pointer.h"

using namespace Core;

namespace Reflection {

Core::Variant ConstructorVisitor::visit (ConstructorAnnotation *a, const Core::Variant &arg)
{
        return Variant (new Constructor (a->getConstructorPointer()));
}

}
