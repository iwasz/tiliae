/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include <boost/shared_ptr.hpp>
#include "Assignment.h"
#include "ContextDependentSimple.h"
#include "k202/Exceptions.h"
#include "k202/Context.h"

namespace k202 {

std::string Assignment::toString () const
{
        assert (getArgs ().size () == 2);
        ExpressionList::const_iterator i1 = getArgs().begin ();
        ExpressionList::const_iterator i2 = i1; ++i2;

        return std::string ("Assignment (") + (*i1)->toString () + ", " +
                        (*i2)->toString () + ")";
}

Core::Variant Assignment::evaluate (Context *ctx)
{
        ExpressionList::const_iterator i = getArgs ().begin ();
        Ptr <IExpression> lhs = *i++;
        Ptr <IExpression> rhs = *i;
        Ptr <Property> prop;

        try {
                prop = boost::dynamic_pointer_cast <Property> (lhs);
        }
        catch (const std::bad_cast &) {
                throw RuntimeException ("RuntimeException : Assignment::evaluate : lhs is not a Property expression.");
        }

        if (prop->getPath ().empty ()) {
                throw RuntimeException ("RuntimeException : Assignment::evaluate : lhs is empty. You can't change entire domain.");
        }

        Core::Variant ret = rhs->evaluate (ctx);
        ctx->setArg (prop->getPath (), ret);
        return ret;
}

}
