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
#include "../src/container/metaStructure/model/meta/MappedMeta.h"
#include "../src/container/metaStructure/model/meta/IndexedMeta.h"
#include "../src/container/inputFormat/mxml/MXmlMetaService.h"
#include "../src/container/metaStructure/model/data/RefData.h"
#include "../src/container/metaStructure/model/data/ValueData.h"
#include "../src/container/metaStructure/model/data/NullData.h"

using namespace Container;
using namespace std;

#define printSize(a) std::cout << #a "=" << sizeof(a) << std::endl;

/**
 *
 */

int main (int argc, char **argv)
{
        BeanFactory *table = new BeanFactory[1000];
        delete [] table;

        printSize (BeanFactory);
        printSize (std::string);
        printSize (Core::StringMap);
        printSize (Core::StringVector);
        printSize (Core::Variant);
        printSize (Ptr <Editor::IEditor>);
        printSize (std::auto_ptr <Editor::IEditor>);
        printSize (Attributes);
        printSize (int);
        printSize (bool);
        printSize (int *);

        printSize (Container::MappedMeta);
        printSize (Container::IndexedMeta);
        printSize (Container::RefData);
        printSize (Container::ValueData);
        printSize (Container::NullData);

#if 1
        Ptr <BeanFactoryContainer> container = ContainerFactory::createContainer (MXmlMetaService::parseFile ("../demo/main.xml"));
        Ptr <BookVector> v = vcast <Ptr <BookVector> > (container->getBean ("books"));

        BOOST_FOREACH (Ptr <Book> b, *v) {
                std::cout << b->toString () << std::endl;
        }

        Ptr <AuthorMap> a = vcast <Ptr <AuthorMap> > (container->getBean ("authorMap"));

        for (AuthorMap::const_iterator i = a->begin (); i != a->end (); ++i) {
                std::cout << i->first << ", " << i->second->toString () << std::endl;
        }

        a = vcast <Ptr <AuthorMap> > (container->getBean ("authorMap2"));

        for (AuthorMap::const_iterator i = a->begin (); i != a->end (); ++i) {
                std::cout << i->first << ", " << i->second->toString () << std::endl;
        }
#endif
}


