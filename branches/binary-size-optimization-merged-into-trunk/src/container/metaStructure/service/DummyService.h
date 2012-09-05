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

        virtual void onContainer (MetaContainer const *data) {}
        virtual bool onMetaBegin (MetaObject const *data) { return true; }
        virtual bool onMetaEnd (MetaObject const *data) { return true; }
        virtual bool onMappedMetaBegin (MetaObject const *data) { return true; }
        virtual bool onMappedMetaEnd (MetaObject const *data) { return true; }
        virtual bool onIndexedMetaBegin (MetaObject const *data) { return true; }
        virtual bool onIndexedMetaEnd (MetaObject const *data) { return true; }
        virtual void onConstructorArgsBegin (MetaObject const *data) {}
        virtual void onConstructorArgsEnd (MetaObject const *data) {}
        virtual void onValueData (DataKey const *dk, ValueData const *data) {}
        virtual void onNullData (DataKey const *dk, NullData const *data) {}
        virtual void onRefData (DataKey const *dk, RefData const *data) {}
};

} // nam

#	endif /* DUMMYSERVICE_H_ */
