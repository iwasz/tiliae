/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TTEE_STATE_H_
#define TTEE_STATE_H_

#include <memory>
#include "Reflection.h"
#include "Vertex.h"
#include "Region.h"
#include "ConnectionPointReference.h"
#include "PseudoState.h"
#include "IBehavior.h"
#include "../core/string/String.h"
#include "../core/ApiMacro.h"
#include "../../core/Pointer.h"

namespace Machine {
class StateMachine;

/**
 * A state models a situation during which some (usually implicit) invariant condition holds.
 * \ingroup StateMachine
 */
class TILIAE_API State : public Vertex {
public:

        explicit State (const std::string &n = std::string ()) : name (n) {}
        virtual  ~State () {}

        /**
         * A state with isComposite=true is said to be a composite state. A composite state is a state that contains at least one
         * region. Default value is false.
         */
        bool isComposite () const { return !regions.empty (); }

        /**
         * A state with isOrthogonal=true is said to be an orthogonal composite state. An orthogonal composite state contains
         * two or more regions. Default value is false.
         */
        bool isOthogonal () const { return regions.size () > 1; }

        /**
         * A state with isSimple=true is said to be a simple state. A simple state does not have any regions and it does not refer
         * to any submachine state machine. Default value is true.
         */
        bool isSimple () const { return !isComposite () && !isSubmachineState (); }

        /**
         * A state with isSubmachineState=true is said to be a submachine state. Such a state refers to a state machine
         * (submachine). Default value is false.
         */
        bool isSubmachineState () const { return bool (submachine); }

        /**
         * The query containingStateMachine() returns the state machine that contains the state either directly or transitively.
         */
        Ptr <StateMachine> getContainingStateMachine () const;

        /**
         * Event processing. Should be not directly called.
         */
        void event (Event *e);

/*--------------------------------------------------------------------------*/

        virtual std::string const &getName () const { return name; }
        void setName (const std::string &name) { this->name = name; }

        void addRegion (std::auto_ptr <Region> region);
        RegionVector const &getRegions () const { return regions; }

        Ptr <StateMachine> getSubmachine () const { return submachine; }
        void setSubmachine (Ptr <StateMachine> submachine);

        void addConnection (ConnectionPointReference *c);
        ConnectionPointReferenceVector const &getConnections () const { return connections; }

        void addConnectionPoint (Ptr <PseudoState> c);
        PseudoStateVector const &getConnectionPonts () const { return connectionPoints; }

/*--------------------------------------------------------------------------*/

private:

        void eventSimple (Event *e);
        void eventComposite (Event *e);
        void eventSubmachine (Event *e);
        Ptr <Transition> findTransition (Event *e);

private:

        std::string name;
        std::auto_ptr <IBehavior> entry;
        std::auto_ptr <IBehavior> exit;
        std::auto_ptr <IBehavior> doActivity;
//
//        // Collection : defferableTrigger (?)
//
//        std::auto_ptr <IConstraint> stateInvariant;
        Ptr <StateMachine> submachine;
//
        // exit, albo entry point.
        PseudoStateVector connectionPoints;
        ConnectionPointReferenceVector connections;
        RegionVector regions;

        TransitionMultiMap transitions;
};

} //nmspc

#endif /* MACHINE_H_ */
