/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MetaContainer.h"
#include "common/Exceptions.h"
#include <boost/algorithm/string/trim.hpp>

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
        if (boost::trim_copy (val->getId ()) == "") {
                throw ConfigurationException ("MetaContainer::add : ID is empty. Root level beans must have proper ID.");
        }

        if (get (val->getId ())) {
                throw ConfigurationException ("MetaContainer::add : There is already a bean with ID [" + val->getId () + "].");
        }

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
