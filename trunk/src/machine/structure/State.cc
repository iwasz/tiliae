/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include "State.h"
#include "StateMachine.h"
#include "Transition.h"
#include "Event.h"

/**
 * TODO Substany nie są zaimplementowane i nie wiem do końca jak mają być zaimplementowane,
 * ale by się bardzo przydały.
 * TODO Można tworzyć całe grupy przejść za pomocą placeholdera "back", ale nie da się wtedy
 * stworzyć TransitionAction per stan docelowy. Jest tak dlatego, że akcje transition dodaje
 * się do tranzycji (a nie do maszyny na przykład) i taka akcja wykona się dla wszystkich
 * stanów końcowych. Gdyby się dało dodawać akcje TransitionAction do maszyny, to wtedy możnaby
 * definiować osobno przejścia (from=stateA, to=back), a osobno kilka akcji w zależności od
 * stanu końcowego (from=stateA, to=stateC | from=stateA, to=stateB).
 */
namespace Machine {

void State::addRegion (std::auto_ptr <Region> region)
{
        if (isSubmachineState ()) {
                throw StateMachineException ("State::addRegion : A state is not allowed to have both a submachine and regions.");
        }

//        regions.push_back (region);
}

/****************************************************************************/

void State::setSubmachine (Ptr <StateMachine> submachine)
{
        if (isComposite ()) {
                throw StateMachineException ("State::setSubmachine : A state is not allowed to have both a submachine and regions.");
        }

        this->submachine = submachine;
}

/****************************************************************************/

void State::addConnection (ConnectionPointReference *c)
{
        if (!isSubmachineState ()) {
                throw StateMachineException ("State::addConnection : Only submachine states can have connection point references.");
        }

        // Add
}

/****************************************************************************/

void State::event (Event *e)
{
        //Sprawdzić czy te warunki się na pewno wykluczają.
        if (isSimple ()) {
                eventSimple (e);
        }
        else if (isComposite ()) {
                eventComposite (e);
        }
        else if (isSubmachineState ()) {
                eventSubmachine (e);
        }
}

/****************************************************************************/

void State::eventSimple (Event *e)
{
        Ptr <Transition> transition = findTransition (e);

        if (!transition) {
                return;
        }

        if (transition->getKind () == EXTERNAL) {
        }
        else if (transition->getKind () == INTERNAL) {
        }
        else if (transition->getKind () == LOCAL) {
        }

        Ptr <Vertex> targetVertex = transition->getTarget ();

}

/****************************************************************************/

Ptr <Transition> State::findTransition (Event *e)
{
        typedef TransitionMultiMap::iterator It;
        typedef std::pair <It, It> Pa;
        Pa result = transitions.equal_range (e->getName ());
}

/****************************************************************************/

void State::eventComposite (Event *e)
{

}

void State::eventSubmachine (Event *e)
{

}

} // namespace
