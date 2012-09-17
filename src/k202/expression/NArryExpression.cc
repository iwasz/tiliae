/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/lexical_cast.hpp>
#include "NArryExpression.h"
#include "Exceptions.h"

namespace k202 {

void NArryExpression::addArgFront (Ptr <IExpression> ex)
{
        if (args.size () >= arity) {
                throw ByteCodeException (std::string ("ScriptException : too many arguments. Maximum number : ") +
                                boost::lexical_cast <std::string> (arity));
        }

        args.push_front (ex);
}

void NArryExpression::addArgBack (Ptr <IExpression> ex)
{
        if (args.size () >= arity) {
                throw ByteCodeException (std::string ("ScriptException : too many arguments. Maximum number : ") +
                                boost::lexical_cast <std::string> (arity));
        }

        args.push_back (ex);
}

}

