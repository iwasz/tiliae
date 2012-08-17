/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SingletonFactoryDeleteService.h"
#include "metaStructure/model/MetaStructure.h"
#include <cassert>

namespace Container {

using namespace Core;

bool SingletonFactoryDeleteService::onMetaBegin (MetaObject *meta)
{
        if (!meta || meta->getAbstract ()) {
                return false;
        }

        BeanFactory *factory = getBVFContext ()->getCurrentBF ();
        assert (factory);

        delete factory;

        return true;
}

}
