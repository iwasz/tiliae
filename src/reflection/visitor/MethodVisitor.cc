/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/make_shared.hpp>
#include "MethodVisitor.h"
#include "../reflectAnnotations/MethodAnnotation.h"
#include "../model/Method.h"
#include "../Manager.h"
#include "../../core/Pointer.h"

namespace Reflection {
using namespace Core;

Core::Variant MethodVisitor::visit (MethodAnnotation *a, const Core::Variant &arg)
{
        return Variant (new Method (a->getMethodName (), a->getCallableWrapper ()));
}

}
