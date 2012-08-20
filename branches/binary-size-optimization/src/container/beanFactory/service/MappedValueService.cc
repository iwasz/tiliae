/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MappedValueService.h"
#include "metaStructure/model/MetaStructure.h"
#include "beanFactory/service/ValueServiceHelper.h"
#include "../../../common/collection/OrderedVariantMap.h"
#include <boost/make_shared.hpp>

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

void MappedValueService::onValueData (std::string const &key, ValueData const *data)
{
        if (!currMappedMeta) {
                return;
        }

        Variant ret = helper->create (data->getType (), data->getData ());
        inputMap->set (key, ret);
}

/****************************************************************************/

void MappedValueService::onRefData (std::string const &key, RefData const *data)
{
        if (!currMappedMeta) {
                return;
        }

        inputMap->set (key, Core::Variant ());
}

/****************************************************************************/

void MappedValueService::onNullData (std::string const &key, NullData const *data)
{
        if (!currMappedMeta) {
                return;
        }

        Core::Variant v;
        v.setNull ();

        inputMap->set (key, v);
}

}
