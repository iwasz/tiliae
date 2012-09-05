/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "../../common/logger/ILogger.h"
#include "StackStateExtension.h"
#include "IState.h"
#include "transition/Transition.h"
#include "../condition/ICondition.h"

namespace StateMachine {

const std::string STACK_STATE_PLACEHOLDER_NAME = "@back";
const std::string DEFAULT_PREV_PREFIX = "prevState";
const int STACK_STATE_MAX_DEPTH = 100;

/****************************************************************************/

std::string StackStateExtension::getPreviusStateName () const
{
        if (history.size () > 1) {
#if 0
                std::copy (history.begin (), history.end (), std::ostream_iterator <std::string> (std::cout, ","));
                std::cout << std::endl;
#endif
                return history[history.size () - 2];
        }

        return "";
}

/****************************************************************************/

bool StackStateExtension::checkContainsStateName (const std::string &stateName) const
{
        if (stateName == placeholder) {
                return true;
        }

        return false;
}

/****************************************************************************/

std::string StackStateExtension::translateName (const std::string &stateName) const
{
        if (stateName == placeholder) {
                return getPreviusStateName ();
        }

        return stateName;
}

/****************************************************************************/

Ptr <Transition> StackStateExtension::findTransition (Ptr <IState> currentState, MachineContext *) const
{
        return Ptr <Transition> ();
}

/****************************************************************************/

void StackStateExtension::beforeInputActions (MachineContext *context, Ptr <IState> currentState)
{
        if (!getPreviusStateName ().empty ()) {
                context->set (getPreviousPrefix(), Core::Variant (getPreviusStateName ()));
        }
}

/****************************************************************************/

void StackStateExtension::afterInputActions (MachineContext *context, Ptr <IState> currentState)
{
#       if 0
        logger->log ("*** Prev state = " + getPreviusStateName ());
        foreach (std::string s, history) {
                logger->log (s + ",");
        }
#endif
}

/****************************************************************************/

void StackStateExtension::afterExitActions (MachineContext *context,
                                            Ptr <IState> currentState,
                                            Ptr <IState> nextState,
                                            Ptr <Transition> transition)
{
        run (transition->getToState(), context);
}

/****************************************************************************/

void StackStateExtension::afterTransitionActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition)
{
}

/****************************************************************************/

void StackStateExtension::afterEntryActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition)
{
}

/****************************************************************************/

void StackStateExtension::reset (MachineContext *context, Ptr <IState> initState)
{
        history.clear ();
        run (initState->getName (), context);

        if (logger) {
                logger->log ("StackStateExtension::reset.");
        }
}

/****************************************************************************/

void StackStateExtension::run (const std::string &stateName, MachineContext *)
{
        Core::StringList outputs;

        if (stateName.empty ()) {
                if (logger) {
                        logger->log ("StackStateExtension::transitionTo : " + stateName + ".");
                }

                return;
        }

        if (history.size () >= getStackMaxDepth ()) {
                throw TooDeepStateNestingException ();
        }

        /*
         * Tutaj historia ma 2 i wiecej elementow. Tu wykrywamy fakt "cofniecia sie"
         * o jeden stan w historii do tylu. Jesli faktycznie wracamy do poprzedniego
         * stanu, to zdejmujemy aktualny z wierzchołka i poprzedni jest teraz aktualnym.
         */
        if (stateName == placeholder) {
                history.pop_back ();
        }
        else {
                history.push_back (stateName);
        }
}

}
