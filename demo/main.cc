/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/foreach.hpp>
#include "../src/container/beanFactory/BeanFactory.h"
#include "../src/container/ContainerFactory.h"
#include "Book.h"
#include "../src/container/metaStructure/model/MetaStructure.h"
#include "../src/container/inputFormat/mxml/MXmlMetaService.h"
#include <string>

using namespace Container;
using namespace std;

#define printSize(a) std::cout << #a "=" << sizeof(a) << std::endl;
#include <vector>
#include <list>


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
        printSize (Container::Attributes);
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


#if 1
        Ptr <MetaContainer> metaCtr = MXmlMetaService::parseFile ("../demo/main.xml");
//        Ptr <BeanFactoryContainer> container = ContainerFactory::createAndInit (metaCtr);
//        BookVector *v = vcast <BookVector *> (container->getBean ("books"));
//
//        BOOST_FOREACH (Book *b, *v) {
//                std::cout << b->toString () << std::endl;
//        }
//
//        AuthorMap *a = NULL;
//
//        if (container->containsBean ("authorMap")) {
//                a = vcast <AuthorMap *> (container->getBean ("authorMap"));
//
//                for (AuthorMap::const_iterator i = a->begin (); i != a->end (); ++i) {
//                        std::cout << i->first << ", " << i->second->toString () << std::endl;
//                }
//        }
//
//        if (container->containsBean ("authorMap2")) {
//                a = vcast <AuthorMap *> (container->getBean ("authorMap2"));
//
//                for (AuthorMap::const_iterator i = a->begin (); i != a->end (); ++i) {
//                        std::cout << i->first << ", " << i->second->toString () << std::endl;
//                }
//        }
#endif
}


