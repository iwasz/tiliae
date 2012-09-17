/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STATE_MACHINE_EXCEPTIONS_H_
#define STATE_MACHINE_EXCEPTIONS_H_

#include "core/Exception.h"
#include "core/ApiMacro.h"

namespace StateMachine {

struct TILIAE_API UndefinedStateException : public Core::Exception {
        UndefinedStateException (const std::string &m = "") : Core::Exception (m) {}
        virtual ~UndefinedStateException () throw () {}
};

struct TILIAE_API DuplicateStateException : public Core::Exception {
        DuplicateStateException (const std::string &m = "") : Core::Exception (m) {}
        virtual ~DuplicateStateException () throw () {}
};

/**
 * Something wrong with a condition.
 */
struct TILIAE_API ConditionException : public Core::Exception {
        ConditionException (Core::Exception const &e) : Core::Exception (e.what ()) {}
        ConditionException (const std::string &m = "") : Core::Exception (m) {}
        virtual ~ConditionException () throw () {}
};

}

#endif /* EXCEPTIONS_H_ */
