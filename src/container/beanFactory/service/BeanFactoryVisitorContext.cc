/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BeanFactoryVisitorContext.h"

namespace Container {

BeanFactory *BeanFactoryVisitorContext::getCurrentBF () const
{
        if (stack.empty ()) {
                return NULL;
        }

        return stack.top ();
}

} //nam
