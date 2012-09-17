/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMACHINEEXTENSION_H_
#define IMACHINEEXTENSION_H_

#include <list>
#include "context/MachineContext.h"
#include "core/Pointer.h"
#include "core/string/String.h"
#include "core/ApiMacro.h"

namespace StateMachine {

class IState;
class Transition;

/**
 * Rozszerzenia, ktore polegają na tym, że wprowadzają placholdery
 * dla istniejących stanów. Przejście do takiego placeholdera (tzn
 * przejście do stanu oznaczonego takim placeholderem, czyli umieszczenie
 * placeholdera w toState transition) powoduje przejście do jakiegoś
 * innego stanu, ktory ten placeholder reprezentuje. Moze to byc na
 * przyklad placeholder o nazwie "previous", ktory zawsze "wskazuje"
 * na poprzedni stan.
 *
 * State::Machine ma odpowiedniki wszystkich 3 metod i deleguje część
 * funkcjonalności właśnie do tych extensionów.
 * \ingroup StateMachine
 */
struct TILIAE_API IMachineExtension : public Core::Object {

        virtual ~IMachineExtension () {}

        virtual bool checkContainsStateName (const std::string &name) const = 0;
        virtual std::string translateName (const std::string &stateName) const = 0;

        virtual Ptr <Transition> findTransition (Ptr <IState> currentState, MachineContext *context) const = 0;
        virtual void reset (MachineContext *context, Ptr <IState> initState) = 0;

        virtual void beforeInputActions (MachineContext *context, Ptr <IState> currentState) = 0;
        virtual void afterInputActions (MachineContext *context, Ptr <IState> currentState) = 0;
        virtual void afterExitActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition) = 0;
        virtual void afterTransitionActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition) = 0;
        virtual void afterEntryActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition) = 0;

};

typedef std::list <Ptr <IMachineExtension> > MachineExtensionList;

}

#endif /* IMACHINEEXTENSION_H_ */
