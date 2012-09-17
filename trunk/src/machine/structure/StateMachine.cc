/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include <string>
#include "StateMachine.h"
#include "Event.h"

namespace Machine {
using namespace Common;
using namespace std;
using boost::bind;

void StateMachine::event (Event *e, PseudoState *defaultEntry)
{
        for (RegionVector::iterator i = regions.begin (); i != regions.end (); ++i) {
                (*i)->event (e);
        }
}

} // namespace
