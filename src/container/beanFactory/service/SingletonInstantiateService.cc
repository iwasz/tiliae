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

bool SingletonInstantiateService::onMetaEnd (MetaObject const *meta)
{
        if (!meta || meta->getAbstract ()) {
                return false;
        }

        BeanFactoryStack &stack = getBVFContext ()->getStack();
        BeanFactoryMap *bfMap = getBVFContext ()->getBeanFactoryMap();

        assert (!stack.empty ());
        BeanFactory *beanFactory = getBVFContext ()->getCurrentBF ();
        stack.pop ();

        // Zagnieżdżanie beanów
        MetaMap inner = meta->getInnerMetas ();

        for (MetaMap::iterator i = inner.begin (); i != inner.end (); ++i) {
                MetaObject *meta = i->second;
                BeanFactoryMap::iterator j = bfMap->find (meta->getId ());
                assert (j != bfMap->end ());
                BeanFactory *bf = *j;
                beanFactory->addInnerBeanFactory (bf);
        }

        // Instancjonowanie
        std::string id = toStr (meta->getId ());
        BeanFactoryContext ctx;

        bool isSingleton = (static_cast <MetaObject::Scope> (beanFactory->getIntAttribute (Attributes::SCOPE_ARGUMENT)) == MetaObject::SINGLETON);
        bool isLazyInit = beanFactory->getBoolAttribute (Attributes::LAZYINIT_ARGUMENT);

        if (isSingleton && !isLazyInit) {
                Core::Variant v = beanFactory->create (Core::VariantMap (), &ctx);

                if (v.isNone ()) {
                        throw ContainerException (ctx, "ContainerFactory::fill : error creating singleton [" + id + "].");
                }

//                Kasowanie
//                delete beanFactory;

//                Dodaj do mapy singletonów
        }
//        else {
                bfMap->insert (beanFactory);
//        }

        return true;
}

}
