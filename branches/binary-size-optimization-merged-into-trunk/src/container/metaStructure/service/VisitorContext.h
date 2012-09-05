/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef VISITORCONTEXT_H_
#define VISITORCONTEXT_H_

#include "../../../core/ApiMacro.h"

namespace Container {
class MetaContainer;

/**
 * Kontekst dla MetaVisitor-a. Zbiera wspólne informacje dla MetaVisitora, dostępne
 * podczas iteracji.
 * \ingroup Container
 */
class VisitorContext {
public:
        VisitorContext () : container () {}
        virtual ~VisitorContext () {}

        int getDepth () const { return depth; }
        void resetDepth () { depth = 0; }
        void incDepth () { depth++; }
        void decDepth () { depth--; }

        MetaContainer *getMetaContainer () const { return container; }
        void setMetaContainer (MetaContainer *c) { container = c; }

        virtual void reset () { resetDepth (); }

private:

        /// Inner bean level;
        int depth;
        MetaContainer *container;

};

}

#	endif /* VISITORCONTEXT_H_ */
