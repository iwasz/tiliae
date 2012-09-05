/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "IndexedValueService.h"
#include "metaStructure/model/MetaStructure.h"
#include "beanFactory/service/ValueServiceHelper.h"

namespace Container {
using namespace Core;

bool IndexedValueService::onIndexedMetaBegin (MetaObject const *data)
{
        if (!data || data->getAbstract ()) {
                return true;
        }

        inputList = new Core::VariantList ();
        cargList = NULL;

        BeanFactory *beanFactory = getBVFContext ()->getCurrentBF ();
        beanFactory->setInputList (inputList);
        return true;
}

/****************************************************************************/

void IndexedValueService::onConstructorArgsBegin (MetaObject const *data)
{
        if (!data || data->getAbstract ()) {
                return;
        }

        inputList = NULL;
        cargList = new Core::VariantList ();

        BeanFactory *beanFactory = getBVFContext ()->getCurrentBF ();
        beanFactory->setCArgs (cargList);
}

/****************************************************************************/

void IndexedValueService::onConstructorArgsEnd (MetaObject const *)
{
        inputList = NULL;
        cargList = NULL;
}

/****************************************************************************/

void IndexedValueService::onValueData (DataKey const *, ValueData const *data)
{
        Variant ret;

        if (inputList || cargList) {
                ret = helper->create (data->getType (), data->getData ());
        }

        if (inputList) {
                inputList->push_back (ret);
        }
        else if (cargList) {
                cargList->push_back (ret);
        }
}

/****************************************************************************/

void IndexedValueService::onRefData (DataKey const *, RefData const *data)
{
        if (inputList) {
                inputList->push_back (Core::Variant ());
        }
        else if (cargList) {
                cargList->push_back (Core::Variant ());
        }
}

/****************************************************************************/

void IndexedValueService::onNullData (DataKey const *, NullData const *data)
{
        Core::Variant v;
        v.setNull ();

        if (inputList) {
                inputList->push_back (v);
        }
        else if (cargList) {
                cargList->push_back (v);
        }
}

}
