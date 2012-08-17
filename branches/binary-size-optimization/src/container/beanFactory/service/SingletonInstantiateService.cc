/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SingletonInstantiateService.h"
#include "metaStructure/model/MetaStructure.h"
#include <cassert>
#include "../BeanFactoryContext.h"

namespace Container {

using namespace Core;

bool SingletonInstantiateService::onMetaEnd (MetaObject *meta)
{
        if (!meta || meta->getAbstract ()) {
                return false;
        }

        BeanFactoryStack &stack = getBVFContext ()->getStack();

        assert (!stack.empty ());
        BeanFactory *beanFactory = getBVFContext ()->getCurrentBF ();
        stack.pop ();

//        if (stack.empty ()) {
                getBVFContext ()->getBeanFactoryMap()->insert (beanFactory);
//        }
//        else {
//                BeanFactory *parent = getBVFContext ()->getCurrentBF ();
//                parent->addInnerBeanFactory (beanFactory);
//        }

        std::string id = toStr (meta->getId ());
        BeanFactoryContext ctx;

        bool isSingleton = (static_cast <MetaObject::Scope> (beanFactory->getIntAttribute (Attributes::SCOPE_ARGUMENT)) == MetaObject::SINGLETON);
        bool isLazyInit = beanFactory->getBoolAttribute (Attributes::LAZYINIT_ARGUMENT);

        if (isSingleton && !isLazyInit) {
                Core::Variant v = beanFactory->create (Core::VariantMap (), &ctx);

                if (v.isNone ()) {
                        throw ContainerException (ctx, "ContainerFactory::fill : error creating singleton [" + id + "].");
                }
        }

        return true;
}

}
