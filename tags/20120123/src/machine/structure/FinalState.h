/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FINALSTATE_H_
#define FINALSTATE_H_

#include "State.h"

namespace Machine {

class FinalState : public State {
public:
        virtual ~FinalState () {}
};

} /* namespace Machine */

#	endif /* FINALSTATE_H_ */
