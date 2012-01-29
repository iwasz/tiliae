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
#include <Reflection.h>
#include "IFactory.h"
#include "../core/Pointer.h"
#include "../core/Typedefs.h"
#include "../core/variant/Variant.h"
#include "../core/ApiMacro.h"

namespace Factory {

/**
 * Nakladka na inną fabryke. Można jej ustawic parametry na stale
 * i te parametry beda podawane do wewnetrznej fabryki.
 * TODO Ta nazwa jest myląca i nic nie wyjaśnia - zawsze trzeba
 * spojrzeć do dokumentacji, żeby się skapnąć co ona robi.
 */
class TILIAE_API ProxyFactory : public IFactory {
public:
        REFLECTION_CONSTRUCTOR_ (void)

        ProxyFactory () {}
        ProxyFactory (Ptr <IFactory> f, const Core::VariantMap &p) : factory (f), params (p) {}
        virtual ~ProxyFactory () {}

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

        Ptr<IFactory> getFactory () const { return factory; }
        REFLECTION_SETTER (setFactory) void setFactory (Ptr<IFactory> factory) { this->factory = factory; }

        Core::VariantMap getParams () const { return params; }
        REFLECTION_METHOD (setParams) void setParams (const Core::VariantMap &params) { this->params = params; }

private:

        Ptr <IFactory> factory;
        Core::VariantMap params;

        REFLECTION_END (ProxyFactory)
};

}

#endif /* PROXYFACTORY_H_ */
