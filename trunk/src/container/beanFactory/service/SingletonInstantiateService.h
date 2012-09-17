/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANFACTORY_SINGLETON_INSTANTIATE_SERVICE_H_
#define BEANFACTORY_SINGLETON_INSTANTIATE_SERVICE_H_

#include "container/beanFactory/service/BeanFactoryService.h"
#include "core/allocator/IAllocator.h"

using Core::IAllocator;

namespace Container {

class MetaObject;

/**
 * Instantiates singletons.
 */
class SingletonInstantiateService : public BeanFactoryService {
public:

        SingletonInstantiateService (IAllocator *m) : memoryAllocator (m) {}
        virtual ~SingletonInstantiateService () {}
        virtual bool onMetaEnd (MetaObject const *meta);

private:

        IAllocator *memoryAllocator;
};

}

#	endif /* BEANFACTORYINITSERVICE_H_ */
