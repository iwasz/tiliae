/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <cassert>
#include "Transition.h"
#include "condition/ICondition.h"
#include "core/string/String.h"
#include "core/Pointer.h"

using namespace boost::lambda;

namespace StateMachine {

Transition::Transition (const std::string &t,
                    Ptr <ICondition> c,
                    Ptr <IAction> action) :
        toState (t),
        condition (c)
{
        if (action) {
                addTransitionAction (action);
        }
}

/****************************************************************************/

bool Transition::checkCondition (MachineContext *context) const
{
        assert (condition);
        return condition->check (context);
}

} // namsp
