/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef INDEXEDMETA_H_
#define INDEXEDMETA_H_

#include "AbstractMeta.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

/**
 * Odzwierciedla takie struktury jak lista, wektor, set etc.
 * Ta klasa nie zawiera zbyt wiele, poniewaz wiekszosc jej
 * dzialan jest wyrzucona do visitorów.
 * \ingroup Container
 */
class TILIAE_API IndexedMeta : public AbstractMeta {
public:

        virtual ~IndexedMeta () {}

        Type getType () const { return INDEXED; }

        ListElemList getFields () const;
        void setFields (const ListElemList &fields) { this->fields = fields; }
        void addFields (const ListElemList &fields);
        void addField (Ptr <ListElem> field) { this->fields.push_back (field); }

        void accept (IMetaVisitor *visitor) { visitor->visit (this); }

private:

        ListElemList fields;
};

}

#endif /* INDEXEDMETA_H_ */
