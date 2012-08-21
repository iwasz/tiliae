/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef REFLECTIONFACTORY_H_
#define REFLECTIONFACTORY_H_

#include <Reflection.h>
#include "IFactory.h"
#include "../core/ApiMacro.h"
#include "../core/variant/Variant.h"
#include "../core/Typedefs.h"

namespace Factory {

/**
 * Przykład fabryki korzystającej z refleksji. Typy skalarne obsługiwane
 * przez wariant tworzy z pominięciem refleksji.
 */
class TILIAE_API ReflectionFactory : public Factory::IFactory {
public:

        static const char *CLASS_NAME;
        static const char *CONSTRUCTOR_ARGS;
        static const char *CREATE_DELETER;

        /**
         * wrapInSharedPtr == false -> return new T.
         * wrapInSharedPtr == true -> return boost::shared_ptr <T> (new T).
         */
        ReflectionFactory (bool w = false) : wrapInSharedPtr (w) {}
        virtual ~ReflectionFactory () {}

        /**
         *
         * @param parameters
         * @return
         */
        virtual Core::Variant create (const Core::VariantMap &parameters, Core::DebugContext *context = NULL) const;

private:

        bool wrapInSharedPtr;
};

}

#endif /* REFLECTIONFACTORY_H_ */
