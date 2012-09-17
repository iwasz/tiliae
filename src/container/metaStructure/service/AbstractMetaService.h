/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTMETASERVICE_H_
#define ABSTRACTMETASERVICE_H_

#include "container/metaStructure/interface/IMetaService.h"
#include "container/metaStructure/service/VisitorContext.h"

namespace Container {

/**
 * Szkielet Meta-serwisu - implementuje wspólne metody.
 * \ingroup Container
 */
struct AbstractMetaService : public IMetaService {
        AbstractMetaService () : ctx (NULL) {}
        virtual ~AbstractMetaService () {}

        virtual void setContext (VisitorContext *c) { ctx = c; }
        virtual VisitorContext *getContext () const { return ctx; }

private:
        VisitorContext *ctx;
};

}

#	endif /* ABSTRACTMETASERVICE_H_ */
