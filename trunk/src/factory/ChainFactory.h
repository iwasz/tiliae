/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CHAINFACTORY_H_
#define CHAINFACTORY_H_

#include "factory/IFactory.h"
#include "core/ApiMacro.h"
#include "reflection/Reflection.h"

namespace Factory {

/**
 * Fabryka, która zawiera łańcuch innych fabryk (w określonej przez usera
 * kolejności) i próbuje po kolei je uruchamiać. Pierwsza która zwróci coś
 * co nie jest Variant.isNone, wygrywa i ten wynik zostaje zwrócony.
 */
class TILIAE_API ChainFactory : public IFactory {
public:

        REFLECTION_CONSTRUCTOR_ (void)

        ChainFactory () : deleteContents (false) {}
        ChainFactory (bool b) : deleteContents (b) {}
        virtual ~ChainFactory ();

        virtual Core::Variant create (const Core::VariantMap &parameters = Core::VariantMap (), Core::DebugContext *context = NULL) const;

        REFLECTION_METHOD (setFactories) void setFactories (Factory::FactoryVector const &f) { factories = f; }
        void addFactory (Factory::IFactory *f) { factories.push_back (f); }
        Factory::FactoryVector const &getFactories () const { return factories; }

private:

        FactoryVector factories;
        bool deleteContents;

        REFLECTION_END (ChainFactory)
};

}

#	endif /* CHAINFACTORY_H_ */
