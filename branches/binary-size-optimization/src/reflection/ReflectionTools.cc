/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include <boost/algorithm/string/case_conv.hpp>

#include "ReflectionTools.h"
#include "model/Class.h"
#include "model/Method.h"

namespace Reflection {
using Core::Variant;

/****************************************************************************/

Ptr <Method> ReflectionTools::findGetter (Ptr <Class> cls, const std::string &name)
{
        assert (cls);

        std::string methodName = getGetterName (name);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << methodName << std::endl;
#endif

        Ptr <Method> getter = cls->getMethod (methodName);
        return getter;
}

/****************************************************************************/

Ptr <Method> ReflectionTools::findMethod (Ptr <Class> cls, const std::string &name)
{
        assert (cls);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << methodName << std::endl;
#endif

        return cls->getMethod (name);
}

/****************************************************************************/

std::string ReflectionTools::getGetterName (const std::string &fieldName)
{
        std::string methodName = "get" + fieldName;
        methodName[3] = std::toupper (methodName[3]);
        return methodName;
}

/****************************************************************************/

Ptr <Method> ReflectionTools::findSetter (Ptr <Class> cls,  const std::string &name)
{
        assert (cls);

        std::string methodName = getSetterName (name);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << methodName << std::endl;
#endif

        // TODO Tu powinno być sprawdzenie argumentu, albo chociaż 1 zamiast tego 0. Ale nie działa.
        Ptr <Method> setter = cls->getMethod (methodName);

        return setter;
}

/****************************************************************************/

std::string ReflectionTools::getSetterName (const std::string &fieldName)
{
        std::string methodName = "set" + fieldName;
        methodName[3] = std::toupper (methodName[3]);
        return methodName;
}

/****************************************************************************/

std::string ReflectionTools::getFieldName (const std::string &getterOrSetterName)
{
        if (getterOrSetterName.size () < 4)
                return std::string ();

        std::string name = getterOrSetterName.substr (0, 3);
        name.replace (0, 1, boost::algorithm::to_lower_copy (name.substr (0, 1)));
        return name;
}

/****************************************************************************/
// TODO test zrobic, nie wiadomo, czy dobrze dziala na stringu UTF8
MethodList ReflectionTools::getMethodsWithPrefix (Ptr <Class> cls, const std::string &prefix)
{
        assert (cls);

        MethodList allMethods = cls->getMethodList ();
        MethodList getters;

        unsigned int prefixLen = prefix.size ();

        for (MethodList::const_iterator i = allMethods.begin (); i != allMethods.end (); i++) {

                Ptr <Method> method = *i;
                std::string methodName = method->getName ();

                if (methodName.size () >= prefixLen + 1 &&
                    methodName.substr (0, prefixLen) == prefix &&
                    std::isupper (methodName[prefixLen])) {

                        getters.push_back (method);

                }
        }

        return getters;
}

/****************************************************************************/

MethodList ReflectionTools::getGetters (Ptr <Class> cls)
{
        return getMethodsWithPrefix (cls, "get");
}

/****************************************************************************/

MethodList ReflectionTools::getSetters (Ptr <Class> cls)
{
        return getMethodsWithPrefix (cls, "set");
}

} // namespace

