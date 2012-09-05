/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IOUTPUT_H_
#define IOUTPUT_H_

#include "../IMachinery.h"
#include "../../core/ApiMacro.h"

namespace StateMachine {

/**
 * Zbior outputów, marker interface.
 * \ingroup StateMachine
 */
struct TILIAE_API IOutput : public IMachinery {
        virtual ~IOutput () {}
};

}

#endif /* IOUTPUT_H_ */
