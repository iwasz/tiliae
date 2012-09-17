/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ILOGGER_H_
#define ILOGGER_H_

#include <string>
#include "core/string/String.h"
#include "core/ApiMacro.h"

namespace Common {

/**
 * Służy do logowania debagów.
 */
struct TILIAE_API ILogger {

        virtual ~ILogger () {}
        virtual void log (const std::string &message) = 0;

};

}

#endif /* ILOGGER_H_ */
