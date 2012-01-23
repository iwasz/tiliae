/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IBEANWRAPPER_H_
#define IBEANWRAPPER_H_

#include <string>
#include "IPropertyAccessor.h"
#include "../core/ApiMacro.h"
#include "../core/Exception.h"

namespace Wrapper {

/**
 * Interfejs klas, które potrafią wrapować jeden obiekt (przekazywany
 * jako wariant) i udostępniają go jako IPropertyAccessor. Właściwości
 * tego wrapowanego obiektu to jego metody (gettery i settery).
 */
class TILIAE_API IBeanWrapper : public IPropertyAccessor {
public:

        virtual ~IBeanWrapper () {}

        /**
         * Ustawia wrapowany obiekt. Jeśli już jakiś jest, to jest on
         * zamazywany. Ta metoda zadziała tak samo jak użycie metody
         * set z pustą ścieżką.
         */
        virtual void setWrappedObject (const Core::Variant &obj) = 0;

        /**
         * Zwraca wrapowany obiekt. Ta metoda zadziała tak samo jak użycie
         * metody get z pustą ścieżką.
         */
        virtual Core::Variant getWrappedObject () const = 0;

        virtual void set (const std::string &path, const Core::Variant &object, Core::Context *ctx = NULL) = 0;
        virtual void add (const std::string &path, const Core::Variant &object, Core::Context *ctx = NULL) = 0;
        virtual Core::Variant get (const std::string &path, Core::Context *ctx = NULL) const = 0;
        virtual Ptr <Core::IIterator> iterator (const std::string &path, Core::Context *ctx = NULL) const = 0;

        virtual void set (Core::Variant *bean, const std::string &path, const Core::Variant &object, Core::Context *ctx = NULL) = 0;
        virtual void add (Core::Variant *bean, const std::string &path, const Core::Variant &object, Core::Context *ctx = NULL) = 0;
        virtual Core::Variant get (const Core::Variant *bean, const std::string &path, Core::Context *ctx = NULL) const = 0;
        virtual Ptr <Core::IIterator> iterator (const Core::Variant *bean, const std::string &path, Core::Context *ctx = NULL) const = 0;

};

/**
 * Wyjątek ogólny.
 */
struct TILIAE_API BeanWrapperException : public Core::Exception {

        BeanWrapperException (const std::string &m = "") : Core::Exception (m) {}
        virtual ~BeanWrapperException () throw () {}
};

/**
 * Zrzucany, kiedy nie udało się znaleźć settera.
 */
struct TILIAE_API PropertyNotSettableException : public BeanWrapperException {

        PropertyNotSettableException (const std::string &m = "") : BeanWrapperException (m) {}
        virtual ~PropertyNotSettableException () throw () {}
};

/**
 * Zrzucany, kiedy nie udało się znaleźć gettera.
 */
struct TILIAE_API PropertyNotGettableException : public BeanWrapperException {

        PropertyNotGettableException (const std::string &m = "") : BeanWrapperException (m) {}
        virtual ~PropertyNotGettableException () throw () {}
};

} // namespace

#endif /* IBEANWRAPPER_H_ */
