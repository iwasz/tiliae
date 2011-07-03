/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include "ConsoleLogger.h"
#include "../../core/string/String.h"

namespace Common {

void ConsoleLogger::log (const Core::String &message)
{
        std::cerr << message << std::endl;
}

}
