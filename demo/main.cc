/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/foreach.hpp>
#include "container/beanFactory/BeanFactory.h"
#include "container/ContainerFactory.h"
#include "Book.h"
#include "container/metaStructure/model/MetaStructure.h"
#include "container/inputFormat/mxml/MXmlMetaService.h"
#include <string>

  #include <boost/graph/graph_traits.hpp>
  #include <boost/graph/adjacency_list.hpp>
  #include <boost/graph/dijkstra_shortest_paths.hpp>
  #include <boost/graph/topological_sort.hpp>

using namespace Container;
using namespace std;
using namespace boost;

#define printSize(a) std::cout << #a "=" << sizeof(a) << std::endl;
#include <vector>
#include <list>

#include <google/sparse_hash_map>
using google::sparse_hash_map;      // namespace where class lives by default

//struct TILIAE_API AllocationException : public Core::Exception {
//        AllocationException (std::string const &m = "") : Core::Exception (m) {}
//        AllocationException (Core::DebugContext const &db, std::string const &s = "") : Core::Exception (db, s) {}
//        virtual ~AllocationException () throw () {}
//};


/**
 *
 */

int main (int argc, char **argv)
{
        {
        // create a typedef for the Graph type
        typedef adjacency_list<vecS, vecS, directedS> Graph;

        // Make convenient labels for the vertices
        enum { A, B, C, D, E, N };
        const int num_vertices = N;
//        const char* name = "ABCDE";

        // writing out the edges in the graph
        typedef std::pair<int, int> Edge;
//        Edge edge_array[] =
//        { Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
//          Edge(C,E), Edge(B,D), Edge(D,E) };

        Edge edge_array[] = { Edge (A, B), Edge (A, C), Edge (B, D), Edge (B, E)  };

        Graph g(edge_array, edge_array + sizeof(edge_array) / sizeof(Edge), num_vertices);

// ----

        // get the property map for vertex indices
        typedef property_map<Graph, vertex_index_t>::type IndexMap;
        IndexMap index = get(vertex_index, g);

        std::cout << "vertices(g) = ";
        typedef graph_traits<Graph>::vertex_iterator vertex_iter;
        std::pair<vertex_iter, vertex_iter> vp;
        for (vp = vertices(g); vp.first != vp.second; ++vp.first)
          std::cout << index[*vp.first] <<  " ";
        std::cout << std::endl;

// ----

        typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef std::vector< Vertex > container;
        container c;
        topological_sort(g, std::back_inserter(c));

        cout << "A topological ordering: ";
        for ( container::reverse_iterator ii=c.rbegin(); ii!=c.rend(); ++ii)
          cout << index(*ii) << " ";
        cout << endl;

        }

        sparse_hash_map<const char*, int, std::tr1::hash<const char*>, Eqstr> months;

        months["january"] = 31;
        months["february"] = 28;
        months["march"] = 31;
        months["april"] = 30;
        months["may"] = 31;
        months["june"] = 30;
        months["july"] = 31;
        months["august"] = 31;
        months["september"] = 30;
        months["october"] = 31;
        months["november"] = 30;
        months["december"] = 31;

        cout << "september -> " << months["september"] << endl;
        cout << "april     -> " << months["april"] << endl;
        cout << "june      -> " << months["june"] << endl;
        cout << "november  -> " << months["november"] << endl;

//        BeanFactory *table = new BeanFactory[1000];
//        delete [] table;
//
//        printSize (BeanFactory);
//        printSize (std::string);
//        printSize (Core::StringMap);
//        printSize (Core::StringVector);
//        printSize (Core::Variant);
//        printSize (Ptr <Editor::IEditor>);
//        printSize (std::auto_ptr <Editor::IEditor>);
//        printSize (Attributes);
//        printSize (int);
//        printSize (bool);
//        printSize (int *);
//
//        printSize (Container::Attributes);
//        printSize (Container::MetaObject);
//        printSize (Container::RefData);
//        printSize (Container::ValueData);
//        printSize (Container::NullData);
//
//        enum En { A, B, C };
//
//        printSize (En);
//        printSize (unsigned char);

//        for (int i = 0; i < 1000; ++i) {
////                new std::string ("test");
//                new char [5];
//        }

//        new char [5000];

//        std::list <char> vec (5000);


        Ptr <MetaContainer> metaCtr = MXmlMetaService::parseFile ("../demo/main.xml");
#if 1
        Ptr <BeanFactoryContainer> container = ContainerFactory::createAndInit (metaCtr);
        BookVector *v = vcast <BookVector *> (container->getBean ("books"));

        BOOST_FOREACH (Book *b, *v) {
                std::cout << b->toString () << std::endl;
        }

        AuthorMap *a = NULL;

        if (container->containsBean ("authorMap")) {
                a = vcast <AuthorMap *> (container->getBean ("authorMap"));

                for (AuthorMap::const_iterator i = a->begin (); i != a->end (); ++i) {
                        std::cout << i->first << ", " << i->second->toString () << std::endl;
                }
        }

        if (container->containsBean ("authorMap2")) {
                a = vcast <AuthorMap *> (container->getBean ("authorMap2"));

                for (AuthorMap::const_iterator i = a->begin (); i != a->end (); ++i) {
                        std::cout << i->first << ", " << i->second->toString () << std::endl;
                }
        }
#endif
}


