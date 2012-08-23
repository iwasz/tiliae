/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <LazyFactory.h>
#include <boost/make_shared.hpp>
#include "FactoryService.h"
#include "metaStructure/model/MetaStructure.h"
#include "Defs.h"
#include "../../../core/variant/Cast.h"
#include "../../../factory/IFactory.h"
#include "../../../factory/LazyFactory.h"
#include "../../../core/StrUtil.h"

namespace Container {
using namespace Core;

/**
 * BeanFactory ma wśrodku factory, które faktycznie tworzy pusty obiekt i domyślnie jest
 * to ReflectionFactory, oraz ma także edytor, który taki nowoutwoprzony obiekt wypełnia
 * danymi. W tej metodzie jest podejmowana decyzja, czy ta wewnętrzna fabryczka to ma być
 * domyślny ReflectionFactory, czy może customowa fabryka i to zależy od atrybutu "factory".
 * Jeśli ten atrybut jest ustawiony, to za pomocą BeanFactoryContainer::getBeanFactory jest
 * pobierana fabryka o podanym w atrybucie ID i ustawiana do BeanFactory.
 */
bool FactoryService::onMetaBegin (MetaObject const *data)
{
        // Tu powinien być beanFactory odpowiadający podanemu meta w parametrze.
        BeanFactory *beanFactory = getBVFContext ()->getCurrentBF ();

        if (!beanFactory) {
                // Gdy abstract
                return false;
        }

        std::string customFactoryName = toStr (data->getFactory ());
        Factory::IFactory *factory = NULL;

        if (!customFactoryName.empty ()) {
                BeanFactoryContainer *container = getBVFContext ()->getBeanFactoryContainer ();
                factory = ocast <Factory::IFactory *> (container->getSingleton (customFactoryName.c_str ()));
                beanFactory->setFactory (factory, false);
        }
        else {
                factory = defaultSingletonFactory;
                beanFactory->setFactory (factory, false);
        }

        if (!factory) {
                throw BeanNotFullyInitializedException ("Can't create factory BeanFactory. Bean id : (" + toStr (data->getId ()) + "), factory name : (" + customFactoryName + ").");
        }

        return true;
}

}
