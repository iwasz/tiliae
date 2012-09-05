/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "XmlString.h"
#include "XmlException.h"

namespace Xml {

XmlString::operator std::string () const
{
        if (body) {
                return std::string (CONST_CHAR_CAST (body));
        }

        if (bodyConst) {
                return std::string (CONST_CHAR_CAST (bodyConst));
        }

        throw XmlException ("XmlString");
}

}
