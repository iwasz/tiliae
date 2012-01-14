/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STM_TRANSITION_H_
#define STM_TRANSITION_H_

#include <list>
#include <map>
#include "action/IAction.h"
#include "context/MachineContext.h"
#include "TransitionAction.h"
#include "TransitionActionContainer.h"
#include "../../core/Pointer.h"
#include "../../core/string/String.h"
#include "../../reflection/reflectAnnotations/CollectionAnnotation.h"
#include "../../reflection/reflectAnnotations/ConstructorAnnotation.h"
#include "../../reflection/reflectAnnotations/MethodAnnotation.h"
#include "../../reflection/annotations/Macros.h"
#include "../../core/ApiMacro.h"

namespace StateMachine {
class ICondition;

/**
 * Podobnie jak klasa State, Transition też jest głównie tylko
 * kontenerem na konfigurację, a brudna robota odbywa się w
 * Machine.
 * \ingroup StateMachine
 */
class TILIAE_API Transition {
public:
        c__ (void)

        Transition () {}

        Transition (const std::string &t,
                    Ptr <ICondition> c,
                    Ptr <IAction> action = Ptr <IAction> ());

        static Ptr <Transition> create (const std::string &f,
                        const std::string &t,
                        Ptr <ICondition> c,
                        Ptr <IAction> action = Ptr <IAction> ())
        {
                return Ptr <Transition> (new Transition (/*f,*/ t, c, action));
        }

/*--------------------------------------------------------------------------*/

        bool checkCondition (MachineContext *context) const;

/*--------------------------------------------------------------------------*/

        std::string getToState () const { return toState; }
        m_ (setToState) void setToState (const std::string &toState) { this->toState = toState; }

        m_ (getCondition) Ptr<ICondition> getCondition () const { return condition; }
        m_ (setCondition) void setCondition (Ptr<ICondition> condition) { this->condition = condition; }

        /**
         * Te akcje zostaną dodane do listy wyjść podczas wykonywania
         * przejścia.
         */
        ActionList getTransitionActions () const { return transitionActions; }
        m_ (setTransitionActions) void setTransitionActions (const ActionList &transitionActions) { this->transitionActions = transitionActions; }
        void addTransitionAction (Ptr <IAction> transitionAction) { transitionActions.push_back (transitionAction); }
        void removeTransitionAction (Ptr <IAction> transitionAction) { transitionActions.remove (transitionAction); }

private:

        std::string toState;
        Ptr <ICondition> condition;
        ActionList transitionActions;

        e_ (Transition)
};

typedef std::list <Ptr <Transition> > TransitionList;
g_ (TransitionList)

} // namespace

#endif /* TRANSITION_H_ */
