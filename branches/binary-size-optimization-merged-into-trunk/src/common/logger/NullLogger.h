/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef NULLLOGGER_H_
#define NULLLOGGER_H_

#include "ILogger.h"

namespace Common {

/**
 * Simple logger, which does not make any output. It is like
 * one have used Console logger and redirected the output to
 * /dev/null.
 */
class TILIAE_API NullLogger : public Common::ILogger {
public:
        virtual ~NullLogger () {}
        void log (const std::string &) {}
};

}

#endif /* NULLLOGGER_H_ */
