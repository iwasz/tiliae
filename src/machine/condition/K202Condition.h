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
#include <Reflection.h>
#include "condition/ICondition.h"
#include "../../core/ApiMacro.h"

namespace Machine {

/**
 * Implementuje ICondition za pomocą parsera K202.
 * \ingroup StateMachine
 */
class TILIAE_API K202Condition : public ICondition {
public:
        c__ (void)
        K202Condition () {}
        c_ (const std::string &)
        K202Condition (const std::string &sourceCode);
        K202Condition (const std::string &sourceCode, Ptr <k202::K202> k202);
        virtual ~K202Condition () {}

/*--------------------------------------------------------------------------*/

        std::string getCode () const;
        m_ (setCode) void setCode (const std::string &code);

/*--------------------------------------------------------------------------*/

        virtual bool check (MachineContext *context);

private:

        Ptr <k202::Script> script;
        e_ (K202Condition)
};

}

#endif /* K202CONDITION_H_ */
