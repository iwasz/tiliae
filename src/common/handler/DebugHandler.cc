/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DebugHandler.h"
#include "Foreach.h"

namespace Common {

Core::Variant DebugHandler::run (const Core::VariantList &params)
{
        std::string ret = debug;

        foreach (Core::Variant v, params) {
                if (can_cast <std::string> (v)) {
                        ret += " " + vcast <std::string> (v);
                }
        }

        if (output) {
                *output += ret;
        }

        return Core::Variant (ret);
}

}
