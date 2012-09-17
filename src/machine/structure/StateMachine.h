/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FSM_STATE_MACHINE_H
#define FSM_STATE_MACHINE_H

#include <vector>
#include <map>
#include "reflection/Reflection.h"
#include "State.h"
#include "Exceptions.h"
#include "MachineListener.h"
#include "Region.h"
#include "core/Typedefs.h"
#include "core/string/String.h"
#include "core/Pointer.h"
#include "core/ApiMacro.h"

namespace Common {
class ILogger;
}

namespace k202 {
class K202;
}

namespace Machine {
class Transition;
class Event;

/**
 * Maszyna stanów skończonych.
 * \ingroup StateMachine
 */
class TILIAE_API StateMachine {
public:

        virtual ~StateMachine () {}

//        getLca (State s1, State s2)
//        bool ancestor (State s1, State s2)
        void event (Event *, PseudoState *defaultEntry = NULL);

/*--------------------------------------------------------------------------*/

        void addRegion (std::auto_ptr <Region> region);
        RegionVector const &getRegions () const { return regions; }

        void addConnectionPoint (Ptr <PseudoState> c);
        PseudoStateVector const &getConnectionPonts () const { return connectionPoints; }

private:

        RegionVector regions;

        // exit, albo entry point.
        PseudoStateVector connectionPoints;

        /*
         * Kontekst może być pojedynczym obiektem, specyfikacja dokładnie nie mówi co to ma być (?).
         */
        Core::Variant context;
};

typedef std::map <std::string, Ptr <StateMachine> > MachineMap;
typedef std::vector <Ptr <StateMachine> > MachineVector;

struct TILIAE_API StateMachineException : public Core::Exception {
        StateMachineException (std::string const &m = "") : Core::Exception (m) {}
        virtual ~StateMachineException () throw () {}
};

} //nmspc

#endif /* MACHINE_H_ */
