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

namespace Editor {
class StringFactoryMethodEditor;
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

        /**
         * Tworzy kontener, czyli główny obiekt kontenera (klasy Container).
         */
        static Ptr <BeanFactoryContainer> createContainer (Ptr <MetaContainer> metaCont,
                        bool storeMetaContainer = false,
                        Ptr <BeanFactoryContainer> linkedParent = Ptr <BeanFactoryContainer> ());

        static Ptr <BeanFactoryContainer> createEmptyContainer (Ptr <MetaContainer> metaCont,
                        bool storeMetaContainer,
                        Ptr <BeanFactoryContainer> linkedParent, ContainerFactory &cf);

        void fill (Ptr <BeanFactoryContainer> bfCont, Ptr <MetaContainer> metaCont);

protected:

        Ptr <BeanFactoryContainer> create ();

        Ptr <Wrapper::BeanWrapper> createBeanWrapper ();
        Ptr <Core::VariantMap> createSingletons ();

private:

        Ptr <MetaVisitor> iteration0; // TODO testowa, w celu naprawienia błędu z parentowaniem.
        Ptr <MetaVisitor> iteration1;
        Ptr <MetaVisitor> iteration2;
        Ptr <Core::VariantMap> singletons;
        Ptr <Editor::StringFactoryMethodEditor> conversionMethodEditor;
        BeanFactoryVisitorContext context;
};

} // ContainerFactory

#endif /* CONTAINERFACTORY_H_ */
