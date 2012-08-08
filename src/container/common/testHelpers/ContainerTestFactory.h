/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONTAINERTESTFACTORY_H_
#define CONTAINERTESTFACTORY_H_

#include <Pointer.h>
#include "ContainerFactory.h"
#include "../../metaStructure/model/MetaFactory.h"

namespace Container {
class MetaContainer;
class BeanFactoryContainer;
}

/**
 * Z innej beczki zupel
 */
struct ContainerTestFactory {

        static Ptr <Container::BeanFactoryContainer> getContainer (const std::string &xmlFilePath);

        static Ptr <Container::MetaContainer> createMetaStructure01 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure02 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure03 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure04 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure05 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure06 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure07 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure08 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure09 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure10 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure11 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure12 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure13 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure14 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure15 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure16 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure17 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure18 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure19 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure20 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure21 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure22 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure23 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure24 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure25 (Container::MetaFactory *factory);
        static Ptr <Container::MetaContainer> createMetaStructure26 (Container::MetaFactory *factory);

        static Container::ContainerFactory cf;
        static Ptr <Container::BeanFactoryContainer> container;

};

#endif /* CONTAINERTESTFACTORY_H_ */
