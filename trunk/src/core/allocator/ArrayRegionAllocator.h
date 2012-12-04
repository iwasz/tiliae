/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ARRAYREGIONALLOCATOR_H_
#define ARRAYREGIONALLOCATOR_H_

#include <vector>
#include "IAllocator.h"

namespace Core {

/**
 *
 */
template <typename T>
class TILIAE_API ArrayRegionAllocator : public IAllocator {
public:

        enum { DEFAULT_REGION_SIZE = 8192 };

        /**
         * New instance, with specified region size in units of type T. Defaults to
         * DEFAULT_REGION_SIZE * sizeof (T). For T == char it means DEFAULT_REGION_SIZE bytes.
         */
        ArrayRegionAllocator (size_t regionSize = DEFAULT_REGION_SIZE) :
                regionSize (regionSize),
                endPointer (NULL) {}

        virtual ~ArrayRegionAllocator ();

        /**
         * Allocate size elements of type T.
         */
        T *mallocT (size_t size);

        /**
         * Allocate size * sizeof (T) bytes.
         */
        void *malloc (size_t size) { return mallocT (size); }

        /// Returns free memory in current region (in T units) or 0 if there is no region yet.
        size_t calculateFreeMemory ();
        size_t getNumberOfRegions () { return regions.size (); }

private:

        void throwIfNotExceeded (size_t size);
        void addNewRegion ();

private:

        size_t regionSize;
        typedef std::vector <T *> RegionsVector;
        RegionsVector regions;
        T *endPointer;
};

template <typename T>
ArrayRegionAllocator <T>::~ArrayRegionAllocator ()
{
        for (typename RegionsVector::iterator i = regions.begin (); i != regions.end (); ++i) {
                delete [] *i;
        }
}

template <typename T>
T *ArrayRegionAllocator <T>::mallocT (size_t sizeReq)
{
        size_t size = sizeReq * sizeof (T);
        size += ((size % 4) ? (4 - size % 4) : (0));

        // Check if size is smaller or equal to regionSize.
        throwIfNotExceeded (size);

        // Calculate remaining memory in current region.
        size_t freeMem = calculateFreeMemory ();

        // Add new region if current is full.
        if (freeMem < size) {
                addNewRegion ();
        }

        // Allocate
        T *ret = endPointer;
        endPointer += size;
        return ret;
}

template <typename T>
void ArrayRegionAllocator <T>::throwIfNotExceeded (size_t size)
{
        if (size > regionSize) {
                throw AllocationException ("ArrayRegionAllocator::malloc : requested amount of memory is bigger than region size.");
        }
}

template <typename T>
size_t ArrayRegionAllocator <T>::calculateFreeMemory ()
{
        if (!endPointer) {
                return 0;
        }

        return (regionSize * sizeof (T) - (endPointer - regions.back ())) / sizeof (T);
}

template <typename T>
void ArrayRegionAllocator <T>::addNewRegion ()
{
        endPointer = new T[regionSize];

//#ifndef NDEBUG
//        memset (endPointer, 0, regionSize * sizeof (T));
//#endif

        regions.push_back (endPointer);
}

} /* namespace Core */

#endif /* ARRAYREGIONALLOCATOR_H_ */
