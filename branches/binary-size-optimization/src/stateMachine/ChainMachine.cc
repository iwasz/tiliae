/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ChainMachine.h"
#include <algorithm>
#include <iterator>

namespace StateMachine {

void ChainMachine::addMachineries (const MachineryList &machineries)
{
        std::copy (machineries.begin (), machineries.end (), std::back_inserter (machineryList));
}

/****************************************************************************/

void ChainMachine::run (MachineContext *context)
{
        foreach (Ptr <IMachinery> machinery, machineryList) {
                machinery->run (context);
        }
}

}
