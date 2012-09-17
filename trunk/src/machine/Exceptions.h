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

namespace Machine {

struct TILIAE_API StateException : public Core::Exception {
        StateException (const std::string &m = "") : Core::Exception (m) {}
        virtual ~StateException () throw () {}
};

struct TILIAE_API UndefinedStateException : public StateException {
        UndefinedStateException (const std::string &m = "") : StateException (m) {}
        virtual ~UndefinedStateException () throw () {}
};

struct TILIAE_API DuplicateStateException : public StateException {
        DuplicateStateException (const std::string &m = "") : StateException (m) {}
        virtual ~DuplicateStateException () throw () {}
};

/**
 * Something wrong with a condition.
 */
struct TILIAE_API ConditionException : public StateException {
        ConditionException (Core::Exception const &e) : StateException (e.what ()) {}
        ConditionException (const std::string &m = "") : StateException (m) {}
        virtual ~ConditionException () throw () {}
};

}

#endif /* EXCEPTIONS_H_ */
