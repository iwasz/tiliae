/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "CacheExtension.h"
#include "CacheExpression.h"

namespace k202 {

Ptr <IExpression> CacheExtension::popStack (Ptr <IExpression> e)
{
        return e;
}

Ptr <IExpression> CacheExtension::onProperty (Ptr <Property> p, ExpressionStack *s, const std::string &k)
{
        // TODO taką listę zrobić
        if (!p || k.find ("prevState") != std::string::npos || k.find ("TRANSITION") != std::string::npos) {
                return Ptr <IExpression> ();
        }

        return CacheExpression::create (p, &cache, k);
}

} // nam
