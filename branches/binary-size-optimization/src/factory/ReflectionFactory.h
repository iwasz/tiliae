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
struct TILIAE_API ReflectionFactory : public Factory::IFactory {


        static const char *CLASS_NAME;
        static const char *CONSTRUCTOR_ARGS;

        virtual ~ReflectionFactory () {}

        /**
         *
         * @param parameters
         * @return
         */
        virtual Core::Variant create (const Core::VariantMap &parameters, Core::DebugContext *context = NULL) const;

        REFLECTION_END_ (ReflectionFactory)
};

}

#endif /* REFLECTIONFACTORY_H_ */
