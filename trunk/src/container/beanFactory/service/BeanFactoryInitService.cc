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

namespace Container {

using namespace Core;

bool BeanFactoryInitService::onMetaBegin (IMeta *meta)
{
        if (!meta || meta->getAbstract ()) {
                return false;
        }

        std::string id = meta->getId ();
        Ptr <BeanFactory> beanFactory = boost::make_shared <BeanFactory> ();
        beanFactory->setBeanWrapper(defaultBeanWrapper);
        beanFactory->setAttributes (meta->getAttributes ());
        getBVFContext ()->getStack().push (beanFactory);
        return true;
}

/****************************************************************************/

bool BeanFactoryInitService::onMetaEnd (IMeta *meta)
{
        if (!meta || meta->getAbstract ()) {
                return false;
        }

        BeanFactoryStack &stack = getBVFContext ()->getStack();

        assert (!stack.empty ());
        Ptr <BeanFactory> beanFactory = getBVFContext ()->getCurrentBF ();
        stack.pop ();

        if (stack.empty ()) {
                getBVFContext ()->getBeanFactoryMap()->insert (beanFactory);
        }
        else {
                Ptr <BeanFactory> parent = getBVFContext ()->getCurrentBF ();
                parent->addInnerBeanFactory (beanFactory);
        }

        return true;
}

}
