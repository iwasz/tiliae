/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BaseClassVisitor.h"
#include "reflectAnnotations/BaseClassAnnotation.h"

using namespace Core;

namespace Reflection {

Core::Variant BaseClassVisitor::visit (BaseClassAnnotation *a, const Core::Variant &)
{
        return Core::Variant (a->getBaseClassList());
}

}
