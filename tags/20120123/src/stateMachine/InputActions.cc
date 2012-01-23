/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "InputActions.h"
#include <cassert>

namespace StateMachine {

bool InputActions::checkCondition (MachineContext *context) const
{
        assert (condition);
        return condition->check (context);
}

/****************************************************************************/

ActionList InputActions::checkConditionAndGetActions (MachineContext *context) const
{
        if (checkCondition (context)) {
                return actions;
        }

        return ActionList ();
}

}
