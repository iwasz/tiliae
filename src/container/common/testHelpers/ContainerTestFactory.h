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

using Container::XmlContainerFactory;

namespace Container {
class MetaContainer;
class BeanFactoryContainer;
}

/**
 * Z innej beczki zupel
 */
struct ContainerTestFactory {

        static Ptr <Container::BeanFactoryContainer> getContainer (const std::string &xmlFilePath);

        static Ptr <Container::MetaContainer> createMetaStructure01 ();
        static Ptr <Container::MetaContainer> createMetaStructure02 ();
        static Ptr <Container::MetaContainer> createMetaStructure03 ();
        static Ptr <Container::MetaContainer> createMetaStructure04 ();
        static Ptr <Container::MetaContainer> createMetaStructure05 ();
        static Ptr <Container::MetaContainer> createMetaStructure06 ();
        static Ptr <Container::MetaContainer> createMetaStructure07 ();
        static Ptr <Container::MetaContainer> createMetaStructure08 ();
        static Ptr <Container::MetaContainer> createMetaStructure09 ();
        static Ptr <Container::MetaContainer> createMetaStructure10 ();
        static Ptr <Container::MetaContainer> createMetaStructure11 ();
        static Ptr <Container::MetaContainer> createMetaStructure12 ();
        static Ptr <Container::MetaContainer> createMetaStructure13 ();
        static Ptr <Container::MetaContainer> createMetaStructure14 ();
        static Ptr <Container::MetaContainer> createMetaStructure15 ();
        static Ptr <Container::MetaContainer> createMetaStructure16 ();
        static Ptr <Container::MetaContainer> createMetaStructure17 ();
        static Ptr <Container::MetaContainer> createMetaStructure18 ();
        static Ptr <Container::MetaContainer> createMetaStructure19 ();
        static Ptr <Container::MetaContainer> createMetaStructure20 ();
        static Ptr <Container::MetaContainer> createMetaStructure21 ();
        static Ptr <Container::MetaContainer> createMetaStructure22 ();
        static Ptr <Container::MetaContainer> createMetaStructure23 ();
        static Ptr <Container::MetaContainer> createMetaStructure24 ();
        static Ptr <Container::MetaContainer> createMetaStructure25 ();
        static Ptr <Container::MetaContainer> createMetaStructure26 ();

        static Container::ContainerFactory cf;
        static Ptr <Container::BeanFactoryContainer> container;

};

#endif /* CONTAINERTESTFACTORY_H_ */
