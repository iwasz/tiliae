/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SingletonInstantiateService.h"
#include "container/beanFactory/BeanFactoryContext.h"
#include "container/beanFactory/BeanFactoryContext.h"
#include "container/metaStructure/model/MetaStructure.h"
#include <cassert>

namespace Container {

using namespace Core;

bool SingletonInstantiateService::onMetaEnd (MetaObject const *meta)
{
        if (!meta || meta->getAbstract ()) {
                return false;
        }

        BeanFactoryVisitorContext *bfCtx = getBVFContext ();
        BeanFactoryMap *bfMap = bfCtx->getBeanFactoryMap ();
        BeanFactory *beanFactory = bfCtx->getCurrentBF ();
        BeanFactoryContainer *container = bfCtx->getBeanFactoryContainer ();

        // Zagnieżdżanie beanów
        MetaMap inner = meta->getInnerMetas ();

        for (MetaMap::iterator i = inner.begin (); i != inner.end (); ++i) {
                MetaObject *innerMeta = i->second;

                if (innerMeta->getScope () != MetaObject::BEAN_PROTOTYPE && innerMeta->getScope () != MetaObject::BEAN_SINGLETON) {
                        continue;
                }

                BeanFactory *bf = container->getBeanFactory (innerMeta->getId ());
                assert (bf);
                beanFactory->addInnerBeanFactory (bf);
        }

        // Instancjonowanie
        BeanFactoryContext ctx;

        bool isSingleton = (static_cast<MetaObject::Scope> (beanFactory->getIntAttribute (Attributes::SCOPE_ARGUMENT)) == MetaObject::SINGLETON);
        bool isLazyInit = beanFactory->getBoolAttribute (Attributes::LAZYINIT_ARGUMENT);

        if (isSingleton && !isLazyInit) {
                Core::Variant v = beanFactory->create (Core::VariantMap (), &ctx);

                if (beanFactory->isMarkForDeletion ()) {
                        delete beanFactory;
                }
                else {
                        bfMap->operator[] (beanFactory->getId ()) = beanFactory;
                }

                if (v.isNone ()) {
                        throw ContainerException (ctx, "ContainerFactory::fill : error creating singleton [" + toStr (meta->getId ()) + "].");
                }
        }
        else {
                bfMap->operator[] (beanFactory->getId ()) = beanFactory;
        }

        bfCtx->setCurrentBF (NULL);
        return true;
}
}
