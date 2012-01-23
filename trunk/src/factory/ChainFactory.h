/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CHAINFACTORY_H_
#define CHAINFACTORY_H_

#include "IFactory.h"
#include "../core/ApiMacro.h"
#include <Reflection.h>

namespace Factory {

/**
 * Fabryka, która zawiera łańcuch innych fabryk (w określonej przez usera
 * kolejności) i próbuje po kolei je uruchamiać. Pierwsza która zwróci coś
 * co nie jest Variant.isNone, wygrywa i ten wynik zostaje zwrócony.
 */
class TILIAE_API ChainFactory : public IFactory {
public:

        REFLECTION_CONSTRUCTOR_ (void)

        virtual ~ChainFactory () {}
        virtual Core::Variant create (const Core::VariantMap &parameters = Core::VariantMap (), Core::Context *context = NULL) const;

        REFLECTION_METHOD (setFactories) void setFactories (Factory::FactoryVector const &f) { factories = f; }
        void addFactory (Ptr <Factory::IFactory> f) { factories.push_back (f); }
        Factory::FactoryVector const &getFactories () const { return factories; }

private:

        Factory::FactoryVector factories;

        REFLECTION_END (ChainFactory)
};

}

#	endif /* CHAINFACTORY_H_ */
