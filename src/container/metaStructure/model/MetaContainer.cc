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
#include "../../../core/StrUtil.h"

namespace Container {

MetaContainer::~MetaContainer ()
{
        for (MetaVector::const_iterator i = metaVector.begin (); i != metaVector.end (); ++i) {
                (*i)->~MetaObject();
        }
}

/****************************************************************************/

void MetaContainer::add (MetaObject *val)
{
        std::string id = val->getId ();

        if (boost::trim_copy (id) == "") {
                throw ConfigurationException ("MetaContainer::add : ID is empty. Root level beans must have proper ID.");
        }

        metaVector.push_back (val);
}

/****************************************************************************/

MetaObject *MetaContainer::get (const std::string &key) const
{
        for (MetaVector::const_iterator i = metaVector.begin (); i != metaVector.end (); ++i) {
                if (!strcmpNull ((*i)->getId (), key.c_str ())) {
                        return *i;
                }
        }

        if (getLinked ()) {
                return getLinked ()->get (key);
        }

        return NULL;
}

}
