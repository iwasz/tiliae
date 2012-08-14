/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef METACONTAINER_H_
#define METACONTAINER_H_

#include "metaStructure/interface/IDataVisitor.h"
#include "ApiMacro.h"
#include "MetaObject.h"
#include "allocator/ArrayRegionAllocator.h"
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
        MetaObject *get (const std::string &key) const;

        /**
         * Zdecydowałem sie na taki interfejs poniewaz kazdy
         * dodawany IMeta powinien miec ustawione ID. To, ze
         * mozna tworzyc beany w XMLu bez podawania ID, to jest
         * tylko i wyłącznie specyfika XML. Metastruktura jest
         * ponad tym.
         */
        void add (MetaObject *val);

        void accept (IContainerVisitor *visitor) { visitor->visit (this); }

        MetaMap const &getMetaMap () const { return metaMap; }

        Ptr <MetaContainer const> getLinked () const { return linked; }
        void setLinked (Ptr <MetaContainer const> l) { linked = l; }

        Core::ArrayRegionAllocator <char> *getMemoryAllocator () { return &memoryAllocator; }
        MetaDeque topologicalSort ();

private:

        typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

        Core::StringList getRuntimeDependencies (MetaObject const *meta) const;
        void fillGraph  (MetaObject *meta, size_t metaNumber, MetaDeque *sorted, Graph *graph, BidirectionalMetaIndex const *index);
        void prepareBidirectionalIndex (BidirectionalMetaIndex *index, size_t *conunter, MetaObject *meta = NULL);
        friend std::ostream &operator<< (std::ostream &o, MetaContainer const &m);

private:

        MetaMap metaMap;
        Ptr <MetaContainer const> linked;
        Core::ArrayRegionAllocator <char> memoryAllocator;
};

TILIAE_API std::ostream &operator<< (std::ostream &o, MetaContainer const &m);

}

#endif /* METACONTAINER_H_ */
