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

class MappedMeta;
class IndexedMeta;
class IMeta;

/**
 * Implementuje obsługę zależnosci dziecko-rodzic. Uzupełnia dzieci danymi z
 * rodziców.
 * \ingroup Container
 */
class ParentService : public DummyMetaService {
public:

        virtual ~ParentService () {}
        static Ptr <ParentService> create () { return Ptr <ParentService> (new ParentService); }

        virtual bool onMetaBegin (IMeta *data);

};

}

#	endif /* PARENTSERVICE_H_ */
