/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMACHINERY_H_
#define IMACHINERY_H_

#include "context/MachineContext.h"
#include <list>
#include "../core/Pointer.h"
#include "../core/ApiMacro.h"

namespace StateMachine {

/**
 * Jest to klasa, która ma reprezentowac jakiś łącznik między
 * parametrami wejściowymi (inputs), a światem
 * wyjściem, które może być dowolne i nie jest tu zdefiniowane.
 *
 * Na przykład dla klasy konkretnej Output wyjściem są akcje
 * (handlery), które mogą robić dowolne rzeczy (w ten sposób
 * zaimplementowane jest wyjście maszyn skończonych na świat
 * zewnętrzny).
 * \ingroup StateMachine
 */
struct TILIAE_API IMachinery {

        virtual void run (MachineContext *context) = 0;

};

typedef std::list <Ptr <IMachinery> > MachineryList;

} // nam

#endif /* IMACHINERY_H_ */
