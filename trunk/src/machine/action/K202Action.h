/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef K202ACTION_H_
#define K202ACTION_H_

#include <K202.h>
#include <Reflection.h>
#include "IAction.h"
#include "../../core/ApiMacro.h"

namespace Machine {

/**
 * Akcja maszyny stanów skończonych - może być składnikiem InputAction
 * TransitionAction, lub ustawiona jako samodzielna EntryAction lub ExitAction.
 * Implementacja za pomocą skryptu K202.
 * \ingroup StateMachine
 */
class TILIAE_API K202Action : public IAction {
public:
        __c (void)
        K202Action () {}

        _c (const std::string &)
        K202Action (const std::string &sourceCode);

        virtual ~K202Action () {}

/*--------------------------------------------------------------------------*/

        std::string getCode () const;
        _m (setCode) void setCode (const std::string &code);

/*--------------------------------------------------------------------------*/

        virtual void run (MachineContext *context);

private:

        Ptr <k202::Script> script;
        _e (K202Action)
};

}

#endif /* K202ACTION_H_ */
