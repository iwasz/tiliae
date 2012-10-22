/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONSOLELOGGER_H_
#define CONSOLELOGGER_H_

#include "ILogger.h"
#include <string>

namespace Common {

/**
 * Poprostu wypisuje na ekran.
 */
class TILIAE_API ConsoleLogger : public ILogger {
public:

        virtual ~ConsoleLogger () {}
        virtual void log (const std::string &message);

};

}

#endif /* CONSOLELOGGER_H_ */
