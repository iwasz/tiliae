/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ChainFactory.h"

namespace Factory {

ChainFactory::~ChainFactory ()
{
        if (deleteContents) {
                for (FactoryVector::iterator i = factories.begin (); i != factories.end (); ++i) {
                        delete *i;
                }
        }
}

Core::Variant ChainFactory::create (const Core::VariantMap &parameters, Core::DebugContext *context) const
{
        Core::Variant result;
        dcBegin (context);

        for (FactoryVector::const_iterator i = factories.begin (); i != factories.end (); ++i) {
                result = (*i)->create (parameters, context);

                if (!result.isNone ()) {
                        dcRollback (context);
                        return result;
                }
        }

        dcError (context, "ChainFactory::create : none of child factories has succeeded.");
        dcCommit (context);
        return Core::Variant ();
}

}
