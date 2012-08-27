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
class MetaObject;
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

        IndexedValueService () : inputList (NULL), cargList (NULL), helper (NULL) {}
        virtual ~IndexedValueService () {}

/*--------------------------------------------------------------------------*/

        virtual bool onIndexedMetaBegin (MetaObject const *data);
        virtual void onConstructorArgsBegin (MetaObject const *data);
        virtual void onConstructorArgsEnd (MetaObject const *data);
        virtual void onValueData (DataKey const *dk, ValueData const *data);
        virtual void onRefData (DataKey const *dk, RefData const *data);
        virtual void onNullData (DataKey const *dk, NullData const *data);

/*--------------------------------------------------------------------------*/

        void setValueServiceHelper (ValueServiceHelper *valueService) { this->helper = valueService; }

private:

        Core::VariantList *inputList;
        Core::VariantList *cargList;
        ValueServiceHelper *helper;

};

}

#	endif /* INDEXEDVALUESERVICE_H_ */
