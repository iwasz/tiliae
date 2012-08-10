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
#include "StrUtil.h"
#include "data/ValueData.h"
#include "data/RefData.h"
#include "ScalarFactory.h"

namespace Container {

MetaContainer::~MetaContainer ()
{
        for (MetaMap::iterator i = metaMap.begin (); i != metaMap.end (); ++i) {
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

	if (get (val->getId ())) {
                throw ConfigurationException ("MetaContainer::add : There is already a bean with ID [" + id + "].");
        }

        metaMap[val->getId ()] = val;
}

/****************************************************************************/

MetaObject *MetaContainer::get (const std::string &key) const
{
        MetaMap::const_iterator i;
        if ((i = metaMap.find (key.c_str ())) != metaMap.end ()) {
                return i->second;
        }

        if (getLinked ()) {
                return getLinked ()->get (key);
        }

        return NULL;
}

/****************************************************************************/

Core::StringList MetaContainer::getRuntimeDependencies (std::string const &metaName) const
{
        Core::StringList deps;

        // Find MetaObject
        MetaObject *meta = get (metaName);

        DataKeyVector fields = meta->getFields ();

        // Check refs and value.type-s
        for (DataKeyVector::const_iterator i = fields.begin (); i != fields.end (); ++i) {
                DataKey *dk = *i;
                const char *depName = NULL;

                if (typeid (*dk->data) == typeid (ValueData)) {
                        ValueData *vd = static_cast <ValueData *> (dk->data);

                        depName = vd->getType ();

                        if (!depName || !strlen (depName)) {
                                continue;
                        }

                        // Jeżeli typ value jest typem wbudowanym, to nie jest to zależność·
                        if (Factory::ScalarFactory::isTypeSupported (depName)) {
                                continue;
                        }

                }
                else if (typeid (*dk->data) == typeid (RefData)) {
                        RefData *rd = static_cast <RefData *> (dk->data);
                        depName = rd->getData ();
                }

                if (!depName || !strlen (depName)) {
                        continue;
                }

                // Jeśli custom type nie jest odnalezione w MetaContainer, to jest to zależność, ale olewamy ją, bo może chodzić o external-singleton.
                if (!get (depName)) {
                        continue;
                }

                deps.push_back (depName);
        }

        // Check editor
        std::string editorName = mkCopy (meta->getEditor ());

        if (get (editorName)) {
                deps.push_back (editorName);
        }

        // Check factory
        std::string factoryName = mkCopy (meta->getFactory ());

        if (get (factoryName)) {
                deps.push_back (factoryName);
        }

        return deps;
}

/****************************************************************************/

MetaVector MetaContainer::topologicalSort () const
{
        MetaVector metaVector;


        return metaVector;
}

}
