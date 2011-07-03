/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MACHINELISTENER_H_
#define MACHINELISTENER_H_

#include "Reflection.h"
#include "../signal/Listener.h"
#include "../core/Typedefs.h"
#include "../core/string/String.h"
#include "../core/ApiMacro.h"

namespace StateMachine {
class Machine;

/**
 * Listener dla FSM. To jest implementacja interfejsu Signal::IListener specjalnie
 * dla maszyn stanów skończonych. Wywołanie tego listenera powoduje uruchomienie metody
 * run i przekazanie parametrów do RUN_SCOPE.
 */
class TILIAE_API MachineListener : public Signal::AbstractListener {
public:
        __c (void)

        virtual ~MachineListener () {}

        Core::Variant run (const Core::VariantVector &paramVector,
                           const Core::VariantMap &argsMap);

        void setMachine (Machine *m);

        std::string getPath () const { return path; }
        _m (setPath) void setPath (const std::string &path) { this->path = path; }

private:

        std::string path;
        Machine *machine;

        _e (MachineListener)
};

}

#	endif /* MACHINELISTENER_H_ */
