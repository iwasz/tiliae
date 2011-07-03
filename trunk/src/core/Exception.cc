/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <sstream>
#include "Exception.h"

namespace Core {

Exception::Exception (std::string const &s)
{
        if (s.empty ()) {
                msgCount = 0;
        }
        else {
                message = "1. " + s;
                msgCount = 1;
        }
}

void Exception::setMessage (std::string const &m)
{
        message += "1. " + m;
        msgCount = 1;
}

void Exception::addMessage (std::string const &m)
{
        std::ostringstream str;
        str << "\n" << ++msgCount << ". " << m;
        message += str.str ();
}

}
