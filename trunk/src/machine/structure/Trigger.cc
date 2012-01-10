/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ITrigger.h"

namespace Machine {

bool Trigger::match (Event *e)
{
        return e->getName () == event->getName ();
}

} /* namespace Machine */
