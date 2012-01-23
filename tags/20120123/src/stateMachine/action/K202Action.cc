/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "K202Action.h"
#include "../context/MachineContext.h"
#include "../../k202/Script.h"

namespace StateMachine {

K202Action::K202Action (const std::string &sourceCode)
{
        script = k202::K202::instance()->prepare (sourceCode);
}


/****************************************************************************/

std::string K202Action::getCode () const
{
        return script->getSourceCode ();
}

/****************************************************************************/

void K202Action::setCode (const std::string &code)
{
        script = k202::K202::instance()->prepare (code);
}

/****************************************************************************/

void K202Action::run (MachineContext *context)
{
        Core::Variant tmp = Core::Variant (context);
        k202::K202::instance()->run (script, &tmp);
}

}
