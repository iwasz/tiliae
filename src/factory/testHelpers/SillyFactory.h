/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SILLYFACTORY_H_
#define SILLYFACTORY_H_

#include "IFactory.h"
#include "../core/variant/Variant.h"
#include "../core/Typedefs.h"

namespace Factory {

/**
 * Bardzo prosta i uzyteczna fabryka. Ustawiamy jej jakis obiekt,
 * a ona (korzystajac ze zwyklego przypisania operator=) kopiuje
 * ten obiekt. Jedyny warunek jaki jest stawiany przed obiektem
 * original, to to, zeby dalo sie go skopiowac (czyli musi byc
 * wariant value).
 * Poniewaz warianty zwracane przez ta fabryke zawsze sa kopiowane,
 * i nie ma mozliwosci produkowania obiektow, a potem zwracania ich
 * w postaci wariant-uchwytów, to ta fabryka nadaje sie glownie
 * do produkowania malych obiektow jak int, String, pusta lista
 * etc.
 * *Uwaga* ta fabryka produkuje tylko warianty-wartości, wiec ma
 * ograniczone zastosowanie. Jesli pobieramy wskaznik do takiego
 * obiektu, to trzeba miec na uwadze, ze moze on zniknac (bo to
 * sa obiekty automatyczne lub tyczasowe najczesciej). Na przyklad:
 * {
 *      Variant v = Core::Variant (String ("a"));
 *      obj.setPtrStrProp (vcast <String *> (v));
 * }
 * // Teraz obj.ptrStrProp wskazuje w kosmos.
 */
class TILIAE_API SillyFactory : public IFactory {
public:

        SillyFactory () {}
        SillyFactory (const Core::Variant &orig) : original (orig) {}
        virtual ~SillyFactory () {}

        virtual Core::Variant create (const Core::VariantMap &parameters = Core::VariantMap (), Core::Context *context = NULL) const
        {
                return original;
        }

        Core::Variant getOriginal() const { return original; }
        void setOriginal (const Core::Variant &original);

private:

        Core::Variant original;

};

}

#endif /* SILLYFACTORY_H_ */
