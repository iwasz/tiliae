/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONTAINERFACTORY_H_
#define CONTAINERFACTORY_H_

#include "beanFactory/BeanFactory.h"
#include "beanFactory/service/BeanFactoryService.h"
#include "../core/Pointer.h"
#include "../core/ApiMacro.h"

namespace Wrapper {
class BeanWrapper;
}

namespace Container {
class MetaContainer;
class MetaVisitor;
class XmlMetaService;

/**
 * Fabryka tworząca kontener. Tworzy kontener, który z kolei tworzy
 * obiekty na podstawie meta-informacji.
 * \ingroup Container
 */
class TILIAE_API ContainerFactory {
public:

        ContainerFactory ();
        virtual ~ContainerFactory () {}

        Ptr <BeanFactoryContainer> create ();
        void fill (Ptr <BeanFactoryContainer> bfCont, Ptr <MetaContainer> metaCont);

        /**
         * Tworzy kontener, czyli główny obiekt kontenera (klasy Container).
         */
        static Ptr <BeanFactoryContainer> createContainer (Ptr <MetaContainer> metaCont);
        static Ptr <Wrapper::BeanWrapper> createBeanWrapper ();
        static Ptr <Core::VariantMap> createSingletons ();

private:

        Ptr <MetaVisitor> iteration1;
        Ptr <MetaVisitor> iteration2;
        Ptr <Core::VariantMap> singletons;
        BeanFactoryVisitorContext context;
};

/*##########################################################################*/

/**
 * Fabryka tworząca kontener. Tworzy kontener, który z kolei tworzy
 * obiekty na podstawie meta-informacji. Potradi przetworzyć opis XML
 * na meta-strukturę, tak więc w jednym kroku potrafi stworzyć kontener
 * z XML.
 * \ingroup Container
 */
class TILIAE_API XmlContainerFactory : public ContainerFactory {
public:

        XmlContainerFactory ();
        virtual ~XmlContainerFactory () {}

        /**
         * Tworzy kontener z pliku XML. Beany pobieramy z kontenera, który jest
         * zwracany przez tą statyczną metodę. Jako drugi argumen podajemy już wcześniej
         * utworzony kontener, który pełnić będzie rolę rodzica dla tego nowego. Dzięki
         * temu można w tym nowym korzystać z beanów zawartych w tym starym (ale nie na
         * odwrót). Działa to trochę jak <import>.
         *
         * \param storeMetaContainer Oznacza czy utworzony BeanFactoryContainer ma pamiętać
         * wskaźnik do swojego MetaContainer. Jeśli pamięta, to umożliwia to linkowanie innych
         * kontenerów.
         */
        static Ptr <BeanFactoryContainer> createContainer (const std::string &xmlFilePath,
                        bool storeMetaContainer = false,
                        Ptr <BeanFactoryContainer> linkedParent = Ptr <BeanFactoryContainer> ());

/*--------------------------------------------------------------------------*/

        Ptr <MetaContainer> parseXml (const std::string &xmlFilePath);
        void fill (Ptr <BeanFactoryContainer> bfCont, const std::string &xmlFilePath);

private:

        Ptr <XmlMetaService> metaService;
};

} // ContainerFactory

#endif /* CONTAINERFACTORY_H_ */
