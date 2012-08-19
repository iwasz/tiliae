/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANFACTORY_SINGLETON_DELETE_SERVICE_H_
#define BEANFACTORY_SINGLETON_DELETE_SERVICE_H_

#include "beanFactory/service/BeanFactoryService.h"

namespace Container {

class MetaObject;

/**
 * Delete unused BeanFactories
 */
class SingletonFactoryDeleteService : public BeanFactoryService {
public:

        virtual ~SingletonFactoryDeleteService () {}
        virtual bool onMetaEnd (MetaObject *meta);

};

}

#	endif /* BEANFACTORYINITSERVICE_H_ */
