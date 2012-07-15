/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef REGIONALLOCATOR_H_
#define REGIONALLOCATOR_H_

#include "IAllocator.h"
#include "../../core/ApiMacro.h"

namespace Core {
class RegionAllocatorImpl;

class TILIAE_API RegionAllocator : public IAllocator {
public:
        enum { DEFAULT_SUB_REGION_SIZE = 8192 };

        RegionAllocator (size_t subRegionSize = DEFAULT_SUB_REGION_SIZE);
        virtual ~RegionAllocator();
        void *malloc (size_t size);
        void free (void *p);

private:

        size_t remainingCapacity () const;
        void newSubRegion ();

private:

        RegionAllocatorImpl *impl;
};

} /* namespace Core */
#endif /* REGIONALLOCATOR_H_ */
