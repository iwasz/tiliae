/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MetaContainer.h"
#include "common/Exceptions.h"

namespace Container {

void MetaContainer::add (Ptr <IMeta> val)
{
        metaMap[val->getId ()] = val;
}

/****************************************************************************/

Ptr <IMeta> MetaContainer::get (const std::string &key) const
{
        MetaMap::const_iterator i;
        if ((i = metaMap.find (key)) != metaMap.end ()) {
                return i->second;
        }

        if (getLinked ()) {
#if 0
                std::cerr << "Linked search : [" << key << "]" << std::endl;
#endif
                return getLinked ()->get (key);
        }

        return Ptr <IMeta> ();
}

}
