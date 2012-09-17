/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include "core/Exception.h"
#include "core/ApiMacro.h"

namespace Container {

/**
 * Ogólnego przeznaczenia.
 * \ingroup Container
 */
struct TILIAE_API ContainerException : public Core::Exception {
        ContainerException (std::string const &m = "") : Core::Exception (m) {}
        ContainerException (Core::DebugContext const &db, std::string const &s = "") : Core::Exception (db, s) {}
        virtual ~ContainerException () throw () {}
};

/**
 * Podobny do WrongReferenceException, zrzucany, gdy pobieramy bean
 * o nieistniejącym ID.
 * \ingroup Container
 */
struct TILIAE_API NoSuchBeanException : public ContainerException {
        NoSuchBeanException (std::string const &m = "") : ContainerException (m) {}
        virtual ~NoSuchBeanException () throw () {}
};

struct TILIAE_API TooDeepNestingException : public ContainerException {
        TooDeepNestingException (std::string const &m = "") : ContainerException (m) {}
        virtual ~TooDeepNestingException () throw () {}
};

struct TILIAE_API RoundReferenceException : public ContainerException {
        RoundReferenceException (std::string const &m = "") : ContainerException (m) {}
        virtual ~RoundReferenceException () throw () {}
};

/**
 * Thrown when one wants to instantiate an uninitialized
 * bean. For example when bean has references to other beans,
 * which are not available yet.
 * \ingroup Container
 */
struct TILIAE_API BeanNotFullyInitializedException : public ContainerException {
        BeanNotFullyInitializedException (std::string const &s = "") : ContainerException (s) {}
//        virtual ~BeanNotFullyInitializedException throw () {}
};

/**
 * Zrzucane podczas różnistych błędów podczas kostruowania metastruktury
 * z XMla.
 * \ingroup Container
 */
struct TILIAE_API XmlMetaServiceException : public ContainerException {
        XmlMetaServiceException (std::string const &msg = "") : ContainerException (msg) {}
//        virtual ~XmlMetaServiceException throw () {}
};

/**
 * Zrzucany w przypadku gdy ktoś zadeklaruje wartość
 * o niestniejącym typie lub o typie dla którego nie
 * można znaleźć pasującego edytora.
 * \ingroup Container
 */
struct TILIAE_API WrongEditorTypeException : public ContainerException {
        WrongEditorTypeException (std::string const &msg = "") : ContainerException (msg) {}
        virtual ~WrongEditorTypeException () throw () {}
};

/**
 * Zła konfiguracja XML, lub meta-struktury.
 */
struct TILIAE_API ConfigurationException : public ContainerException {
        ConfigurationException (std::string const &msg = "") : ContainerException (msg) {}
        virtual ~ConfigurationException () throw () {}
};

}

#	endif /* EXCEPTIONS_H_ */
