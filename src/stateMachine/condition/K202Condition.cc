/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Script.h>

#include "K202Condition.h"
#include "context/MachineContext.h"
#include "Exceptions.h"
#include "core/Exception.h"

namespace StateMachine {

K202Condition::K202Condition (const std::string &sourceCode)
{
        script = k202::K202::instance()->prepare (sourceCode);
}

/****************************************************************************/

K202Condition::K202Condition (const std::string &sourceCode, Ptr <k202::K202> k202)
{
        if (k202) {
                script = k202->prepare (sourceCode);
        }
        else {
                script = k202::K202::instance()->prepare (sourceCode);
        }
}

/****************************************************************************/

std::string K202Condition::getCode () const
{
        return script->getSourceCode ();
}

/****************************************************************************/

void K202Condition::setCode (const std::string &code)
{
        script = k202::K202::instance()->prepare (code);
}

/****************************************************************************/

bool K202Condition::check (MachineContext *context)
{
        try {
                Core::Variant tmp = Core::Variant (context);
                tmp = k202::K202::instance()->run (script, &tmp);

#if 0
                std::cerr << script->getSourceCode() << std::endl;
#endif

                if (tmp.isNone ()) {
                        return false;
                }

                return vcast <bool> (tmp);
        }
        catch (const Core::Exception &e) {
                ConditionException ne (e);
                ne.addMessage ("ConditionException caused by script : " + script->getSourceCode ());
                throw ne;
        }
        catch (...) {
                throw ConditionException ("ConditionException caused by script : " + script->getSourceCode ());
        }
}

}
