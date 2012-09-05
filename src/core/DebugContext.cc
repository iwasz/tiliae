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
#include "DebugContext.h"
#include <iostream>

namespace Core {

std::string DebugContext::getMessage () const
{
	std::string ret;
	int cnt = stack.size();

	if (cnt == 1) {
	        return stack.front ();
	}

	for (std::vector <std::string>::const_iterator i = stack.begin (); i != stack.end (); ++i) {
		ret += boost::lexical_cast <std::string> (cnt--) + ". " + *i + "\n";
	}

	return ret;
}

/****************************************************************************/

void DebugContext::addMessage (const std::string &e)
{
        stack.push_back (e);
}

/****************************************************************************/

void DebugContext::addContext (DebugContext const &c)
{
	std::copy (c.stack.begin (), c.stack.end (), std::back_inserter (stack));
}

/****************************************************************************/

void DebugContext::begin ()
{
        transaction = stack.size ();
}

/****************************************************************************/

void DebugContext::commit ()
{
        transaction = -1;
}

/****************************************************************************/

void DebugContext::rollback ()
{
        if (transaction > 0) {
                stack.resize (transaction);
                transaction = -1;
        }
}

} // nam

/****************************************************************************/

#ifndef NDEBUG

void dcBegin (Core::DebugContext *dc)
{
        if (dc) {
                dc->begin ();
        }
}

/****************************************************************************/

void dcCommit (Core::DebugContext *dc)
{
        if (dc) {
                dc->commit ();
        }
}

/****************************************************************************/

void dcRollback (Core::DebugContext *dc)
{
        if (dc) {
                dc->rollback ();
        }
}

#endif
