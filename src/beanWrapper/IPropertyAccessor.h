/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ISERVICEREPOSITORY_822081_H
#define ISERVICEREPOSITORY_822081_H

#include "../core/string/String.h"
#include "../core/variant/Variant.h"
#include "../core/ApiMacro.h"
#include "../common/Context.h"
#include "../core/Object.h"

namespace Wrapper {

/**
 * Interfejs klas, które pozwalają na dostęp do obiektów
 * poprzez ich ,,właściwości'' (properties). Właściwości
 * to pary ścieżka -> obiekt. Ścieżki skłądają się z
 * segmentów, a obiekty mogą być dowolnymi obiektami, które
 * da się przekazać przez Core::Variant.
 */
class TILIAE_API IPropertyAccessor : public Core::Object {
public:

        virtual ~IPropertyAccessor () {}

        /**
         * To jest metoda set, ale przyjmuje argument w postaci ścieżki std::string.
         * Ścieżki takie skladają sie z segmentow. Segment moze byc:
         * - Stringiem wskazujacym na jakies property beana, czy element mapy, czy innego obiektu.
         * - Indeksem listy.
         */
        virtual void set (Core::Variant *bean, const std::string &path, const Core::Variant &object, Common::Context *ctx = NULL) = 0;

        /**
         * Dodawanie elementów do kolekcji sekwencyjnych takich jak lista, czy wektor.
         */
        virtual void add (Core::Variant *bean, const std::string &path, const Core::Variant &object, Common::Context *ctx = NULL) = 0;

        /**
         * Metoda pobierająca element z BeanWrapper. Zwraca
         * Variant o typie NONE, kiedy nie udalo sie pobrac
         * elementu z danej ścieżki (to dotyczy też ścieżki "").
         * W przeciwnym wypdaku get (...).isNone () == false.
         */
        virtual Core::Variant get (const Core::Variant *bean, const std::string &path, Common::Context *ctx = NULL) const = 0;

};

} // namespace

#endif

