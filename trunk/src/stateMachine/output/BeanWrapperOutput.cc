/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include "BeanWrapperOutput.h"
#include "beanWrapper/IBeanWrapper.h"

namespace StateMachine {

Core::StringList BeanWrapperOutput::run (const Core::StringList &in)
{
        assert (getBeanWrapper ());

        foreach (std::string input, in) {
                getBeanWrapper ()->get (input);
        }

        return in;
}

}
