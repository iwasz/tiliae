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

        virtual bool onMappedMetaBegin (MetaObject *data);
        virtual void onConstructorArgsBegin (MetaObject *data);
        virtual void onConstructorArgsEnd (MetaObject *data);
        virtual void onValueData (std::string const &key, ValueData *data);
        virtual void onRefData (std::string const &key, RefData *data);
        virtual void onNullData (std::string const &key, NullData *data);

/*--------------------------------------------------------------------------*/

        void setValueServiceHelper (ValueServiceHelper *valueService) { this->helper = valueService; }

private:

        Common::OrderedVariantMap *inputMap;
        ValueServiceHelper *helper;
        MetaObject *currMappedMeta;
};

}

#	endif /* MAPPEDVALUESERVICE_H_ */
