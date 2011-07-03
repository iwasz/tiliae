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

bool IndexedValueService::onIndexedMetaBegin (IndexedMeta *data)
{
        if (!data || data->getAbstract ()) {
                return true;
        }

//        currIndexedMeta = data;
        inputList = Ptr <Core::VariantList> (new Core::VariantList ());
        cargList.reset ();

        Ptr <BeanFactory> beanFactory = getBVFContext ()->getCurrentBF ();
        beanFactory->setInput (Core::Variant (inputList));
        return true;
}

/****************************************************************************/

void IndexedValueService::onConstructorArgsBegin (IMeta *data)
{
        if (!data || data->getAbstract ()) {
                return;
        }

        inputList.reset ();
        cargList = Ptr <Core::VariantList> (new Core::VariantList ());

        Ptr <BeanFactory> beanFactory = getBVFContext ()->getCurrentBF ();
        beanFactory->setCArgs (Core::Variant (cargList));
}

/****************************************************************************/

void IndexedValueService::onConstructorArgsEnd (IMeta *data)
{
        currIndexedMeta = NULL;
        currListElem = NULL;
        inputList.reset ();
        cargList.reset ();
}

/****************************************************************************/

void IndexedValueService::onListElem (ListElem *data)
{
        currListElem = data;
}

/****************************************************************************/

void IndexedValueService::onValueData (ValueData *data)
{
        if (/*!currIndexedMeta || */!currListElem) {
                return;
        }

        Variant ret = helper->create (data->getType (), data->getData ());

        if (inputList) {
                inputList->push_back (ret);
        }
        else if (cargList) {
                cargList->push_back (ret);
        }
}

/****************************************************************************/

void IndexedValueService::onRefData (RefData *data)
{
//        if (!currIndexedMeta) {
//                return true;
//        }

        if (inputList) {
                inputList->push_back (Core::Variant ());
        }
        else if (cargList) {
                cargList->push_back (Core::Variant ());
        }
}

/****************************************************************************/

void IndexedValueService::onNullData (NullData *data)
{
        if (/*!currIndexedMeta || */!currListElem) {
                return;
        }

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
