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

        FactoryService () : defaultSingletonFactory (NULL) {}
        virtual ~FactoryService () {}
        void init (Core::VariantMap *singletons);

        virtual bool onMetaBegin (MetaObject const *data);

private:

        // Singletons owned by BeanFactoryContainer.
        Factory::IFactory *defaultSingletonFactory;
};

} //nam

#	endif /* FACTORYSERVICE_H_ */
