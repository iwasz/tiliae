/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LAZY_FACTORY_H_
#define LAZY_FACTORY_H_

#include "IFactory.h"
#include <cassert>
#include "../core/variant/Cast.h"
#include "../core/variant/Variant.h"
#include "../core/Typedefs.h"
#include "../core/ApiMacro.h"
#include "../core/Pointer.h"

namespace Factory {

/**
 * To działa w prosty sposób:
 * 1. Uruchomienie create powoduje uruchomienie fabryki factory, która tworzy obiekt.
 * 2. Obiekt jest kastowany na IFactory.
 * 3. Tworzenie (create) jest delegowana do tej nowej fabryki..
 * TODO Test.
 */
class TILIAE_API LazyFactory : public IFactory {
public:

        LazyFactory () {}
        LazyFactory (Ptr <Factory::IFactory> f) : factory (f) {}
        virtual ~LazyFactory () {}

/*--------------------------------------------------------------------------*/

        virtual Core::Variant create (const Core::VariantMap &parameters = Core::VariantMap (), Core::DebugContext *context = NULL) const
        {
                assert (factory);
                Core::Variant vFac = factory->create (Core::VariantMap (), context);
                Ptr <IFactory> fac = ocast <Ptr <IFactory> > (vFac);

                if (!fac) {
                        dcError (context, "LazyFactory cam't create factory");
                        return Core::Variant ();
                }

                return fac->create (parameters, context);
        }

        Ptr <Factory::IFactory> getFactory () const { return factory; }
        void setFactory (Ptr <Factory::IFactory> factory) { this->factory = factory; }

private:

        Ptr <Factory::IFactory> factory;
};

}

#endif
