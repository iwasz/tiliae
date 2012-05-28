/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BaseClassAnnotation.h"

namespace Reflection {

std::string BaseClassAnnotation::toString () const
{
//        return "BaseClassAnnotation (className:'" + className + "', baseClassList:'" + baseClassList.toString () + "')";
        // TODO wypisywanie listy.
        return "BaseClassAnnotation (className:'" + className + "', baseClassList:'TODO')";
}

std::string BaseClassAnnotation::getHash () const
{
        std::string s = className;

        for (Core::StringList::const_iterator i = baseClassList.begin (); i != baseClassList.end (); ++i) {
                s += *i;
        }

        return s;
}

}
