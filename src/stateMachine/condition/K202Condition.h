/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef K202CONDITION_H_
#define K202CONDITION_H_

#include <K202.h>
#include "reflection/Reflection.h"
#include "condition/ICondition.h"
#include "core/ApiMacro.h"

namespace StateMachine {

/**
 * Implementuje ICondition za pomocą parsera K202.
 * \ingroup StateMachine
 */
class TILIAE_API K202Condition : public ICondition {
public:
        REFLECTION_CONSTRUCTOR_ (void)
        K202Condition () {}

        REFLECTION_CONSTRUCTOR (const std::string &)
        K202Condition (const std::string &sourceCode);

        K202Condition (const std::string &sourceCode, Ptr <k202::K202> k202);
        virtual ~K202Condition () {}
        static Ptr <K202Condition> create (const std::string &sourceCode, Ptr <k202::K202> k202 = Ptr <k202::K202> ()) { return Ptr <K202Condition> (new K202Condition (sourceCode, k202)); }

/*--------------------------------------------------------------------------*/

        std::string getCode () const;
        REFLECTION_METHOD (setCode) void setCode (const std::string &code);

/*--------------------------------------------------------------------------*/

        virtual bool check (MachineContext *context);

private:

        Ptr <k202::Script> script;
        REFLECTION_END (K202Condition)
};

}

#endif /* K202CONDITION_H_ */
