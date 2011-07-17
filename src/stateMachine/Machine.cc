/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Machine.h"
#include "transition/Transition.h"
#include "../common/logger/ILogger.h"
#include "../core/Typedefs.h"
#include "../k202/extension/CacheExtension.h"
#include "../k202/K202.h"
#include <cassert>
#include "../beanWrapper/beanWrapper/BeanWrapper.h"

using namespace Common;

namespace StateMachine {

const char *SHUT_DOWN_PLACEHOLDER = "@shutDown";
const char *RESET_PLACEHOLDER = "@reset";

Machine::Machine (const Core::VariantMap &mp) : machineScope (mp), running (true)
{
        defaultContext.setMap (MachineContext::MACHINE, &machineScope);
}

/****************************************************************************/

Ptr <Machine> Machine::create (const Core::VariantMap &mp)
{
        Ptr <Machine> m (new Machine (mp));
        Ptr <k202::CacheExtension> c = k202::CacheExtension::create ();
        Ptr <k202::K202> k = k202::K202::create (Wrapper::BeanWrapper::create (), c);
        m->setK202 (k);
        m->setCache (c);
        return m;
}

/****************************************************************************/

void Machine::reset ()
{
        setCurrentStateName ("");
        running = true;
}

/****************************************************************************/

std::string Machine::translateName (const std::string &name) const
{
        foreach (Ptr <IMachineExtension> ext, extensionList) {

                std::string newName = ext->translateName (name);

                // Pierwszy, ktory przekonwertuje na cos innego.
                if (newName != name) {
                        return newName;
                }
        }

        return name;
}

/****************************************************************************/

bool Machine::checkContainsStateName (const std::string &name) const
{
        foreach (Ptr <IMachineExtension> ext, extensionList) {
                if (ext->checkContainsStateName (name)) {
                        return true;
                }
        }

        if (stateMap.find (name) != stateMap.end ()) {
                return true;
        }

        return false;
}

/*## Extensions execution ##################################################*/

Ptr <Transition> Machine::findTransition (Ptr <IState> currentState, MachineContext *context) const
{
        if (!currentState) {
                return Ptr <Transition> ();
        }

        foreach (Ptr <IMachineExtension> extension, extensionList) {
                Ptr <Transition> tr = extension->findTransition (currentState, context);

                if (tr) {
                        return tr;
                }
        }

#if 0
        std::cerr << currentState->getTransitions ().size () << std::endl;
#endif

        foreach (Ptr <Transition> transition, currentState->getTransitions ()) {

                assert (transition);

                if (transition->checkCondition (context)) {
                        return transition;
                }
        }

        return Ptr <Transition> ();
}

void Machine::beforeInputActions (MachineContext *context, Ptr <IState> currentState)
{
        foreach (Ptr <IMachineExtension> ext, extensionList) {
                ext->beforeInputActions (context, currentState);
        }
}

void Machine::afterInputActions (MachineContext *context, Ptr <IState> currentState)
{
        foreach (Ptr <IMachineExtension> ext, extensionList) {
                ext->afterInputActions (context, currentState);
        }
}

void Machine::afterExitActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition)
{
        foreach (Ptr <IMachineExtension> ext, extensionList) {
                ext->afterExitActions (context, currentState, nextState, transition);
        }
}

void Machine::afterTransitionActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition)
{
        foreach (Ptr <IMachineExtension> ext, extensionList) {
                ext->afterTransitionActions (context, currentState, nextState, transition);
        }
}

void Machine::afterEntryActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition)
{
        foreach (Ptr <IMachineExtension> ext, extensionList) {
                ext->afterEntryActions (context, currentState, nextState, transition);
        }
}

/*##########################################################################*/

void Machine::run (const Core::VariantMap &runScope, const Core::VariantMap &transitionScope)
{
        Core::VariantMap runScopeCopy = runScope;
        Core::VariantMap transitionScopeCopy = transitionScope;

        defaultContext.setMap (MachineContext::RUN, &runScopeCopy);
        defaultContext.setMap (MachineContext::TRANSITION, &transitionScopeCopy);

        run (&defaultContext);
}

/****************************************************************************/

void Machine::run (MachineContext *context)
{
        /*
         * Pole running mówi czy maszyna ma w ogóle działac, czy nie.
         * running będzie false kiedy przejdziemy do stanu mońcowego,
         * czyli do SHUT_DOWN_PLACEHOLDER.
         */
        if (!running) {
                return;
        }

#if 0
        std::cerr << "Machine::run (MachineContext *context)" << std::endl;
#endif

        if (cache) {
                cache->clearCache ();
        }

        // Znaczy ze był reset, albo startujemy pierwszy raz.
        if (getCurrentStateName ().empty ()) {
                setCurrentStateName (getInitialStateName ());
                Ptr <IState> initialState = getState (getInitialStateName ());
                runActionList (context, initialState->getEntryActions (context));

                foreach (Ptr <IMachineExtension> ext, extensionList) {
                        ext->reset (context, initialState);
                }
        }

        Ptr <IState> currentState = getState (getCurrentStateName ()); // Will throw if no currentStateName
        beforeInputActions (context, currentState);

        runActionList (context, currentState->getInputActions (context));

        afterInputActions (context, currentState);

#if 1
        if (logger) {
                logger->log ("Machine::run");
                logger->log (" firstState : " + getCurrentStateName ());
                logger->log (" context : " + context->toString ());
        }
#endif

        while (Ptr <Transition> transition = findTransition (getState (getCurrentStateName ()), context)) {

                runActionList (context, currentState->getExitActions (context));

                std::string nextStateName = translateName (transition->getToState ());
                Ptr <IState> nextState = getState (nextStateName); // Will throw if no currentStateName

                /*
                 * Poinformowanie extansionów o zmianie stanu. Podany stan w
                 * oryginalnej notacji (bez translate).
                 */
                afterExitActions (context, currentState, nextState, transition);

                // Nowe transition Actions.
                if (transition->getToState () != nextStateName) {
                        runActionList (context, transitionActions.get (getCurrentStateName (), transition->getToState ()));
                }

                runActionList (context, transitionActions.get (getCurrentStateName (), nextStateName));

                /*
                 * Akcje przejścia i entry w nowy stan.
                 */
                runActionList (context, transition->getTransitionActions ());
                afterTransitionActions (context, currentState, nextState, transition);

                /*
                 * Jeśli nextStateName to placeholder końcowego metastanu, to wyłączamy maszynę.
                 */
                if (nextStateName == SHUT_DOWN_PLACEHOLDER) {
                        running = false;
                        currentStateName = "";
                        return;
                }

                if (nextStateName == RESET_PLACEHOLDER) {
                        reset ();
                        return;
                }

                /*
                 * Faktyczna zmiana aktualnego stanu.
                 */
                setCurrentStateName (nextStateName);
                runActionList (context, nextState->getEntryActions (context));
                afterEntryActions (context, currentState, nextState, transition);

                context->clearMap (MachineContext::TRANSITION);

#if 1
                if (logger) {
                        logger->log (" ");
                        logger->log (" nextState : " + getCurrentStateName ());
                        logger->log (" context : " + context->toString ());
                }
#endif
        }

        context->clearMap (MachineContext::RUN);

        if (logger) {
                logger->log (" clearing RUN ");
                logger->log (" context : " + context->toString ());
        }
}

/****************************************************************************/

Ptr <IState> Machine::getState (const std::string &stateName) const
{
        if (stateName == SHUT_DOWN_PLACEHOLDER || stateName == RESET_PLACEHOLDER) {
                return Ptr <IState> ();
        }

        StateMap::const_iterator i = stateMap.find (stateName);
        if (i == stateMap.end ()) {
                UndefinedStateException e ("UndefinedStateException name = (" + stateName + ")");
                throw e;
        }

        return i->second;
}

/****************************************************************************/

void Machine::setStates (const StateList &states)
{
        stateMap.clear ();
        addStates (states);
}

/****************************************************************************/

void Machine::addState (Ptr <IState> state)
{
        assert (state);

        if (checkContainsStateName (state->getName ())) {
                throw DuplicateStateException ();
        }

        stateMap[state->getName ()] = state;
}

/****************************************************************************/

void Machine::addStates (const StateList &states)
{
        foreach (Ptr <IState> state, states) {
                addState (state);
        }
}

/****************************************************************************/

void Machine::removeState (const std::string &stateName)
{
        stateMap.erase (stateName);
}

/****************************************************************************/

void Machine::addTransitionActions (const TransitionActionList &act)
{
        foreach (Ptr <TransitionAction> a, act) {
                addTransitionAction (a);
        }
}

/****************************************************************************/

void Machine::runActionList (MachineContext *context, const ActionList &list)
{
        foreach (Ptr <IAction> action, list) {
                action->run (context);
        }
}

/****************************************************************************/

void Machine::setListener (Ptr <MachineListener> l)
{
        listener = l;
        l->setMachine (this);
}

} // namespace
