/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_REFLECT_EXCEPTIONS_H
#define TILIAE_REFLECT_EXCEPTIONS_H

#include <string>
#include <boost/lexical_cast.hpp>
#include "core/Exception.h"
#include "core/ApiMacro.h"

namespace Reflection {

/**
 *  Raised when you pass wrong number of arguments to Method::invoke method.
 */
struct TILIAE_API WrongNumberOfArgumentsException : public Core::Exception {
        WrongNumberOfArgumentsException (int is, int shouldBe) :
                Core::Exception (std::string ("Wrong number of arguments. Is : ") +
                 boost::lexical_cast <std::string> (is) + std::string (", expected : ") +
                 boost::lexical_cast <std::string> (shouldBe)) {}

        virtual ~WrongNumberOfArgumentsException () throw () {}
};

/**
 *
 */
struct TILIAE_API AnnotationException : public Core::Exception {

        AnnotationException (std::string const &s) : Core::Exception (s) {}
        virtual ~AnnotationException () throw () {}

};

/**
 *
 */
struct TILIAE_API NullMethodPointerException : public Core::Exception {

        NullMethodPointerException () : Core::Exception ("MethodPointer is null during invocation of a method.") {}
        virtual ~NullMethodPointerException () throw () {}

};

/**
 *
 */
struct TILIAE_API NoSuchKeyException : public Core::Exception {
        NoSuchKeyException () : Core::Exception ("No such key.") {}
        virtual ~NoSuchKeyException () throw () {}
};

/**
 *
 */
struct TILIAE_API NotIndexedException : public Core::Exception {
        NotIndexedException () : Core::Exception ("This class is not indexed. You may only call getTypeInfo ();") {}
        virtual ~NotIndexedException () throw () {}
};


/**
 *  
 */
struct TILIAE_API NoSuchBaseClassException : public Core::Exception {
        NoSuchBaseClassException (const std::string &n) : Core::Exception ("No such BaseClass. Name=" + n) {}
        virtual ~NoSuchBaseClassException () throw () {}
};

/**
 *
 */
struct TILIAE_API NoSuchConstructorException : public Core::Exception {
        NoSuchConstructorException (const std::string &n) : Core::Exception ("No such constructor. Name=" + n) {}
        virtual ~NoSuchConstructorException () throw () {}
};

/**
 *
 */
struct TILIAE_API NoSuchMethodException : public Core::Exception {
        NoSuchMethodException (const std::string &n) : Core::Exception ("No such method. Name=" + n) {}
        virtual ~NoSuchMethodException () throw () {}
};

struct TILIAE_API NoConstructorAnnotationException : public Core::Exception {
        NoConstructorAnnotationException (const std::string &s) : Core::Exception (s) {}
        virtual ~NoConstructorAnnotationException () throw () {}
};

struct TILIAE_API ManagerNotInitializedException : public Core::Exception {
        ManagerNotInitializedException (const std::string &s) : Core::Exception (s) {}
        virtual ~ManagerNotInitializedException () throw () {}
};

struct TILIAE_API ClassAllreadyManagedException : public Core::Exception {
        ClassAllreadyManagedException (const std::string &s) : Core::Exception (s) {}
        virtual ~ClassAllreadyManagedException () throw () {}
};

}

#endif

