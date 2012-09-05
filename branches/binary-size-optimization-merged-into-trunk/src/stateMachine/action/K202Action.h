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

namespace StateMachine {

/**
 * Akcja maszyny stanów skończonych - może być składnikiem InputAction
 * TransitionAction, lub ustawiona jako samodzielna EntryAction lub ExitAction.
 * Implementacja za pomocą skryptu K202.
 * \ingroup StateMachine
 */
class TILIAE_API K202Action : public IAction {
public:
        REFLECTION_CONSTRUCTOR_ (void)
        K202Action () {}

        REFLECTION_CONSTRUCTOR (const std::string &)
        K202Action (const std::string &sourceCode);

        virtual ~K202Action () {}
        static Ptr <K202Action> create (const std::string &sourceCode) { return Ptr <K202Action> (new K202Action (sourceCode)); }

/*--------------------------------------------------------------------------*/

        std::string getCode () const;
        REFLECTION_METHOD (setCode) void setCode (const std::string &code);

/*--------------------------------------------------------------------------*/

        virtual void run (MachineContext *context);

private:

        Ptr <k202::Script> script;
        REFLECTION_END (K202Action)
};

}

#endif /* K202ACTION_H_ */
