/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BeanFactoryVisitorContext.h"

namespace Container {

Ptr <BeanFactory> BeanFactoryVisitorContext::getCurrentBF () const
{
        if (stack.empty ()) {
                return Ptr <BeanFactory> ();
        }

        return stack.top ();
}

} //nam
