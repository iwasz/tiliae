/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SCALARFACTORY_H_
#define SCALARFACTORY_H_

#include "IFactory.h"
#include "../core/Typedefs.h"
#include "../core/ApiMacro.h"

namespace Factory {

/**
 * Zwraca skalary. Naśladuje fabrykę ReflectionFactroy (te same nazwy argumentów
 * w mapie) ale nie używa do tego refleksji, tylko zwraca proste Varianty.
 */
class TILIAE_API ScalarFactory : public IFactory {
public:

        virtual ~ScalarFactory () {}
        virtual Core::Variant create (const Core::VariantMap &parameters = Core::VariantMap (), Core::DebugContext *context = NULL) const;

};

}

#	endif /* SCALARFACTORY_H_ */
