/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BooleanObject.h"

namespace StateMachine {

Core::VariantList BooleanObject::run () const
{
        Core::VariantList ret;
        ret.push_back (Core::Variant (getName () + ((object) ? "_TRUE" : "_FALSE")));
        return ret;
}

}

