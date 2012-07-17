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
        virtual bool onMetaBegin (MetaObject *data) { return true; }
        virtual bool onMetaEnd (MetaObject *data) { return true; }
        virtual bool onMappedMetaBegin (MetaObject *data) { return true; }
        virtual bool onMappedMetaEnd (MetaObject *data) { return true; }
        virtual bool onIndexedMetaBegin (MetaObject *data) { return true; }
        virtual bool onIndexedMetaEnd (MetaObject *data) { return true; }
        virtual void onConstructorArgsBegin (MetaObject *data) {}
        virtual void onConstructorArgsEnd (MetaObject *data) {}
        virtual void onValueData (std::string const &key, ValueData *data) {}
        virtual void onNullData (std::string const &key, NullData *data) {}
        virtual void onRefData (std::string const &key, RefData *data) {}
};

} // nam

#	endif /* DUMMYSERVICE_H_ */
