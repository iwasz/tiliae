/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PROXYFACTORY_H_
#define PROXYFACTORY_H_

#include <algorithm>
#include <iterator>
#include "factory/IFactory.h"
#include "core/Pointer.h"
#include "core/Typedefs.h"
#include "core/variant/Variant.h"
#include "core/ApiMacro.h"

namespace Factory {

/**
 * Nakladka na inną fabryke. Można jej ustawic parametry na stale
 * i te parametry beda podawane do wewnetrznej fabryki.
 * TODO Ta nazwa jest myląca i nic nie wyjaśnia - zawsze trzeba
 * spojrzeć do dokumentacji, żeby się skapnąć co ona robi.
 */
class TILIAE_API ProxyFactory : public IFactory {
public:

        ProxyFactory (IFactory *f, const Core::VariantMap &p, bool d = false) : factory (f), params (p), deleteContents (d) {}
        virtual ~ProxyFactory ()
        {
                if (deleteContents) {
                        delete factory;
                }
        }

/*--------------------------------------------------------------------------*/

        virtual Core::Variant create (const Core::VariantMap &parameters = Core::VariantMap (), Core::DebugContext *context = NULL) const
        {
                Core::VariantMap tmp = params;
                std::copy (parameters.begin (), parameters.end (), std::inserter (tmp, tmp.end ()));

                if (factory) {
                        return factory->create (tmp, context);
                }

                return Core::Variant ();
        }

/*--------------------------------------------------------------------------*/

        IFactory *getFactory () const { return factory; }
        void setFactory (IFactory *factory) { this->factory = factory; }

        Core::VariantMap getParams () const { return params; }
        void setParams (const Core::VariantMap &params) { this->params = params; }

private:

        IFactory *factory;
        Core::VariantMap params;
        bool deleteContents;
};

}

#endif /* PROXYFACTORY_H_ */
