/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include "Machine.h"
#include "State.h"
#include "action/IAction.h"

using namespace Common;

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
namespace StateMachine {

ActionList State::getInputActions (MachineContext *context) const
{
        ActionList actions;

        if (inputActions.empty ()) {
                return actions;
        }

        for  (InputActionsList::const_iterator i = inputActions.begin (); i != inputActions.end (); ++i) {
                assert (*i);
                ActionList tmp = (*i)->checkConditionAndGetActions (context);
                std::copy (tmp.begin (), tmp.end (), std::back_inserter (actions));
        }

        return actions;
}

} // namespace
