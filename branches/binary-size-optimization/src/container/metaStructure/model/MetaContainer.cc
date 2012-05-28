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

MetaContainer::~MetaContainer ()
{
        for (MetaMap::iterator i = metaMap.begin (); i != metaMap.end (); ++i) {
                delete i->second;
        }
}

/****************************************************************************/

void MetaContainer::add (IMeta *val)
{
        metaMap[val->getId ()] = val;
}

/****************************************************************************/

IMeta *MetaContainer::get (const std::string &key) const
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

        return NULL;
}

}
