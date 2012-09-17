/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANFACTORYSERVICE_H_
#define BEANFACTORYSERVICE_H_

#include "container/metaStructure/service/AbstractMetaService.h"
#include "container/beanFactory/BeanFactory.h"
#include "container/metaStructure/service/DummyService.h"
#include "BeanFactoryVisitorContext.h"

namespace Container {

class BeanFactoryService : public DummyMetaService {
public:

        BeanFactoryService () : ctx (NULL) {}

        virtual void setContext (VisitorContext *c);
        virtual BeanFactoryVisitorContext *getBVFContext () const { return ctx; }

private:

        BeanFactoryVisitorContext *ctx;

};

}

#	endif /* BEANFACTORYSERVICE_H_ */
