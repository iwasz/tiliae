/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MethodAnnotation.h"
#include <boost/lexical_cast.hpp>

namespace Reflection {

std::string MethodAnnotation::toString () const
{
        return "MethodAnnotation (className:'" + className + "', methodName:'" + methodName + "', callableWrapper:'" +
                className + boost::lexical_cast <std::string> (((unsigned long int)callableWrapper)) + "')";
}

}
