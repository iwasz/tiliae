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

bool MappedValueService::onMappedMetaBegin (MappedMeta *data)
{
        if (!data || data->getAbstract ()) {
                return true;
        }

        Ptr <BeanFactory> beanFactory = getBVFContext ()->getCurrentBF ();
        inputMap = boost::make_shared <Common::OrderedVariantMap> ();
        currMappedMeta = data;
        beanFactory->setInput (Core::Variant (inputMap));
        return true;
}

/****************************************************************************/

void MappedValueService::onMapElem (MapElem *data)
{
        currMapElem = data;
}

/****************************************************************************/

void MappedValueService::onConstructorArgsEnd (IMeta *data)
{
        currMappedMeta = NULL;
        currMapElem = NULL;
        inputMap.reset ();
}

/****************************************************************************/

void MappedValueService::onValueData (ValueData *data)
{
        if (!currMappedMeta || !currMapElem) {
                return;
        }

        Variant ret = helper->create (data->getType (), data->getData ());
        inputMap->set (currMapElem->getKey (), ret);
}

/****************************************************************************/

void MappedValueService::onRefData (RefData *data)
{
        if (!currMappedMeta || !currMapElem) {
                return;
        }

        inputMap->set (currMapElem->getKey (), Core::Variant ());
}

/****************************************************************************/

void MappedValueService::onNullData (NullData *data)
{
        if (!currMappedMeta || !currMapElem) {
                return;
        }

        Core::Variant v;
        v.setNull ();

        inputMap->set (currMapElem->getKey (), v);
}

}
