/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BeanStackUpdateService.h"
#include "metaStructure/model/meta/IMeta.h"
#include <cassert>

namespace Container {

using namespace Core;

bool BeanStackUpdateService::onMetaBegin (IMeta *data)
{
        if (data->getAbstract()) {
                return false;
        }

        std::string const &id = data->getId ();
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

bool BeanStackUpdateService::onMetaEnd (IMeta *data)
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
