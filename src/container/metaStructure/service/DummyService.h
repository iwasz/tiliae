/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DUMMYSERVICE_H_
#define DUMMYSERVICE_H_

#include "AbstractMetaService.h"

namespace Container {

/**
 * Prosta implementacja IMetaService. Ta implementacja nie robi nic, ale jest
 * kokrentną klasą, ktorej obiekty można instancjonować. Jest pomyślana jako
 * baza dla innych serwisów, które nie poytrzebują implementować wszystkich
 * metod-handlerów. Jeśli by jej nie było, każdy kokretny serwis musiałby
 * implementować takie puste metody ja poniżej.
 * \ingroup Container
 */
struct DummyMetaService : public AbstractMetaService {
        virtual ~DummyMetaService () {}

        virtual void onContainer (MetaContainer *data) {}
        virtual bool onMetaBegin (IMeta *data) { return true; }
        virtual bool onMetaEnd (IMeta *data) { return true; }
        virtual bool onMappedMetaBegin (MappedMeta *data) { return true; }
        virtual bool onMappedMetaEnd (MappedMeta *data) { return true; }
        virtual bool onIndexedMetaBegin (IndexedMeta *data) { return true; }
        virtual bool onIndexedMetaEnd (IndexedMeta *data) { return true; }
        virtual void onConstructorArgsBegin (IMeta *data) {}
        virtual void onConstructorArgsEnd (IMeta *data) {}
        virtual void onListElem (ListElem *data) {}
        virtual void onMapElem (MapElem *data) {}
        virtual void onValueData (ValueData *data) {}
        virtual void onNullData (NullData *data) {}
        virtual void onRefData (RefData *data) {}
//        virtual void onIdRefData (IdRefData *data) {}
};

} // nam

#	endif /* DUMMYSERVICE_H_ */
