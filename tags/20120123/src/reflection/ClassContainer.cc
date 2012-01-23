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

using boost::detail::lexical_cast;

namespace Reflection {
using namespace Core;

/****************************************************************************/

Ptr<Class> ClassContainer::get (const std::string &className) const
{
        Multi::nth_index<0>::type::iterator i = body.find (className);

        if (i == body.end ()) {
                return Ptr<Class> ();
        }

        return *i;
}

/****************************************************************************/

Ptr<Class> ClassContainer::get (std::type_info const &t) const
{
        TypeMap::const_iterator i = typeMap.find (&t);
        return (i == typeMap.end ()) ? (Ptr <Class> ()) : (i->second);
}

/****************************************************************************/

void ClassContainer::add (Ptr<Class> clazz)
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

                Ptr <Class> cls = *i;
                ret += cls->toString ();

                if (++i != body.end ()) {
                        ret += ", ";
                }
        }

        return ret + ")";
}

}
