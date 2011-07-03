/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ZeroHandler.h"

namespace Common {

Core::Variant ZeroHandler::run (const Core::VariantList &parms)
{
        ASSERT (handler, "");
        return handler->run (parms);
}

Core::Variant ZeroHandler::run ()
{
        ASSERT (handler, "");
        return handler->run (Core::VariantList ());
}


}
