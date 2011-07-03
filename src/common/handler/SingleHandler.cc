/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SingleHandler.h"

namespace Common {

Core::Variant SingleHandler::run (const Core::VariantList &parms)
{
        ASSERT (handler, "");
        return handler->run (parms);
}

Core::Variant SingleHandler::run (const Core::Variant &input) const
{
        ASSERT (handler, "");
        Core::VariantList params;
        params.add (input);
        return handler->run (params);
}

}
