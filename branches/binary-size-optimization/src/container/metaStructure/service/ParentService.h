/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PARENTSERVICE_H_
#define PARENTSERVICE_H_

#include "AbstractMetaService.h"
#include "metaStructure/service/DummyService.h"

namespace Container {

class MetaObject;
class IndexedMeta;
class MetaObject;

/**
 * Implementuje obsługę zależnosci dziecko-rodzic. Uzupełnia dzieci danymi z
 * rodziców.
 * \ingroup Container
 */
class ParentService : public DummyMetaService {
public:

        virtual ~ParentService () {}
        virtual bool onMetaBegin (MetaObject *data);

};

}

#	endif /* PARENTSERVICE_H_ */
