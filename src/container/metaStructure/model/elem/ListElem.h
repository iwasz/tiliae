/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LISTELEM_H_
#define LISTELEM_H_

#include <list>
#include <map>
#include "AbstractElem.h"
#include "metaStructure/interface/IDataVisitor.h"
#include "../../../../core/Pointer.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

/**
 * Element listy. Reprezentuje jeden element dla IndexedMeta, czyli jeden element
 * struktury typu lista, czy tabela.
 * \ingroup Container
 */
struct TILIAE_API ListElem : public AbstractElem {

        ListElem () : AbstractElem () {}
        ListElem (Ptr <IData> d, const Core::StringMap &a) : AbstractElem (d, a) {}
        virtual ~ListElem () {}

        static Ptr <ListElem> create (Ptr <IData> d = Ptr <IData> (), const Core::StringMap &a = Core::StringMap ())
        {
                return Ptr <ListElem> (new ListElem (d, a));
        }

        void accept (IElemVisitor *visitor) { visitor->visit (this); }
};

typedef std::list <Ptr <ListElem> > ListElemList;
typedef std::map <std::string, Ptr <ListElem> > ListElemMap;

}

#endif /* LISTELEM_H_ */
