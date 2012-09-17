/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ITRIGGER_H_
#define ITRIGGER_H_

#include <vector>
#include "core/Pointer.h"
#include "Event.h"

namespace Machine {

class Trigger {
public:

        /**
         * Checks whether incoming event should be accepted or denied.
         */
        bool match (Event *e);

        Ptr <Event> getEvent () const { return event; }
        void setEvent (Ptr <Event> event) { this->event = event; }

private:

        Ptr <Event> event;
};

// TODO inny
typedef std::vector <Ptr <Trigger> > TriggerVector;

} /* namespace Machine */

#	endif /* ITRIGGER_H_ */
