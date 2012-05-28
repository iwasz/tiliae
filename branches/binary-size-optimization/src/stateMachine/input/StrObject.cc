/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "StrObject.h"

namespace StateMachine {

Core::VariantList StrObject::run () const
{
        Core::VariantList ret;

        if (object.empty ()) {
                ret.push_back (Core::Variant (getName () + "_EMPTY"));
        }

        if (object == match) {
                ret.push_back (Core::Variant (getName () + "_MATCH"));
        }
        else {
                ret.push_back (Core::Variant (getName () + "_NOMATCH"));
        }

        return ret;
}

}

