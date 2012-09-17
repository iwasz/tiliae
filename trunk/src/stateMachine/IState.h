/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ISTATE_H_
#define ISTATE_H_

#include "action/IAction.h"
#include "context/MachineContext.h"
#include "transition/Transition.h"
#include "reflection/Reflection.h"
#include "core/Pointer.h"
#include <map>
#include <list>
#include "core/ApiMacro.h"

namespace StateMachine {

/**
 * Baza dla stanów.
 * \ingroup StateMachine
 */
struct TILIAE_API IState : public Core::Object {

        virtual ~IState () {}
        virtual std::string getName () const = 0;
        virtual ActionList getEntryActions (MachineContext *context = NULL) const = 0;
        virtual ActionList getExitActions (MachineContext *context = NULL) const = 0;
        virtual ActionList getInputActions (MachineContext *context) const = 0;
        virtual const TransitionList &getTransitions () const = 0;
};

typedef std::list <Ptr <IState> > StateList;
REFLECTION_COLLECTION (StateList)

typedef std::map <std::string, Ptr <IState> > StateMap;
REFLECTION_COLLECTION (StateMap)

} // nam

#endif /* ISTATE_H_ */
