/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef INDEXEDVALUESERVICE_H_
#define INDEXEDVALUESERVICE_H_

#include "beanFactory/service/BeanFactoryService.h"

namespace Container {
class IndexedMeta;
class IMeta;
class ListElem;
class ValueData;
class RefData;
class NullData;
class ValueServiceHelper;

/**
 * Tworzy i ustawia inputMap.
 * \ingroup Container
 */
class IndexedValueService : public BeanFactoryService {
public:

        IndexedValueService () : currIndexedMeta (NULL), currListElem (NULL) {}
        virtual ~IndexedValueService () {}
        static Ptr <IndexedValueService> create () { return Ptr <IndexedValueService> (new IndexedValueService); }

/*--------------------------------------------------------------------------*/

        virtual bool onIndexedMetaBegin (IndexedMeta *data);
        virtual void onConstructorArgsBegin (IMeta *data);
        virtual void onConstructorArgsEnd (IMeta *data);
        virtual void onListElem (ListElem *data);
        virtual void onValueData (ValueData *data);
        virtual void onRefData (RefData *data);
        virtual void onNullData (NullData *data);

/*--------------------------------------------------------------------------*/

        Ptr<ValueServiceHelper> getValueServiceHelper () const { return helper; }
        void setValueServiceHelper (Ptr<ValueServiceHelper> valueService) { this->helper = valueService; }

private:

        Ptr <Core::VariantList> inputList;
        Ptr <Core::VariantList> cargList;

        Ptr<ValueServiceHelper> helper;

        IndexedMeta *currIndexedMeta;
        ListElem *currListElem;

};

}

#	endif /* INDEXEDVALUESERVICE_H_ */
