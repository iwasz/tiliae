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
class IMeta;
class ListElem;
class ValueData;
class RefData;

/**
 * Tworzy i ustawia inputMap.
 * \ingroup Container
 */
class MappedValueService : public BeanFactoryService {
public:

        MappedValueService () : inputMap (NULL), currMappedMeta (NULL), currMapElem (NULL) {}
        virtual ~MappedValueService () {}
        static Ptr <MappedValueService> create () { return Ptr <MappedValueService> (new MappedValueService); }

/*--------------------------------------------------------------------------*/

        virtual bool onMappedMetaBegin (MappedMeta *data);
        virtual void onConstructorArgsEnd (IMeta *data);
        virtual void onMapElem (MapElem *data);
        virtual void onValueData (ValueData *data);
        virtual void onRefData (RefData *data);
        virtual void onNullData (NullData *data);

/*--------------------------------------------------------------------------*/

        Ptr<ValueServiceHelper> getValueServiceHelper () const { return helper; }
        void setValueServiceHelper (Ptr<ValueServiceHelper> valueService) { this->helper = valueService; }

private:

        Common::OrderedVariantMap *inputMap;
        Ptr<ValueServiceHelper> helper;

        MappedMeta *currMappedMeta;
        MapElem *currMapElem;

};

}

#	endif /* MAPPEDVALUESERVICE_H_ */
