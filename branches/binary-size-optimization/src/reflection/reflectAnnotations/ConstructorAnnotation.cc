/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <sstream>
#include "ConstructorAnnotation.h"

namespace Reflection {

std::string ConstructorAnnotation::toString () const
{
        return "ConstructorAnnotation (className:'" + className + "')";
}

/****************************************************************************/

std::string ConstructorAnnotation::getHash () const
{
        return className +
               boost::lexical_cast <std::string> (constructorPointer->getArity ()) +
               constructorPointer->getType().name();
}

} // notebook
