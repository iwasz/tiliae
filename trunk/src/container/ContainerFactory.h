/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONTAINERFACTORY_H_
#define CONTAINERFACTORY_H_

#include "container/beanFactory/BeanFactory.h"
#include "container/beanFactory/service/BeanFactoryService.h"
#include "container/beanFactory/BeanFactoryContainer.h"
#include "core/Pointer.h"
#include "core/ApiMacro.h"
#include "core/allocator/IAllocator.h"

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
class InternalSingletons;

/**
 * Fabryka tworząca kontener. Tworzy kontener, który z kolei tworzy
 * obiekty na podstawie meta-informacji.
 * \ingroup Container
 */
class TILIAE_API ContainerFactory {
public:

        /**
         * Tworzy kontener, czyli główny obiekt kontenera (klasy Container).
         */
        static Ptr <BeanFactoryContainer> create (Ptr <MetaContainer> metaCont,
                                                  bool storeMetaContainer = false,
                                                  BeanFactoryContainer *linkedParent = NULL);

        /**
         * Inicjuje kontener stworzony za pomocą create.
         */
        static void init (BeanFactoryContainer *bfCont, MetaContainer *metaCont);

        /**
         * Metoda robi to co create + init.
         */
        static Ptr <BeanFactoryContainer> createAndInit (Ptr <MetaContainer> metaCont,
                                                         bool storeMetaContainer = false,
                                                         BeanFactoryContainer *linkedParent = NULL);

private:

        /// Singletony powiny być skasowane (dalete) w BeanFactoryContainer.
        static Wrapper::BeanWrapper *createBeanWrapper ();
        /// Singletony powiny być skasowane (dalete) w BeanFactoryContainer. ContainerFactory tworzy je per BeanFactoryContainer.
        static InternalSingletons *createSingletons (Core::IAllocator *memoryAllocator, SparseVariantMap *singletons);
};

} // ContainerFactory

#endif /* CONTAINERFACTORY_H_ */
