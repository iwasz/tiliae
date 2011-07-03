/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ChainFactory.h"

namespace Factory {

Core::Variant ChainFactory::create (const Core::VariantMap &parameters, Common::Context *context) const
{
        Core::Variant result;

        for (FactoryVector::const_iterator i = factories.begin (); i != factories.end (); ++i) {
                result = (*i)->create (parameters, context);

                if (!result.isNone ()) {
                        return result;
                }
        }

        return result;
}

}
