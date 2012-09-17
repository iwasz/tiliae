/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SingletonInstantiateService.h"
#include "container/metaStructure/model/MetaStructure.h"
#include <cassert>
#include "container/beanFactory/BeanFactoryContext.h"

namespace Container {

using namespace Core;

bool SingletonInstantiateService::onMetaEnd (MetaObject const *meta)
{
        if (!meta || meta->getAbstract ()) {
                return false;
        }

        BeanFactoryVisitorContext *bfCtx = getBVFContext ();
        BeanFactoryMap *bfMap = bfCtx->getBeanFactoryMap();
        BeanFactory *beanFactory = bfCtx->getCurrentBF ();

        // Zagnieżdżanie beanów
        MetaMap inner = meta->getInnerMetas ();

        for (MetaMap::iterator i = inner.begin (); i != inner.end (); ++i) {
                MetaObject *meta = i->second;

                if (meta->getScope () != MetaObject::BEAN) {
                        continue;
                }

                BeanFactoryMap::iterator j = bfMap->find (meta->getId ());
                assert (j != bfMap->end ());
                BeanFactory *bf = j->second;
                beanFactory->addInnerBeanFactory (bf);
        }

        // Instancjonowanie
        BeanFactoryContext ctx;

        bool isSingleton = (static_cast <MetaObject::Scope> (beanFactory->getIntAttribute (Attributes::SCOPE_ARGUMENT)) == MetaObject::SINGLETON);
        bool isLazyInit = beanFactory->getBoolAttribute (Attributes::LAZYINIT_ARGUMENT);

        if (isSingleton && !isLazyInit) {
                Core::Variant v = beanFactory->create (Core::VariantMap (), &ctx);

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
