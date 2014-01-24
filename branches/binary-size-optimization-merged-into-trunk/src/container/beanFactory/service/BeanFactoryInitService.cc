/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <BeanWrapper.h>

#include "BeanFactoryInitService.h"
#include "metaStructure/model/MetaStructure.h"
#include <cassert>
#include <boost/make_shared.hpp>
#include "../BeanFactory.h"
#include "StrUtil.h"

namespace Container {

using namespace Core;

bool BeanFactoryInitService::onMetaBegin (MetaObject const *meta)
{
        if (!meta || meta->getAbstract ()) {
                return false;
        }

        std::string id = toStr (meta->getId ());
        BeanFactoryContainer *container = getBVFContext ()->getBeanFactoryContainer ();
        BeanFactory *beanFactory = new BeanFactory (container);
        beanFactory->setBeanWrapper(defaultBeanWrapper);
        beanFactory->setAttributes (meta->getAttributes ()->makeCopyOnHeap ());
        getBVFContext ()->setCurrentBF (beanFactory);
        return true;
}

}