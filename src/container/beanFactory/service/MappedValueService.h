/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MAPPEDVALUESERVICE_H_
#define MAPPEDVALUESERVICE_H_

#include "beanFactory/service/BeanFactoryService.h"

namespace Common {
class OrderedVariantMap;
}

namespace Container {
class ValueServiceHelper;
class IndexedMeta;
class MetaObject;
class ListElem;
class ValueData;
class RefData;

/**
 * Tworzy i ustawia inputMap.
 * \ingroup Container
 */
class MappedValueService : public BeanFactoryService {
public:

        MappedValueService () : inputMap (NULL), helper (NULL), currMappedMeta (NULL) {}
        virtual ~MappedValueService () {}

/*--------------------------------------------------------------------------*/

        virtual bool onMappedMetaBegin (MetaObject const *data);
        virtual void onConstructorArgsBegin (MetaObject const *data);
        virtual void onConstructorArgsEnd (MetaObject const *data);
        virtual void onValueData (DataKey const *dk, ValueData const *data);
        virtual void onRefData (DataKey const *dk, RefData const *data);
        virtual void onNullData (DataKey const *dk, NullData const *data);

/*--------------------------------------------------------------------------*/

        void setValueServiceHelper (ValueServiceHelper *valueService) { this->helper = valueService; }

private:

        Common::OrderedVariantMap *inputMap;
        ValueServiceHelper *helper;
        MetaObject const *currMappedMeta;
};

}

#	endif /* MAPPEDVALUESERVICE_H_ */
