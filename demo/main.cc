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

using namespace Container;
using namespace std;

/**
 *
 */

int main (int argc, char **argv)
{
        Ptr <BeanFactoryContainer> container = XmlContainerFactory::createContainer ("../demo/main.xml");
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
}


