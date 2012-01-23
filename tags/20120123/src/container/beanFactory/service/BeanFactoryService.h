/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANFACTORYSERVICE_H_
#define BEANFACTORYSERVICE_H_

#include "metaStructure/service/AbstractMetaService.h"
#include "beanFactory/BeanFactory.h"
#include "metaStructure/service/DummyService.h"
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
