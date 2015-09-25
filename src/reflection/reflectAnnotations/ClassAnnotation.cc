/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef REFLECTION_ENABLED
#include <sstream>
#include "ClassAnnotation.h"

namespace Reflection {

std::string ClassAnnotation::toString () const
{
        std::ostringstream o;

        o << "ClassAnnotation (className:'" << className
          << "', typeInfo : " << type.name()
          << ", &typeInfo : " << (unsigned long int)&type << ")";

        return o.str ();
}

void ClassAnnotation::deleteDuplicate ()
{
        delete deleter;
}

} // notebook
#endif
