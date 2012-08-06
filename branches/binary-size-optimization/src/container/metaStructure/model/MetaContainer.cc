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
//                delete i->second;
                i->second->~MetaObject ();
        }
}

/****************************************************************************/

void MetaContainer::add (MetaObject *val)
{
        std::string id = val->getId ();

        if (boost::trim_copy (id) == "") {
                throw ConfigurationException ("MetaContainer::add : ID is empty. Root level beans must have proper ID.");
        }

        if (get (id)) {
                throw ConfigurationException ("MetaContainer::add : There is already a bean with ID [" + id + "].");
        }

        metaMap[id] = val;
}

/****************************************************************************/

MetaObject *MetaContainer::get (const std::string &key) const
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
