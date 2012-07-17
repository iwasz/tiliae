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

        virtual bool onIndexedMetaBegin (MetaObject *data);
        virtual void onConstructorArgsBegin (MetaObject *data);
        virtual void onConstructorArgsEnd (MetaObject *data);
        virtual void onValueData (std::string const &key, ValueData *data);
        virtual void onRefData (std::string const &key, RefData *data);
        virtual void onNullData (std::string const &key, NullData *data);

/*--------------------------------------------------------------------------*/

        void setValueServiceHelper (ValueServiceHelper *valueService) { this->helper = valueService; }

private:

        Core::VariantList *inputList;
        Core::VariantList *cargList;
        ValueServiceHelper *helper;

};

}

#	endif /* INDEXEDVALUESERVICE_H_ */
