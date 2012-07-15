/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "RegionAllocator.h"
#include <list>
#include <cstdlib>

namespace Core {

struct RegionAllocatorImpl {

        RegionAllocatorImpl (size_t s) : currentSubRegion (NULL), freeSpace (NULL), subRegionSize (s) {}

        std::list <void *> subRegions;
        void *currentSubRegion;
        void *freeSpace;
        size_t subRegionSize;
};

/****************************************************************************/

RegionAllocator::RegionAllocator (size_t subRegionSize) : impl (new RegionAllocatorImpl (subRegionSize))
{
}

/****************************************************************************/

RegionAllocator::~RegionAllocator ()
{
        for (std::list <void *>::iterator i = impl->subRegions.begin (); i != impl->subRegions.end (); ++i) {
                ::free (*i);
        }

        delete impl;
}

/****************************************************************************/

void *RegionAllocator::malloc (size_t size)
{
        if (size > impl->subRegionSize) {
                throw AllocationException ("RegionAllocator::malloc : requested memory size is bigger than subregion size.");
        }

        if (impl->subRegions.empty () || size > remainingCapacity ()) {
                newSubRegion ();
        }

        void *ret = impl->freeSpace;
        impl->freeSpace = (char *)impl->freeSpace + size;
        return ret;
}

/****************************************************************************/

void RegionAllocator::free (void *p) {}

/****************************************************************************/

size_t RegionAllocator::remainingCapacity () const
{
        char *b = (char *)impl->currentSubRegion;
        char *e = (char *)impl->freeSpace;
        return impl->subRegionSize - (b - e);
}

/****************************************************************************/

void RegionAllocator::newSubRegion ()
{
        void *p = ::malloc (impl->subRegionSize);
        impl->subRegions.push_back (p);
        impl->currentSubRegion = p;
        impl->freeSpace = p;
}

} /* namespace Core */
