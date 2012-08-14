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

Core::StringList MetaContainer::getRuntimeDependencies (MetaObject const *meta) const
{
        Core::StringList deps;

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

MetaDeque MetaContainer::topologicalSort ()
{
        MetaDeque sorted;
        BidirectionalMetaIndex index;
        Graph graph;
        size_t counter = 0;

        prepareBidirectionalIndex (&index, &counter);
//        std::cerr << index << std::endl;

        for (BidirectionalMetaIndex::MetaToInt::iterator i = index.metaToInt.begin (); i != index.metaToInt.end (); ++i) {
                MetaObject *meta = i->first;
                size_t metaNumber = i->second;

                fillGraph (meta, metaNumber, &sorted, &graph, &index);
        }

        typedef boost::graph_traits <Graph>::vertex_descriptor Vertex;
        typedef std::vector <Vertex> Container;
        Container c;
        boost::topological_sort (graph, std::back_inserter (c));

        for (Container::const_iterator i = c.begin (); i != c.end (); ++i) {
                MetaObject *meta = index.get (*i);
                assert (meta);
                sorted.push_back (meta);
        }

        return sorted;
}

/****************************************************************************/

void MetaContainer::fillGraph  (MetaObject *meta, size_t metaNumber, MetaDeque *sorted, Graph *graph, BidirectionalMetaIndex const *index)
{
        Core::StringList deps = getRuntimeDependencies (meta);

        // jeśli nie ma zależności, to dodajemy na początek.
        /*
         * TODO Tu powinny lądować tylko takie obiekty, które nie mają ani zaleznosci, ani nie zależą od niczego (czyli takie, które nie są cześcią grafu)!
         * W tym momencie jest błąd, który powoduje, że niektóre obiekty się dublują w kolekcji sorted (podwójnie sa te, które nie zależą od niczego, ale
         * od nich zależą inne).
         */
        if (deps.empty ()) {
                sorted->push_front (meta);
                return;
        }

        for (Core::StringList::const_iterator i = deps.begin (); i != deps.end (); ++i) {
                MetaObject *dependency = get (*i);

                if (!dependency) {
                        continue;
                }

                size_t dependencyNumber = index->get (dependency);
                boost::add_edge (metaNumber, dependencyNumber, *graph);
//                std::cerr << "add_edge (" << metaNumber << ", " << dependencyNumber << ")" << std::endl;
        }
}

/****************************************************************************/

void MetaContainer::prepareBidirectionalIndex (BidirectionalMetaIndex *index, size_t *counter, MetaObject *meta)
{
        if (!meta) {
                for (MetaMap::iterator i = metaMap.begin (); i != metaMap.end (); ++i) {
                        prepareBidirectionalIndex (index, counter, i->second);
                }

                return;
        }

        index->add ((*counter)++, meta);

        MetaMap innerMetas = meta->getInnerMetas ();
        for (MetaMap::iterator i = innerMetas.begin (); i != innerMetas.end (); ++i) {
                prepareBidirectionalIndex (index, counter, i->second);
        }
}

/****************************************************************************/

std::ostream &operator<< (std::ostream &o, MetaContainer const &m)
{
        o << "MetaContainer [";

        for (MetaMap::const_iterator i = m.metaMap.begin (); i != m.metaMap.end ();) {
                o << *i->second;

                if (++i != m.metaMap.end ()) {
                        o << ", ";
                }
        }

        o << "]";
        return o;
}

}
