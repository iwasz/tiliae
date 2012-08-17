/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANFACTORY_SINGLETON_INSTANTIATE_SERVICE_H_
#define BEANFACTORY_SINGLETON_INSTANTIATE_SERVICE_H_

#include "beanFactory/service/BeanFactoryService.h"

namespace Container {

class MetaObject;

/**
 * Instantiates singletons.
 */
class SingletonInstantiateService : public BeanFactoryService {
public:

        virtual ~SingletonInstantiateService () {}
        virtual bool onMetaEnd (MetaObject *meta);

};

}

#	endif /* BEANFACTORYINITSERVICE_H_ */
