/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include "BeanFactoryService.h"
#include "metaStructure/model/MetaStructure.h"
#include "beanFactory/service/ValueServiceHelper.h"

namespace Container {

using namespace Core;

void BeanFactoryService::setContext (VisitorContext *c)
{
        ctx = dynamic_cast <BeanFactoryVisitorContext *> (c);

        if (!ctx) {
                throw ContainerException ("Failed to dynamic_cast argument c of type VisitorContext * to BeanFactoryVisitorContext * in BeanFactoryAwareService::setContext.");
        }
}

}

