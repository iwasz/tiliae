/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Region.h"
#include "State.h"
#include "../Event.h"

namespace Machine {

void Region::event (Event *e)
{
        // TODO Czy jest możliwe, ze to będzie null?
        if (activeState) {
                activeState->event (e);
        }
}

} /* namespace Machine */
