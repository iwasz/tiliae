/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <sstream>
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include "Context.h"

namespace Core {

std::string Context::getMessage () const
{
	std::string ret;
	int cnt = stack.size ();

	for (std::deque <std::string>::const_iterator i = stack.begin (); i != stack.end (); ++i) {
		ret += boost::lexical_cast <std::string> (cnt--) + *i;
	}

	return ret;
}

/****************************************************************************/

void Context::apendContext (Context const &c)
{
	stack.resize (stack.size () + c.stack.size ());
	std::copy (c.stack.begin (), c.stack.end (), stack.end ());
}

/****************************************************************************/

void Context::prependContext (Context const &c)
{
	stack.resize (stack.size () + c.stack.size ());
	// TODO to jest append skopiowane. jak to zroibć ładnie?
	std::copy (c.stack.begin (), c.stack.end (), stack.end ());
}

} // nam
