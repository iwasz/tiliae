/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef INPUTACTIONS_H_
#define INPUTACTIONS_H_

#include <list>
#include "Reflection.h"
#include "condition/ICondition.h"
#include "action/IAction.h"
#include "context/MachineContext.h"
#include "../core/Pointer.h"
#include "../core/ApiMacro.h"

namespace StateMachine {

/**
 * I've noticed, that in some FSM imlementations there is no such
 * thing like this one. In some implementations it can be seen as
 * transitions from A to A. Such transition in fact does not cause
 * the state to change, but only invokes some actions upon certain
 * conditions (guard conditions).
 *
 * In other words - this class imlements actions which are invoked
 * when condition (as a filed) is satisfied.
 * \ingroup StateMachine
 */
class TILIAE_API InputActions {
public:
        __c (void)

        InputActions () {}
        InputActions (Ptr <ICondition> c, const ActionList &a) : condition (c), actions (a) {}
        InputActions (Ptr <ICondition> c, Ptr <IAction> a) : condition (c) { actions.push_back (a); }

        static Ptr <InputActions> create (Ptr <ICondition> c, const ActionList &a) { return Ptr <InputActions> (new InputActions (c, a)); }
        static Ptr <InputActions> create (Ptr <ICondition> c, Ptr <IAction> a) { return Ptr <InputActions> (new InputActions (c, a)); }

        bool checkCondition (MachineContext *context) const;
        ActionList checkConditionAndGetActions (MachineContext *context) const;

/*--------------------------------------------------------------------------*/

        Ptr<ICondition> getCondition () const { return condition; }
        _m (setCondition) void setCondition (Ptr<ICondition> condition) { this->condition = condition; }

        ActionList getActions () const { return actions; }
        _m (setActions) void setActions (ActionList actions) { this->actions = actions; }
        _m (setAction) void setAction (Ptr <IAction> a) { actions.clear(); actions.push_back (a); }

private:

        Ptr <ICondition> condition;
        ActionList actions;

        _e (InputActions)
};

typedef std::list <Ptr <InputActions> > InputActionsList;
_g (InputActionsList)

} // nam

#endif /* INPUTACTIONS_H_ */
