/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FSM_REGION_H_
#define FSM_REGION_H_

#include <vector>
#include "core/Pointer.h"

namespace Machine {
class State;
class Event;

class Region {
public:

        virtual ~Region () {}

        void event (Event *e);

private:

        Ptr <State> activeState;
};

//TODO Zmienic na jakiś inny wektor, na przykład ptr_vector, tylko coś się sypie.
typedef std::vector <Ptr <Region> > RegionVector;

} /* namespace Machine */

#	endif /* REGION_H_ */
