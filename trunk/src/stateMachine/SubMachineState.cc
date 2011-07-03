/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SubMachineState.h"
#include "Machine.h"
#include <cassert>

namespace StateMachine {

ActionList SubMachineState::getEntryActions (MachineContext *context) const
{
        assert (machine);
        ActionList ret = State::getEntryActions (context);
        machine->reset ();
        machine->run (context);
        return ret;

}

/****************************************************************************/

ActionList SubMachineState::getInputActions (MachineContext *context) const
{
        assert (machine);
        ActionList ret = State::getInputActions (context);
        machine->run (context);
        return ret;
}

/****************************************************************************/

ActionList SubMachineState::getExitActions (MachineContext *ctx) const
{
        return State::getExitActions (ctx);
}

}
