/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MappedValueService.h"
#include "container/metaStructure/model/MetaStructure.h"
#include "container/beanFactory/service/ValueServiceHelper.h"
#include "common/collection/OrderedVariantMap.h"
#include <boost/make_shared.hpp>
#include "core/StrUtil.h"

namespace Container {
using namespace Core;

bool MappedValueService::onMappedMetaBegin (MetaObject const *data)
{
        if (!data || data->getAbstract ()) {
                return true;
        }

        BeanFactory *beanFactory = getBVFContext ()->getCurrentBF ();
        inputMap = new Common::OrderedVariantMap ();
        currMappedMeta = data;
        beanFactory->setInputMap (inputMap);
        return true;
}

/****************************************************************************/

void MappedValueService::onConstructorArgsBegin (MetaObject const *)
{
        currMappedMeta = NULL;
}

/****************************************************************************/

void MappedValueService::onConstructorArgsEnd (MetaObject const *)
{
        currMappedMeta = NULL;
        inputMap = NULL;
}

/****************************************************************************/

void MappedValueService::onValueData (DataKey const *dk, ValueData const *data)
{
        if (!currMappedMeta) {
                return;
        }

        Variant ret = helper->create (data->getType (), data->getData ());
        inputMap->set (currMappedMeta->resolveAlias (toStr (dk->key)), ret);
}

/****************************************************************************/

void MappedValueService::onRefData (DataKey const *dk, RefData const *data)
{
        if (!currMappedMeta) {
                return;
        }

        inputMap->set (currMappedMeta->resolveAlias (toStr (dk->key)), Core::Variant ());
}

/****************************************************************************/

void MappedValueService::onNullData (DataKey const *dk, NullData const *data)
{
        if (!currMappedMeta) {
                return;
        }

        Core::Variant v;
        v.setNull ();

        inputMap->set (currMappedMeta->resolveAlias (toStr (dk->key)), v);
}

}
