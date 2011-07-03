/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <sstream>
#include "Context.h"

namespace Common {

#if defined (TILIAE_DEBUG)

void Context::addFatal (std::string const &errorMessage)
{
        fatal = true;
        std::ostringstream str;

        if (msgCount) {
                str << "\n";
        }

        str << ++msgCount << ". FATAL: " << errorMessage;
        message += str.str ();
}

void Context::addError (std::string const &errorMessage)
{
        error = true;
        std::ostringstream str;

        if (msgCount) {
                str << "\n";
        }

        str << ++msgCount << ". ERROR: " << errorMessage;
        message += str.str ();
}

#endif

} // nam
