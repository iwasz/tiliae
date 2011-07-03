/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MAPELEM_H_
#define MAPELEM_H_

#include "ListElem.h"
#include <map>
#include <list>
#include "../../../../core/string/String.h"
#include "../../../../core/Pointer.h"
#include "../../../../core/Typedefs.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

/**
 * Element mapy. Reprezentuje jeden element dla MappedMeta, czyli jeden element
 * struktury typu bean, czy mapa.
 * \ingroup Container
 */
class TILIAE_API MapElem : public ListElem {
public:

        MapElem () : ListElem () {}
        MapElem (Ptr <IData> d, const Core::StringMap &a) : ListElem (d, a) {}
        virtual ~MapElem () {}

        static Ptr <MapElem> create (Ptr <IData> d = Ptr <IData> (), const Core::StringMap &a = Core::StringMap ())
        {
                return Ptr <MapElem> (new MapElem (d, a));
        }

        static Ptr <MapElem> create (const std::string &key, Ptr<IData> data, const Core::StringMap &attributes = Core::StringMap ());

/*--------------------------------------------------------------------------*/

        std::string getKey () const { return key; }
        void setKey (const std::string &key) { this->key = key; }

/*--------------------------------------------------------------------------*/

        void accept (IElemVisitor *visitor) { visitor->visit (this); }

private:

        std::string key;
};

typedef std::list <Ptr <MapElem> > MapElemList;
typedef std::map <std::string, Ptr <MapElem> > MapElemMap;

}

#endif /* MAPELEM_H_ */
