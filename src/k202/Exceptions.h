/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef K202_EXCEPTIONS_H_
#define K202_EXCEPTIONS_H_

#include "core/Exception.h"
#include "core/ApiMacro.h"

namespace k202 {

/**
 * Exceptions thrown by Compiler / Parser.
 */
struct TILIAE_API ParserException : public Core::Exception {

        ParserException (std::string const &m = "") : Core::Exception (m) {}
        virtual ~ParserException () throw () {}
};

/**
 *
 */
struct TILIAE_API StackEmptyException : public ParserException {

        StackEmptyException (std::string const &m = "") : ParserException (m) {}
        virtual ~StackEmptyException () throw () {}
};

struct TILIAE_API SyntaxErrorException : public ParserException {

        SyntaxErrorException (std::string const &m = "") : ParserException (m) {}
        virtual ~SyntaxErrorException () throw () {}
};

/**
 *
 */
struct TILIAE_API ByteCodeException : public Core::Exception {

        ByteCodeException (std::string const &m = "") : Core::Exception (m) {}
        virtual ~ByteCodeException () throw () {}
};


struct TILIAE_API RuntimeException : public Core::Exception {

        RuntimeException (Core::Exception const &e) : Core::Exception (e.what ()) {}
        RuntimeException (std::string const &m = "") : Core::Exception (m) {}
        virtual ~RuntimeException () throw () {}
};

}

#endif /* EXCEPTIONS_H_ */
