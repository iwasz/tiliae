/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef VALUESERVICE_HELPER_H_
#define VALUESERVICE_HELPER_H_

#include "../../../core/Pointer.h"
#include "../../../core/variant/Variant.h"
#include "../../../core/Typedefs.h"
#include "../../../core/string/String.h"

namespace Container {

extern const char *EDITOR_SPECIAL_CHAR;

/**
 * Serwis pracujący z metastrukturą. Tworzy skalary.
 */
class ValueServiceHelper {
public:

        ValueServiceHelper () : classArgs (1) {}
        static Ptr <ValueServiceHelper> create () { return Ptr <ValueServiceHelper> (new ValueServiceHelper); }

        /**
         * Metod tworząca skalary. Szuka edytorów w singletonMap.
         * Do nazwy edytora dorzucany jest znak &, czyli w mapie
         * singletonów potrzebny jest &text, &bool etc.
         */
        Core::Variant create (const std::string &type, const std::string &value) const;

        /**
         * Singleton map, to mapa w której ten serwis będzie szukał
         * edytorów do tworzenia wartości skalarnych ze stringów.
         * Taki interfejs jest dlatego, że tworząc skalar można podać
         * dowolny typ (nie tylko wbudowany) i jeżeli tylko znajdzie
         * się edytor o odpowiedniej nazwie, to zostanie zastosowany.
         */
        Ptr <Core::VariantMap> getSingletonMap () const { return singletonMap; }
        void setSingletonMap (Ptr <Core::VariantMap> singletonMap) { this->singletonMap = singletonMap; }

private:

        Ptr <Core::VariantMap> singletonMap;
        mutable Core::VariantMap params;
        mutable Core::VariantVector classArgs;

};

}

#endif /* VALUESERVICE_H_ */
