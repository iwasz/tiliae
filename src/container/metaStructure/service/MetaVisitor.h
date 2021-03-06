/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef METAVISITOR_H_
#define METAVISITOR_H_

#include <list>

#include "container/metaStructure/interface/IMetaService.h"
#include "container/metaStructure/model/MetaStructure.h"
#include "container/metaStructure/interface/IDataVisitor.h"


namespace Container {

/**
 * Iteruje przez całą strukturę. Głowna pozwalająca na iterowanie przez całą meta-
 * strukturę. Ma listę serwisów (klas kokretnych typu IMetaService), których metody
 * są wywoływane w odpowiednich miejscach. Na przykłąd gdy  MetaVisitor iterując natrafia
 * na obiekt typu IndexedMeta, wywołuje metody onIndexedMeta wszystkich swoich serwisów.
 * \ingroup Container
 */
class MetaVisitor : public IContainerVisitor,
                public IMetaVisitor,
                public IDataVisitor {
public:

        MetaVisitor () : ctx (NULL) {}
        virtual ~MetaVisitor () {}

/*--------------------------------------------------------------------------*/

        void visit (MetaContainer *data);
        void visit (MetaDeque *data);

        void visit (MetaObject const *data);

        void visit (DataKey const *dk, ValueData *data);
        void visit (DataKey const *dk, NullData *data);
        void visit (DataKey const *dk, RefData *data);

        void reset ();

/*--------------------------------------------------------------------------*/

        void addService (IMetaService *s) { services.push_back (s); }
        void clearServices () { services.clear (); }

/*--------------------------------------------------------------------------*/

        void setContext (VisitorContext *c) { ctx = c; }
        VisitorContext *getContext () const { return ctx; }

private:

        MetaServiceVector services;
        VisitorContext *ctx;
};

}

#	endif /* METAVISITOR_H_ */
