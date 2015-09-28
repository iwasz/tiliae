/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef WITH_ANNOTATIONS
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

        for (Core::StringVector::const_iterator i = baseClassList.begin (); i != baseClassList.end (); ++i) {
                s += *i;
        }

        return s;
}

}

#endif
