/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MACHINECONTEXT_H_
#define MACHINECONTEXT_H_

#include <vector>
#include "context/MachineContext.h"
#include "core/Typedefs.h"
#include "core/variant/Cast.h"
#include "core/string/String.h"
#include "core/variant/Variant.h"
#include "core/IToStringEnabled.h"
#include "core/ApiMacro.h"
#include "reflection/Reflection.h"

namespace Machine {

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

        virtual ~MachineContext () {}

        /// Szuka we wszystkich, zwraca pierwszy znaleziony.
        REFLECTION_METHOD (get) Core::Variant get (const std::string &name) const;

        /// Ustawia w transition.
        REFLECTION_METHOD (set) void set (const std::string &name, const Core::Variant &object);

        void put (Core::VariantMap *m) { stack.push_back (m); }
        void pop () { stack.pop_back (); }

        virtual std::string toString () const;

private:

        std::vector <Core::VariantMap *> stack;

        REFLECTION_END (MachineContext)
};

}

#endif /* MACHINECONTEXT_H_ */
