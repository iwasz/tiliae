/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BeanStackUpdateService.h"
#include <cassert>
#include "../../metaStructure/model/MetaObject.h"
#include "StrUtil.h"

namespace Container {

using namespace Core;

bool BeanStackUpdateService::onMetaBegin (MetaObject *data)
{
        if (data->getAbstract()) {
                return false;
        }

        std::string id = toStr (data->getId ());
        BeanFactoryStack &stack = getBVFContext ()->getStack();
        Ptr <BeanFactory> beanFactory;

        // Top-level beans are taken directly from container.
        if (stack.empty ()) {
                BeanFactoryContainer *container = getBVFContext ()->getBeanFactoryContainer ();
                beanFactory = container->getBeanFactory (id);
        }
        else {
                Ptr <BeanFactory> parent = getBVFContext ()->getCurrentBF ();
                beanFactory = parent->getInnerBeanFactory (id);
        }

        stack.push (beanFactory);
        return true;
}

/****************************************************************************/

bool BeanStackUpdateService::onMetaEnd (MetaObject *data)
{
        if (data->getAbstract()) {
                return false;
        }

        BeanFactoryStack &stack = getBVFContext ()->getStack();
        assert (!stack.empty ());
        stack.pop ();
        return true;
}

}
