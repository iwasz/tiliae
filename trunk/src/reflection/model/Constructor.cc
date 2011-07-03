/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Constructor.h"
#include <boost/lexical_cast.hpp>
#include <boost/lexical_cast.hpp>

namespace Reflection {

/****************************************************************************/

std::string Constructor::toString () const
{
        return std::string ("Constructor (arg number : ") + boost::lexical_cast <std::string> (getArity()) + ")";
}

/****************************************************************************/

Core::Variant Constructor::newInstance (Core::VariantVector *ol)
{
        try {
                assert (constructorPointer);
                return constructorPointer->invoke (ol);
        }
        catch (Core::Exception &e) {
                e.addMessage ("In Constructor::newInstance. Arity : [" + boost::lexical_cast <std::string> (getArity()) + "].");
                throw;
        }
}

/****************************************************************************/

Core::Variant Constructor::newInstance (Core::Variant const &arg)
{
        try {
                assert (constructorPointer);
                Core::VariantVector v (1);
                v[0] = arg;
                return constructorPointer->invoke (&v);
        }
        catch (Core::Exception &e) {
                e.addMessage ("In Constructor::newInstance. Arity : 1, Arg : " + arg.toString ());
                throw;
        }

}

} // namespace

