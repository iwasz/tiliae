/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <string>
#include <boost/lexical_cast.hpp>
#include "ClassContainer.h"

namespace Reflection {
using namespace Core;

/****************************************************************************/

ClassContainer::~ClassContainer ()
{
        for (Multi::nth_index<0>::type::iterator i = body.begin (); i != body.end (); ++i) {
                delete *i;
        }
}

/****************************************************************************/

Class *ClassContainer::get (const std::string &className) const
{
        Multi::nth_index<0>::type::iterator i = body.find (className);

        if (i == body.end ()) {
                return NULL;
        }

        return *i;
}

/****************************************************************************/

Class *ClassContainer::get (std::type_info const &t) const
{
        TypeMap::const_iterator i = typeMap.find (&t);
        return (i == typeMap.end ()) ? (NULL) : (i->second);
}

/****************************************************************************/

void ClassContainer::add (Class *clazz)
{
#if 0
        Multi::nth_index<0>::type::iterator i = body.find (clazz->getName ());
        std::cerr << clazz->getName () << std::endl;

        if (i != body.end ()) {
                throw ClassAllreadyManagedException ("ClassAllreadyManagedException (" + clazz->getName () + ")");
        }
#endif

        body.get<0>().insert(clazz);
        typeMap[&clazz->getType ()] = clazz;
}

/****************************************************************************/

std::string ClassContainer::toString () const
{
        std::string ret = std::string ("ClassContainer (noOfClasses:") + boost::lexical_cast <std::string> (body.size ()) + ", classes:";

        Multi::nth_index<0>::type::iterator i = body.begin ();

        while (i != body.end ()) {

                Class *cls = *i;
                ret += cls->toString ();

                if (++i != body.end ()) {
                        ret += ", ";
                }
        }

        return ret + ")";
}

}
