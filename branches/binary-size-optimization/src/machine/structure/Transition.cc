/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include <boost/bind.hpp>
#include "Transition.h"
#include "Trigger.h"

namespace Machine {

bool Transition::match (Event *e)
{
        return std::find_if (
                        triggers.begin (),
                        triggers.end (),
                        boost::bind (&Trigger::match, _1, e)
        ) != triggers.end ();
}

} // namsp
