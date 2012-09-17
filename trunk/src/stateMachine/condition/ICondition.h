/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/


#ifndef ICONDITION_H_
#define ICONDITION_H_

#include "context/MachineContext.h"
#include "core/Object.h"
#include "core/ApiMacro.h"

namespace StateMachine {

/**
 * Warunek na wejścia. To jest interfejs, który jest używany w przejściach
 * (warunek przejścia z jednego stanu do innego), oraz podczas wykonywania
 * input-actions. Więcej informacji w klasach konkretnych.
 * \see State::SimpleCondition
 * \see State::Condition
 * \ingroup StateMachine
 */
class TILIAE_API ICondition : public Core::Object {
public:

        virtual ~ICondition () {}
        virtual bool check (MachineContext *context) = 0;

};

} // nam

#endif /* ICONDITION_H_ */
