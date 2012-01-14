/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MACHINECONTEXT_H_
#define MACHINECONTEXT_H_

#include "context/MachineContext.h"
#include "../../core/Typedefs.h"
#include "../../core/variant/Cast.h"
#include "../../core/string/String.h"
#include "../../core/variant/Variant.h"
#include "../../core/IToStringEnabled.h"
#include "../../core/ApiMacro.h"
#include "Reflection.h"

namespace StateMachine {

/**
 * Kontekst przechowujący wejścia maszyny stanów skończonych.
 * Jest dostępny dla kilu różnych obiektów tu w stateMachine.
 *
 * Jest to cudo zaimplementowane jako 2 mapy wariantów.
 * Nie ma interfejsu, bo implementacja cały czas wymagała
 * kastowania z MachineContext do MachineContext, czyli
 * była zalezna właśnie od tej klasy.
 * \ingroup StateMachine
 */
class TILIAE_API MachineContext : public Core::IToStringEnabled {
public:
        d__

        enum Scope { MACHINE, RUN, TRANSITION };

        static const std::string MACHINE_LITERAL;
        static const std::string RUN_LITERAL;
        static const std::string TRANSITION_LITERAL;

        MachineContext () : machine (NULL), run (NULL), transition (NULL) {}
        virtual ~MachineContext () {}

        /// Szuka we wszystkich, zwraca pierwszy znaleziony.
        m_ (get) virtual Core::Variant get (const std::string &name) const;

        /// Ustawia w transition.
        m_ (set) virtual void set (const std::string &name, const Core::Variant &object);

        void setMap (Scope scope, Core::VariantMap *map);
        Core::VariantMap *getMap (Scope scope);

        void clearMap (Scope scope);

        virtual std::string toString () const;

private:

        Core::VariantMap *machine;
        Core::VariantMap *run;
        Core::VariantMap *transition;

        e_ (MachineContext)
};

}

#endif /* MACHINECONTEXT_H_ */
