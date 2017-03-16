/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef REFLECTIONTOOLS_636860_H
#define REFLECTIONTOOLS_636860_H

#include "core/Pointer.h"
#include "core/string/String.h"
#include "model/Method.h"

/****************************************************************************/

namespace Reflection {
class Method;
class Class;

class TILIAE_API ReflectionTools {
public:

        /**
         * Finds getter for field field in class cls. If field is not ,,gettable'',
         * or if error has occured it returns NULL; It looks for getXxxx and isXxxx
         * methods (regardless if method returns bool or not).
         */
        static Method *findGetter (Class *cls, const std::string &name);
        static Method *findMethod (Class *cls, const std::string &name);
        static Method *findSetter (Class *cls, const std::string &name);

        static std::string getGetterName (const std::string &fieldName, bool is = false);
        static std::string getSetterName (const std::string &fieldName);
        /**
         *  W przypadku bledu zwraca pusty String.
         */
        static std::string getFieldName (const std::string &getterOrSetterName);

        /**
         *  Gdy prefix jest "foo" znajdzie metody fooXxxx.
         */
        static MethodList getMethodsWithPrefix (Class *cls, const std::string &prefix);
        static MethodList getGetters (Class *cls);
        static MethodList getSetters (Class *cls);
};

} // namespace

#endif

