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

bool MappedValueService::onMappedMetaBegin (MetaObject *data)
{
        if (!data || data->getAbstract ()) {
                return true;
        }

        Ptr <BeanFactory> beanFactory = getBVFContext ()->getCurrentBF ();
        inputMap = new Common::OrderedVariantMap ();
        currMappedMeta = data;
        beanFactory->setInputMap (inputMap);
        return true;
}

/****************************************************************************/

void MappedValueService::onConstructorArgsBegin (MetaObject *)
{
        currMappedMeta = NULL;
}

/****************************************************************************/

void MappedValueService::onConstructorArgsEnd (MetaObject *)
{
        currMappedMeta = NULL;
        inputMap = NULL;
}

/****************************************************************************/

void MappedValueService::onValueData (std::string const &key, ValueData *data)
{
        if (!currMappedMeta) {
                return;
        }

        Variant ret = helper->create (data->getType (), data->getData ());
        inputMap->set (key, ret);
}

/****************************************************************************/

void MappedValueService::onRefData (std::string const &key, RefData *data)
{
        if (!currMappedMeta) {
                return;
        }

        inputMap->set (key, Core::Variant ());
}

/****************************************************************************/

void MappedValueService::onNullData (std::string const &key, NullData *data)
{
        if (!currMappedMeta) {
                return;
        }

        Core::Variant v;
        v.setNull ();

        inputMap->set (key, v);
}

}
