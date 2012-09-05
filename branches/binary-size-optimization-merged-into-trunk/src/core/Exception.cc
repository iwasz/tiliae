/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Exception.h"

namespace Core {

std::string Exception::whatCopy;

Exception::Exception (std::string const &s)
{
        ctx.addMessage (s);
}

/****************************************************************************/

Exception::Exception (DebugContext const &db, std::string const &s)
{
        ctx.addContext (db);

        if (s != "") {
                ctx.addMessage (s);
        }
}

/****************************************************************************/

void Exception::addMessage (std::string const &m)
{
        ctx.addMessage (m);
}

/****************************************************************************/

void Exception::addContext (DebugContext const &dc)
{
        ctx.addContext (dc);
}

/****************************************************************************/

const char* Exception::what() const throw ()
{
        whatCopy = getMessage ();
        return whatCopy.c_str ();
}

}
