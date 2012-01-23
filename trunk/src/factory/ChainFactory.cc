/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ChainFactory.h"

namespace Factory {

Core::Variant ChainFactory::create (const Core::VariantMap &parameters, Core::Context *context) const
{
        Core::Variant result;
        unsigned int errCnt = 0;

        for (FactoryVector::const_iterator i = factories.begin (); i != factories.end (); ++i) {
                result = (*i)->create (parameters, context);

                if (!result.isNone ()) {
                        return result;
                }
                else {
                        ++errCnt;
                }
        }

        if (errCnt >= factories.size ()) {
                error (context, FactoryException, UNDEFINED_ERROR, "ChainFactory::create : none of child factories has succeeded.");
        }

        return result;
}

}
