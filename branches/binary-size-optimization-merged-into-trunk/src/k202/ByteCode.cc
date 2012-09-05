/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ByteCode.h"
#include "Context.h"
#include "expression/IExpression.h"
#include "expression/ExpressionCollection.h"

namespace k202 {

std::string ByteCode::toString () const
{
        std::string ret = std::string ("ByteCode (");

        foreach (Ptr <IExpression> ex, expressions) {
                ret += ex->toString () + ", ";
        }

        if (!expressions.empty ()) {
                ret.resize (ret.size () - 2);
        }

        return ret + ")";
}

/****************************************************************************/

Core::Variant ByteCode::run (Context *ctx)
{
        ExpressionList::iterator i = expressions.begin ();

        while (i != expressions.end ()) {

                Ptr <IExpression> ex = *i++;

                if (i == expressions.end ()) {
                        return ex->evaluate (ctx);
                }

                ex->evaluate (ctx);
        }

        return Core::Variant ();
}

}
