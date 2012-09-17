/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef METACONTAINER_H_
#define METACONTAINER_H_

#include "container/metaStructure/interface/IDataVisitor.h"
#include "core/ApiMacro.h"
#include "MetaObject.h"
#include "core/allocator/ArrayRegionAllocator.h"
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/topological_sort.hpp>

namespace Container {

/**
 * Główna kolekcja obiektów metastruktury. Zazwyczaj użytkownik stworzy jedną taką
 * a potem wypełni ją obiektami takimi jak MappedMeta, IndexedMeta etc.
 * \ingroup Container
 */
class TILIAE_API MetaContainer {
public:

        MetaContainer () : memoryAllocator () {}
        ~MetaContainer ();

        /// O(N)
        MetaObject const *get (const std::string &key) const;

        /**
         * Zdecydowałem sie na taki interfejs poniewaz kazdy
         * dodawany IMeta powinien miec ustawione ID. To, ze
         * mozna tworzyc beany w XMLu bez podawania ID, to jest
         * tylko i wyłącznie specyfika XML. Metastruktura jest
         * ponad tym.
         */
        void add (MetaObject *val);
        void addInner (MetaObject *outer, MetaObject *inner);

        void accept (IContainerVisitor *visitor) { visitor->visit (this); }

        MetaMap const &getMetaMap () const { return metaMap; }

        Ptr <MetaContainer> getLinked () { return linked; }
        Ptr <MetaContainer const> getLinked () const { return linked; }
        void setLinked (Ptr <MetaContainer> l) { linked = l; }

        Core::ArrayRegionAllocator <char> *getMemoryAllocator () { return &memoryAllocator; }

        /**
         * Should be invoked after MetaStructure is complete, that is after
         * all MetaObjects was added.
         */
        void updateParents ();

        /**
         * Returns a collection of pointers to MetaObjects in topological order,
         * which guarantees, that MetaObjects with no dependencies, or with smallest
         * number of dependencies are before those which depends on them.
         */
        MetaDeque topologicalSort ();

private:

        typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

        Core::StringVector getRuntimeDependencies (MetaObject const *meta) const;
        void fillGraph  (MetaObject const *meta, size_t metaNumber, MetaDeque *sorted, Graph *graph, BidirectionalMetaIndex const *index) const;
        void prepareBidirectionalIndex (BidirectionalMetaIndex *index, Graph *graph) const;
        const char *getDependencyName (IData *data) const;
        friend std::ostream &operator<< (std::ostream &o, MetaContainer const &m);

private:

        MetaMap metaMap;
        Ptr <MetaContainer> linked;
        Core::ArrayRegionAllocator <char> memoryAllocator;
};

TILIAE_API std::ostream &operator<< (std::ostream &o, MetaContainer const &m);

}

#endif /* METACONTAINER_H_ */
