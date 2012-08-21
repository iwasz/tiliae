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

void MetaContainer::addInner (MetaObject *outer, MetaObject *inner)
{
        outer->addInnerMeta (inner);
        add (inner);
}

/****************************************************************************/

MetaObject const *MetaContainer::get (const std::string &key) const
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

Core::StringVector MetaContainer::getRuntimeDependencies (MetaObject const *meta) const
{
        Core::StringVector deps = meta->getDependsOn ();

        DataKeyVector fields = meta->getFields ();

        // Check refs and value.type-s
        for (DataKeyVector::const_iterator i = fields.begin (); i != fields.end (); ++i) {
                DataKey *dk = *i;
                const char *depName = getDependencyName (dk->data);

                if (depName) {
                        deps.push_back (depName);
                }
        }

        DataVector cArgs = meta->getConstructorArgs ();
        for (DataVector::const_iterator i = cArgs.begin (); i != cArgs.end (); ++i) {
                const char *depName = getDependencyName (*i);

                if (depName) {
                        deps.push_back (depName);
                }
        }

        // Check editor
        std::string editorName = meta->getEditor ();

        if (get (editorName)) {
                deps.push_back (editorName);
        }

        // Check factory
        std::string factoryName = meta->getFactory ();

        if (get (factoryName)) {
                deps.push_back (factoryName);
        }

        return deps;
}

/****************************************************************************/

const char *MetaContainer::getDependencyName (IData *data) const
{
        const char *depName = NULL;

        if (typeid (*data) == typeid (ValueData)) {
                ValueData *vd = static_cast <ValueData *> (data);

                depName = vd->getType ();

                if (!depName || !strlen (depName)) {
                        return NULL;
                }

                // Jeżeli typ value jest typem wbudowanym, to nie jest to zależność·
                if (Factory::ScalarFactory::isTypeSupported (depName)) {
                        return NULL;
                }

        }
        else if (typeid (*data) == typeid (RefData)) {
                RefData *rd = static_cast <RefData *> (data);
                depName = rd->getData ();
        }

        if (!depName || !strlen (depName)) {
                return NULL;
        }

        // Jeśli custom type nie jest odnalezione w MetaContainer, to jest to zależność, ale olewamy ją, bo może chodzić o external-singleton.
        if (!get (depName)) {
                return NULL;
        }

        return depName;
}

/****************************************************************************/

MetaDeque MetaContainer::topologicalSort ()
{
        MetaDeque sorted;
        BidirectionalMetaIndex index;
        Graph graph;

        prepareBidirectionalIndex (&index, &graph);

        for (BidirectionalMetaIndex::MetaToInt::iterator i = index.metaToInt.begin (); i != index.metaToInt.end (); ++i) {
                MetaObject const *meta = i->first;
                size_t metaNumber = i->second;

                fillGraph (meta, metaNumber, &sorted, &graph, &index);
        }

        typedef boost::graph_traits <Graph>::vertex_descriptor Vertex;
        typedef std::vector <Vertex> Container;
        Container c;

        try {
                boost::topological_sort (graph, std::back_inserter (c));
        }
        catch (...) {
                throw RoundReferenceException ("MetaContainer::topologicalSort : circular dependency detected.");
        }

        for (Container::const_iterator i = c.begin (); i != c.end (); ++i) {
                MetaObject const *meta = index.get (*i);
                assert (meta);
                sorted.push_back (meta);
        }

        return sorted;
}

/****************************************************************************/

void MetaContainer::fillGraph  (MetaObject const *meta, size_t metaNumber, MetaDeque *sorted, Graph *graph, BidirectionalMetaIndex const *index) const
{
        Core::StringVector deps = getRuntimeDependencies (meta);

        for (Core::StringVector::const_iterator i = deps.begin (); i != deps.end (); ++i) {
                MetaObject const *dependency = get (*i);

                if (!dependency) {
                        continue;
                }

                size_t dependencyNumber = index->get (dependency);
                boost::add_edge (metaNumber, dependencyNumber, *graph);
#if 0
                std::cerr << "add_edge (" << metaNumber << ", " << dependencyNumber << ")" << std::endl;
#endif
        }
}

/****************************************************************************/

void MetaContainer::prepareBidirectionalIndex (BidirectionalMetaIndex *index, Graph *graph) const
{
        for (MetaMap::const_iterator i = metaMap.begin (); i != metaMap.end (); ++i) {
                size_t vertexDescriptor = boost::add_vertex (*graph);
                index->add (vertexDescriptor, i->second);
        }

        if (linked) {
                linked->prepareBidirectionalIndex (index, graph);
        }

        return;
}

/****************************************************************************/

void MetaContainer::updateParents ()
{
        for (MetaMap::const_iterator i = metaMap.begin (); i != metaMap.end (); ++i) {
                MetaObject *child = i->second;

                if (!child->containsAttribute (Attributes::PARENT_ARGUMENT)) {
                        continue;
                }

                std::string parentName = child->getParent ();
                MetaObject const *parent = get (parentName);

                if (!parent) {
                        throw NoSuchBeanException ("MetaContainer::updateParents : Wrong 'parent' value. There is no bean with id =" + parentName);
                }

                if ((child->getType () == MetaObject::INDEXED && parent->getType () == MetaObject::MAPPED) ||
                    (child->getType () == MetaObject::MAPPED && parent->getType () == MetaObject::INDEXED)) {
                        throw ConfigurationException ("MetaContainer::updateParents : parent is MAPPED and child is INDEXED or vice versa.");
                }

                child->setParentMeta (parent);
        }

        if (linked) {
                linked->updateParents ();
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
