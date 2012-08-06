/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef METAFACTORY_H_
#define METAFACTORY_H_

#include "allocator/ArrayRegionAllocator.h"
#include "MetaObject.h"
#include "data/ValueData.h"
#include "data/RefData.h"
#include "data/NullData.h"

namespace Container {

class MetaFactory {
public:
        MetaFactory (Core::ArrayRegionAllocator <char> *aloc) : memoryAllocator (aloc) {}

        MetaObject *newMetaObject ();

        ValueData *newValueData ();
        ValueData *newValueData (const char *d);
        ValueData *newValueData (const char *d, const char *t);

        RefData *newRefData ();
        RefData *newRefData (const char *d);

        NullData *newNullData ();

        const char *newString (std::string const &orig);
        const char *newString (const char *orig);

private:

        Core::ArrayRegionAllocator <char> *memoryAllocator;

};

} /* namespace Container */
#endif /* METAFACTORY_H_ */
