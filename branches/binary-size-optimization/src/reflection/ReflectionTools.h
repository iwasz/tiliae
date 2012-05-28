/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef REFLECTIONTOOLS_636860_H
#define REFLECTIONTOOLS_636860_H

#include "../core/Pointer.h"
#include "../core/string/String.h"
#include "model/Method.h"

/****************************************************************************/

namespace Reflection {
class Method;
class Class;

class ReflectionTools {
public:

        /**
         *  Finds getter for field field in class cls. If field is not ,,gettable'',
         *  or if error has occured it returns NULL;
         */
        static Ptr <Method> findGetter (const Ptr <Class> cls, const std::string &name);
        static Ptr <Method> findMethod (const Ptr <Class> cls, const std::string &name);
        static Ptr <Method> findSetter (const Ptr <Class> cls, const std::string &name);

        static std::string getGetterName (const std::string &fieldName);
        static std::string getSetterName (const std::string &fieldName);
        /**
         *  W przypadku bledu zwraca pusty String.
         */
        static std::string getFieldName (const std::string &getterOrSetterName);

        /**
         *  Gdy prefix jest "foo" znajdzie metody fooXxxx.
         */
        static MethodList getMethodsWithPrefix (const Ptr <Class> cls, const std::string &prefix);
        static MethodList getGetters (const Ptr <Class> cls);
        static MethodList getSetters (const Ptr <Class> cls);
};

} // namespace

#endif

