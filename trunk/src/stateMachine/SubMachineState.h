/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SUBMACHINESTATE_H_
#define SUBMACHINESTATE_H_

#include "State.h"
#include "../core/ApiMacro.h"

namespace StateMachine {
class Machine;

/**
 * A to będzie pozwalało robić subMaszyny. Jest to takze normalny stan
 * typu State, a wiec mozna mu nadac akcje exit, input i entry.
 * \ingroup StateMachine
 */
class TILIAE_API SubMachineState : public State {
public:

        explicit SubMachineState (const std::string &n = std::string (),
                        Ptr<Machine> m = Ptr<Machine> ()) : State (n), machine (m) {}

        virtual ~SubMachineState () {}

        static Ptr <SubMachineState> create (const std::string &n = std::string (),
                        Ptr<Machine> m = Ptr<Machine> ()) { return Ptr <SubMachineState> (new SubMachineState (n, m)); }

        /**
         * Ta metoda jest uruchamiana przez Machine zawsze gdy wchodzimy w
         * dany stan, żeby pobrać jakie entry-actions maja sie wykonać. Dlatego
         * można ją przedefiniować w klasach dziedzicących ze State i dodać
         * kod, który ma się wykonać przy wejściu w stan.
         */
        virtual ActionList getEntryActions (MachineContext *context = NULL) const;

        /**
         * Analogicznie do getEntryActions i getExitActions.
         */
        virtual ActionList getInputActions (MachineContext *context) const;

        /**
         * Ta metoda jest uruchamiana przez Machine zawsze gdy wychodzimy z
         * danego stanu, żeby pobrać jakie exit-actions maja sie wykonać. Dlatego
         * można ją przedefiniować w klasach dziedzicących ze State i dodać
         * kod, który ma się wykonać przy wyjściu ze stanu.
         */
        virtual ActionList getExitActions (MachineContext *context = NULL) const;

/*--------------------------------------------------------------------------*/

        Ptr<Machine> getMachine() const { return machine; }
        void setMachine(Ptr<Machine> machine) { this->machine = machine; }

private:

        Ptr <Machine> machine;

};

}

#endif /* SUBMACHINESTATE_H_ */
