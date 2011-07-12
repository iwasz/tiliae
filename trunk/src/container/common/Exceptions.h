/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include "../../core/Exception.h"
#include "../../core/ApiMacro.h"

namespace Container {

/**
 * Ogólnego przeznaczenia.
 * \ingroup Container
 */
struct TILIAE_API ContainerException : public Core::Exception {
        ContainerException (std::string const &m = "") : Core::Exception (m) {}
        virtual ~ContainerException () throw () {}
};

/**
 * Podobny do WrongReferenceException, zrzucany, gdy pobieramy bean
 * o nieistniejącym ID.
 * \ingroup Container
 */
struct TILIAE_API NoSuchBeanException : public Core::Exception {
        NoSuchBeanException (std::string const &m = "") : Core::Exception (m) {}
        virtual ~NoSuchBeanException () throw () {}
};

struct TILIAE_API TooDeepNestingException : public ContainerException {
        TooDeepNestingException (std::string const &m = "") : ContainerException (m) {}
        virtual ~TooDeepNestingException () throw () {}
};

/**
 * Thrown when one wants to instantiate an uninitialized
 * bean. For example when bean has references to other beans,
 * which are not available yet.
 * \ingroup Container
 */
struct TILIAE_API BeanNotFullyInitializedException : public Core::Exception {
        BeanNotFullyInitializedException (std::string const &s = "") : Core::Exception (s) {}
//        virtual ~BeanNotFullyInitializedException throw () {}
};

/**
 * Zrzucane podczas różnistych błędów podczas kostruowania metastruktury
 * z XMla.
 * \ingroup Container
 */
struct TILIAE_API XmlMetaServiceException : public Core::Exception {
        XmlMetaServiceException (std::string const &msg = "") : Core::Exception (msg) {}
//        virtual ~XmlMetaServiceException throw () {}
};

/**
 * Zrzucany w przypadku gdy ktoś zadeklaruje wartość
 * o niestniejącym typie lub o typie dla którego nie
 * można znaleźć pasującego edytora.
 * \ingroup Container
 */
struct TILIAE_API WrongEditorTypeException : public Core::Exception {
        WrongEditorTypeException (std::string const &msg = "") : Core::Exception (msg) {}
        virtual ~WrongEditorTypeException () throw () {}
};

}

#	endif /* EXCEPTIONS_H_ */
