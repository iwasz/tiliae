/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STATE_H_
#define STATE_H_

#include "IState.h"
#include "InputActions.h"
#include "reflection/Reflection.h"
#include "core/string/String.h"
#include "core/ApiMacro.h"

namespace StateMachine {

/**
 * Stan. Prosta jest ta klasa stanu, bo zawieta właściwie tylko konfigurację.
 * \ingroup StateMachine
 */
class TILIAE_API State : public IState {
public:
        REFLECTION_CONSTRUCTOR_ (void)

        explicit State (const std::string &n = std::string ()) : name (n) {}
        virtual  ~State () {}

        static Ptr <State> create (const std::string &n = std::string ()) { return Ptr <State> (new State (n)); }

        virtual std::string getName () const { return name; }
        REFLECTION_METHOD (setName) void setName (const std::string &name) { this->name = name; }

        virtual ActionList getEntryActions (MachineContext *context = NULL) const { return entryActions; }
        REFLECTION_METHOD (setEntryActions) void setEntryActions (const ActionList &entryActions) { this->entryActions = entryActions; }
        void addEntryAction (Ptr <IAction> entryAction) { entryActions.push_back (entryAction); }
//        void addEntryActions (const ActionList &entryActions) { this->entryActions.addAll (entryActions); }
        void removeEntryAction (Ptr <IAction> entryAction) { entryActions.remove (entryAction); }

        virtual ActionList getExitActions (MachineContext *context = NULL) const { return exitActions; }
        REFLECTION_METHOD (setExitActions) void setExitActions (const ActionList &exitActions) { this->exitActions = exitActions; }
        void addExitAction (Ptr <IAction> exitAction) { exitActions.push_back (exitAction); }
//        void addExitActions (const ActionList &exitActions) { this->exitActions.addAll (exitActions); }
        void removeExitAction (Ptr <IAction> exitAction) { exitActions.remove (exitAction); }

        virtual ActionList getInputActions (MachineContext *context) const;
        REFLECTION_METHOD (setInputActions) void setInputActions (const InputActionsList &inputActions) { this->inputActions = inputActions; }
        void addInputAction (Ptr <InputActions> inputAction) { inputActions.push_back (inputAction); }
//        void addInputActions (const InputActionsList &inputActions) { this->inputActions.addAll (inputActions); }
        void removeInputAction (Ptr <InputActions> inputAction) { inputActions.remove (inputAction); }

        REFLECTION_METHOD (getTransitions) const TransitionList &getTransitions () const {return transitions;}
        REFLECTION_METHOD (setTransitions) void setTransitions (const TransitionList &transitions) { this->transitions = transitions; }
        void addTransition (Ptr <Transition> transition) { transitions.push_back (transition); }
//        void addTransitions (const TransitionList &transitions) { this->transitions.addAll (transitions); }
        void removeTransition (Ptr <Transition> transition) { transitions.remove (transition); }

private:

        std::string name;
        ActionList entryActions;
        ActionList exitActions;
        InputActionsList inputActions;
        TransitionList transitions;

        REFLECTION_END (State)
};

} //nmspc

#endif /* MACHINE_H_ */
