/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "IntObject.h"

namespace StateMachine {

Core::VariantList IntObject::run () const
{
        Core::VariantList ret;

        if (object == match) {
                ret.push_back (Core::Variant (getName () + "_EQUAL"));
        }
        else {
                ret.push_back (Core::Variant (getName () + "_NOTEQUAL"));

                if (object > match) {
                        ret.push_back (Core::Variant (getName () + "_GREATER"));
                }

                if (object < match) {
                        ret.push_back (Core::Variant (getName () + "_LOWER"));
                }

        }

        return ret;
}

}

