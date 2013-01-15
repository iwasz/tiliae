/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include <boost/lexical_cast.hpp>
#include "k202/expression/ContextDependentSimple.h"
#include "k202/Context.h"
#include "core/string/String.h"
#include "core/Typedefs.h"

namespace k202 {

std::string Placeholder::toString () const
{
        return std::string ("Placeholder (") + boost::lexical_cast <std::string> (place) + ")";
}

/****************************************************************************/

Core::Variant Placeholder::evaluate (Context *ctx)
{
        return ctx->getParam (place);
}

/****************************************************************************/

Core::Variant Property::evaluate (Context *ctx)
{
        return ctx->getArg (property, conditional);
}

/****************************************************************************/

std::string Function::toString () const
{
        std::string ret = std::string ("Function (") + name;

        if (!getArgs ().empty ()) {
                ret += std::string (", ") + boost::lexical_cast <std::string> (getArgs ().size ()) + " args : ";
        }

        for (ExpressionList::const_iterator i = getArgs ().begin (); i != getArgs ().end (); ++i) {
                ret += (*i)->toString () + ", ";
        }

        if (!getArgs ().empty ()) {
                ret.resize (ret.size () - 2);
        }

        return ret + ")";
}

/****************************************************************************/

Core::Variant Function::evaluate (Context *ctx)
{
        Core::VariantVector args;

        for (ExpressionList::const_iterator i = getArgs ().begin (); i != getArgs ().end (); ++i) {
                args.push_back ((*i)->evaluate (ctx));
        }

        return ctx->callFunction (name, args);
}

}
