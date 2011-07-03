/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CHAINMACHINE_H_
#define CHAINMACHINE_H_

#include "IMachinery.h"
#include "../core/ApiMacro.h"

namespace StateMachine {

/**
 * Jakkolwiek sama jest częścią maszynerii, to zawiera w sobie
 * jeszcze więcej maszynerii i uruachamia swoje elementy po kolei
 * przekazując wyjście jednej do wejścia następnej.
 *
 * ChainMachine dziedziczy z IMachinery ponieważ to ujednolica interfejs
 * i klas jest mniej, a co za tym idzie łatwiej spamiętać to wszystko.
 * \ingroup StateMachine
 */
class TILIAE_API ChainMachine : public IMachinery {
public:

        virtual void run (MachineContext *context);

        MachineryList getMachineryList () const { return machineryList; }
        void setMachineryList (const MachineryList &machineryList) { this->machineryList = machineryList; }

        void addMachinery (Ptr <IMachinery> machinery) { machineryList.push_back (machinery); }
        void addMachineries (const MachineryList &machineries);
        void removeMachinery (Ptr <IMachinery> machinery) { machineryList.remove (machinery); }

private:

        MachineryList machineryList;

};

}

#endif /* CHAINMACHINE_H_ */
