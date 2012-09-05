/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FACTORYSERVICE_H_
#define FACTORYSERVICE_H_

#include "beanFactory/service/BeanFactoryService.h"

namespace Editor {
class IndexedEditor;
}

namespace Container {

class MetaObject;

/**
 * Create factory
 */
class FactoryService : public BeanFactoryService {
public:

        FactoryService () : defaultSingletonFactory (NULL), defaultPrototypeFactory (NULL) {}
        virtual ~FactoryService () {}

        virtual bool onMetaBegin (const MetaObject* data);

        void setDefaultSingletonFactory (Factory::IFactory* defaultSingletonFactory) { this->defaultSingletonFactory = defaultSingletonFactory; }
        void setDefaultPrototypeFactory (Factory::IFactory* defaultPrototypeFactory) { this->defaultPrototypeFactory = defaultPrototypeFactory; }

private:

        // Singletons owned by BeanFactoryContainer.
        Factory::IFactory *defaultSingletonFactory;
        Factory::IFactory *defaultPrototypeFactory;
};

} //nam

#	endif /* FACTORYSERVICE_H_ */
