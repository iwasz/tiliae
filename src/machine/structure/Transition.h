/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <list>
#include <map>
#include <memory>
#include "IConstraint.h"
#include "IBehavior.h"
#include "Trigger.h"
#include "context/MachineContext.h"
#include "core/Pointer.h"
#include "core/string/String.h"
#include "core/ApiMacro.h"

namespace Machine {
class Vertex;

/**
 *
 */
enum TransitionKind {
        INTERNAL,
        LOCAL,
        EXTERNAL
};

/**
 * Podobnie jak klasa State, Transition też jest głównie tylko
 * kontenerem na konfigurację, a brudna robota odbywa się w
 * Machine.
 * \ingroup StateMachine
 */
class TILIAE_API Transition {
public:
        Transition () {}

        /**
         * Checks whether incoming event should be accepted or denied.
         */
        bool match (Event *e);

/*--------------------------------------------------------------------------*/

        Ptr <Vertex> getTarget () const { return target; }
        void setTarget (Ptr <Vertex> target) { this->target = target; }

        TransitionKind getKind () const { return kind; }
        void setKind (TransitionKind kind) { this->kind = kind; }

/*--------------------------------------------------------------------------*/

private:

        Ptr <Vertex> target;
        std::auto_ptr <IConstraint> guard;
        std::auto_ptr <IBehavior> effect;
        TriggerVector triggers;
        TransitionKind kind;
};

typedef std::list <Ptr <Transition> > TransitionList;
typedef std::multimap <std::string, Ptr <Transition> > TransitionMultiMap;

} // namespace

#endif /* TRANSITION_H_ */
