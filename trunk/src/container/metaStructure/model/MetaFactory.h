/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef METAFACTORY_H_
#define METAFACTORY_H_

#include "core/allocator/ArrayRegionAllocator.h"
#include "MetaObject.h"
#include "data/ValueData.h"
#include "data/RefData.h"
#include "data/NullData.h"
#include "core/ApiMacro.h"

namespace Container {

class TILIAE_API MetaFactory {
public:
        MetaFactory (Core::ArrayRegionAllocator <char> *aloc) : memoryAllocator (aloc) {}

        MetaObject *newMetaObject ();

        DataKey *newDataKey ();
        DataKey *newDataKey (IData *d);
        DataKey *newDataKey (const char *k, IData *d);
        DataKey *newDataKeyNewString (const char *k, IData *d) { return newDataKey (newString (k), d); }

        ValueData *newValueData ();
        ValueData *newValueData (const char *d);
        ValueData *newValueDataNewString (const char *d) { return newValueData (newString (d)); }
        ValueData *newValueData (const char *d, const char *t);
        ValueData *newValueDataNewString (const char *d, const char *t) { return newValueData (newString (d), newString (t)); }

        RefData *newRefData ();
        RefData *newRefData (const char *d);
        RefData *newRefDataNewString (const char *d) { return newRefData (newString (d)); }

        NullData *newNullData ();

        const char *newString (std::string const &orig);
        const char *newString (const char *orig);

private:

        Core::ArrayRegionAllocator <char> *memoryAllocator;

};

} /* namespace Container */
#endif /* METAFACTORY_H_ */
