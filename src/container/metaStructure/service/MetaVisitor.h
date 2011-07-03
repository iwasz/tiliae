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

#include "metaStructure/interface/IMetaService.h"
#include "metaStructure/model/MetaStructure.h"
#include "metaStructure/interface/IDataVisitor.h"


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
                public IElemVisitor,
                public IDataVisitor {
public:

        MetaVisitor () : ctx (NULL) {}
        virtual ~MetaVisitor () {}

        /// Zwraca nowy obiekt klasy MetaVisitor.
        static Ptr <MetaVisitor> create () { return Ptr <MetaVisitor> (new MetaVisitor); }

/*--------------------------------------------------------------------------*/

        void visit (MetaContainer *data);

        void visit (MappedMeta *data);
        void visit (IndexedMeta *data);

        void visit (ListElem *data);
        void visit (MapElem *data);

        void visit (ValueData *data);
        void visit (NullData *data);
        void visit (RefData *data);
        void visit (IdRefData *data);

        void reset ();

/*--------------------------------------------------------------------------*/

        void addService (Ptr <IMetaService> s) { services.push_back (s); }
        void clearServices () { services.clear (); }

/*--------------------------------------------------------------------------*/

        void setContext (VisitorContext *c) { ctx = c; }
        VisitorContext *getContext () const { return ctx; }

private:

        void visitInnerMeta (AbstractMeta *data);

private:

        MetaServiceList services;
        VisitorContext *ctx;
};

}

#	endif /* METAVISITOR_H_ */
