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
#include "../../../core/allocator/ArrayRegionAllocator.h"

namespace Factory {
class IFactory;
}

namespace Container {

extern const char *EDITOR_SPECIAL_CHAR;

/**
 * Serwis pracujący z metastrukturą. Tworzy skalary.
 */
class ValueServiceHelper {
public:

        ValueServiceHelper () : defaultValueFactory (NULL), classArgs (1) {}

        /**
         * Metod tworząca skalary. Szuka edytorów w singletonMap.
         * Do nazwy edytora dorzucany jest znak &, czyli w mapie
         * singletonów potrzebny jest &text, &bool etc.
         */
        Core::Variant create (const char *type, const char *value) const;
        void setDefaultValueFactory (Factory::IFactory* defaultValueFactory) { this->defaultValueFactory = defaultValueFactory; }

private:

        Factory::IFactory *defaultValueFactory;
        mutable Core::VariantMap params;
        mutable Core::VariantVector classArgs;

};

}

#endif /* VALUESERVICE_H_ */
