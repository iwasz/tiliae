/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/make_shared.hpp>
#include "ClassVisitor.h"
#include "reflectAnnotations/BaseClassAnnotation.h"
#include "reflectAnnotations/ConstructorAnnotation.h"
#include "reflectAnnotations/MethodAnnotation.h"
#include "reflectAnnotations/ClassAnnotation.h"
#include "reflectAnnotations/FieldAnnotation.h"
#include "model/Class.h"

namespace Reflection {
using namespace Core;

Core::Variant ClassVisitor::visit (BaseClassAnnotation *a, Class *cls)
{
        return Core::Variant (findClass (a->getClassName ()));
}

/****************************************************************************/

Core::Variant ClassVisitor::visit (MethodAnnotation *a, Class *cls)
{
        return Core::Variant (findClass (a->getClassName ()));
}

/****************************************************************************/

Core::Variant ClassVisitor::visit (FieldAnnotation *a, Class *cls)
{
        return Core::Variant (findClass (a->getClassName ()));
}

/****************************************************************************/

Core::Variant ClassVisitor::visit (ConstructorAnnotation *a, Class *cls)
{
        return Core::Variant (findClass (a->getClassName ()));
}

/****************************************************************************/

Core::Variant ClassVisitor::visit (ClassAnnotation *a, Class *cls)
{
        Class *clazz = findClass (a->getClassName ());

        if (!clazz) {
                clazz = createClass (a->getClassName (), a->getType ());
        }
        else {
                if (a->getType () != clazz->getType ()) {
                        std::ostringstream str;
                        str << "ClassAllreadyManagedException (" << clazz->getName () + "). "
                                "There is another class with this name with different type_info. Type info of stored class : [";
                        str << clazz->getType ().name () << ", " << (unsigned long int)&(clazz->getType ());
                        str << "], type_info of new class : [" << a->getType ().name () << ", " << (unsigned long int)&(a->getType ()) << "].";
                        throw ClassAllreadyManagedException (str.str ());
                }
        }

        return Core::Variant (clazz);
}

/****************************************************************************/

Class *ClassVisitor::findClass (const std::string &className) const
{
        // Dla każdej adnotacji pobrać nazwę klasy
        if (cache && className == cache->getName ()) {
                return cache;
        }

        // 3. Odszukać klasę po nazwie w kontenerze klas, jeśli nie ma, stworzyć.
        Class *clazz = Manager::classForNameImpl (className);

        if (!clazz) {
                return NULL;
        }

        return clazz;
}

/****************************************************************************/

Class *ClassVisitor::createClass (const std::string &className, std::type_info const &classType)
{
        Class *clazz = new Class (className, classType);
        Manager::add (clazz);
        cache = clazz;
        return clazz;
}

}
