/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MachineContext.h"
#include "../../core/Typedefs.h"
#include "../Exceptions.h"

namespace Machine {

/****************************************************************************/

Core::Variant MachineContext::get (const std::string &name) const
{
        for (std::vector <Core::VariantMap *>::const_reverse_iterator i = stack.rbegin (); i != stack.rend (); ++i) {
                Core::VariantMap::const_iterator j = (*i)->find (name);

                if (j != (*i)->end ()) {
                        return j->second;
                }
        }

        return Core::Variant ();
}

/****************************************************************************/

void MachineContext::set (const std::string &name, const Core::Variant &object)
{
        if (stack.empty ()) {
                throw StateException ("MachineContext::set : stack empty.");
        }

        stack.back ()->operator [] (name) = object;
}

/****************************************************************************/

std::string MachineContext::toString () const
{
        std::string ret = "MachineContext (";
        ret += ")";
        return ret;
}

}
