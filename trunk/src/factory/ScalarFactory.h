/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SCALARFACTORY_H_
#define SCALARFACTORY_H_

#include "factory/IFactory.h"
#include "core/Typedefs.h"
#include "core/ApiMacro.h"

namespace Factory {

/**
 * Zwraca skalary. Naśladuje fabrykę ReflectionFactroy (te same nazwy argumentów
 * w mapie) ale nie używa do tego refleksji, tylko zwraca proste Varianty.
 */
class TILIAE_API ScalarFactory : public IFactory {
public:

        virtual ~ScalarFactory () {}
        virtual Core::Variant create (const Core::VariantMap &parameters = Core::VariantMap (), Core::DebugContext *context = NULL) const;

        /**
         * Nazwy typów obsługiwanych przez tą fabrykę.
         */
        static const char *SUPPORTED_TYPES[];

        /**
         * Odpowiada na pytanie czy podany typ (podany jako nazwa) jest obsługiwany przez tą fabrykę,
         * czyli czy umie ona stworzyć skalar tego typu.
         */
        static bool isTypeSupported (const char *name);
};

}

#	endif /* SCALARFACTORY_H_ */
