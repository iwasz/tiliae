/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Output.h"
#include "core/Typedefs.h"

namespace StateMachine {

void Output::removeAction (const std::string &name)
{
        assert (0);
        //actions.remove (name);
}

/****************************************************************************/

Core::StringList Output::run (const Core::StringList &in)
{
        foreach (std::string input, in) {
                Common::ZeroHandler *handler = actions[input];

                if (!handler) {
                        throw OutputException ();
                }

                handler->run ();
        }

        return in;
}

}
