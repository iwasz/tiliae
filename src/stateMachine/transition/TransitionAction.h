/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TRANSITIONACTION_H_
#define TRANSITIONACTION_H_

#include "action/IAction.h"
#include <list>
#include "../../core/Pointer.h"
#include "../../core/string/String.h"
#include "../../core/ApiMacro.h"

namespace StateMachine {

/**
 * Modeluje transition action.
 * \ingroup StateMachine
 */
class TILIAE_API TransitionAction {
public:

        explicit TransitionAction (const std::string &f = std::string (),
                          const std::string &t = std::string (),
                          Ptr <IAction> a = Ptr <IAction> ()) : fromState (f), toState (t), action (a) {}

        static Ptr <TransitionAction> create (const std::string &f = std::string (),
                        const std::string &t = std::string (),
                        Ptr <IAction> a = Ptr <IAction> ()) { return Ptr <TransitionAction> (new TransitionAction (f, t, a)); }

        Ptr <IAction> getAction () const { return action; }
        void setAction (Ptr <IAction> action) { this->action = action; }

        std::string getFromState () const { return fromState; }
        void setFromState (const std::string &fromState) { this->fromState = fromState; }

        std::string getToState () const { return toState; }
        void setToState (const std::string &toState) { this->toState = toState; }

        bool operator== (const TransitionAction &a) const { return a.fromState == fromState && a.toState == toState && a.action == action; }

private:

        std::string fromState;
        std::string toState;
        Ptr <IAction> action;

};

typedef std::list <Ptr <TransitionAction> > TransitionActionList;

}

#endif /* TRANSITIONACTION_H_ */
