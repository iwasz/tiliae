/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef METACONTAINER_H_
#define METACONTAINER_H_

#include "metaStructure/model/meta/IMeta.h"
#include "metaStructure/interface/IDataVisitor.h"
#include "../../../core/ApiMacro.h"

namespace Container {

/**
 * Główna kolekcja obiektów metastruktury. Zazwyczaj użytkownik stworzy jedną taką
 * a potem wypełni ją obiektami takimi jak MappedMeta, IndexedMeta etc.
 * \ingroup Container
 */
class TILIAE_API MetaContainer {
public:

        static Ptr <MetaContainer> create () { return Ptr <MetaContainer> (new MetaContainer ()); }

        Ptr <IMeta> get (const std::string &key) const;

        /**
         * Zdecydowałem sie na taki interfejs poniewaz kazdy
         * dodawany IMeta powinien miec ustawione ID. To, ze
         * mozna tworzyc beany w XMLu bez podawania ID, to jest
         * tylko i wyłącznie specyfika XML. Metastruktura jest
         * ponad tym.
         * TODO Wyjątek, jesli Meta o danym ID juz istnieje -
         * w tym miejscu, czyli najwczesniej!
         */
        void add (Ptr <IMeta> val);

        void accept (IContainerVisitor *visitor) { visitor->visit (this); }

        /**
         * Pobiera wskaźnik do mapy obiektów Meta. Uwaga, ta mapa
         * nie jest alokowana dynamicznie.
         */
        const MetaMap &getMetaMap () const { return metaMap; }

        Ptr <MetaContainer const> getLinked () const { return linked; }
        void setLinked (Ptr <MetaContainer const> l) { linked = l; }

private:

        MetaMap metaMap;
        Ptr <MetaContainer const> linked;
};

}

#endif /* METACONTAINER_H_ */
