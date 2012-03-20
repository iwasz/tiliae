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

        /**
         * Tworzy kontener, czyli główny obiekt kontenera (klasy Container).
         */
        static Ptr <BeanFactoryContainer> createContainer (Ptr <MetaContainer> metaCont,
                        bool storeMetaContainer = false,
                        Ptr <BeanFactoryContainer> linkedParent = Ptr <BeanFactoryContainer> ());

protected:

        Ptr <BeanFactoryContainer> create ();
        void fill (Ptr <BeanFactoryContainer> bfCont, Ptr <MetaContainer> metaCont);

        static Ptr <Wrapper::BeanWrapper> createBeanWrapper ();
        static Ptr <Core::VariantMap> createSingletons ();

private:

        Ptr <MetaVisitor> iteration0; // TODO testowa, w celu naprawienia błędu z parentowaniem.
        Ptr <MetaVisitor> iteration1;
        Ptr <MetaVisitor> iteration2;
        Ptr <Core::VariantMap> singletons;
        BeanFactoryVisitorContext context;
};

} // ContainerFactory

#endif /* CONTAINERFACTORY_H_ */
