/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ALWAYS_H_
#define ALWAYS_H_

#include "IMachinery.h"
#include "../core/ApiMacro.h"

namespace StateMachine {

/**
 * Dodaje input "ALWAYS". Do użycia z ChainMachinery
 * \ingroup StateMachine
 */
struct TILIAE_API Always : public IMachinery {

        virtual ~Always () {}
        virtual void run (MachineContext *context);

};

}

#endif /* ALWAYS_H_ */
