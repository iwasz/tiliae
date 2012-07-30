/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include "allocator/ArrayRegionAllocator.h"

BOOST_AUTO_TEST_SUITE (AllocatorTest10);

using namespace boost;
using namespace Core;

/**
 *
 */
BOOST_AUTO_TEST_CASE (testAlloc1)
{
        ArrayRegionAllocator <char> alloc;
        BOOST_REQUIRE_EQUAL (alloc.getNumberOfRegions (), 0U);
        BOOST_REQUIRE_EQUAL (alloc.calculateFreeMemory (), 0U);
}

BOOST_AUTO_TEST_CASE (testAlloc2)
{
        ArrayRegionAllocator <char> alloc (10);
        char *p = alloc.malloc (3);
        (void)p;

        BOOST_REQUIRE_EQUAL (alloc.getNumberOfRegions (), 1U);
        BOOST_REQUIRE_EQUAL (alloc.calculateFreeMemory (), 7U);

        p = alloc.malloc (3);
        BOOST_REQUIRE_EQUAL (alloc.getNumberOfRegions (), 1U);
        BOOST_REQUIRE_EQUAL (alloc.calculateFreeMemory (), 4U);

        p = alloc.malloc (5);
        BOOST_REQUIRE_EQUAL (alloc.getNumberOfRegions (), 2U);
        BOOST_REQUIRE_EQUAL (alloc.calculateFreeMemory (), 5U);

        p = alloc.malloc (0);
        BOOST_REQUIRE_EQUAL (alloc.getNumberOfRegions (), 2U);
        BOOST_REQUIRE_EQUAL (alloc.calculateFreeMemory (), 5U);

        p = alloc.malloc (10);
        BOOST_REQUIRE_EQUAL (alloc.getNumberOfRegions (), 3U);
        BOOST_REQUIRE_EQUAL (alloc.calculateFreeMemory (), 0U);

        BOOST_REQUIRE_THROW (alloc.malloc (11), AllocationException);
}

BOOST_AUTO_TEST_CASE (testAlloc3)
{
        ArrayRegionAllocator <double> alloc (10);
        double *p = alloc.malloc (3);
        (void)p;

        BOOST_REQUIRE_EQUAL (alloc.getNumberOfRegions (), 1U);
        BOOST_REQUIRE_EQUAL (alloc.calculateFreeMemory (), 7U);

        p = alloc.malloc (3);
        BOOST_REQUIRE_EQUAL (alloc.getNumberOfRegions (), 1U);
        BOOST_REQUIRE_EQUAL (alloc.calculateFreeMemory (), 4U);

        p = alloc.malloc (5);
        BOOST_REQUIRE_EQUAL (alloc.getNumberOfRegions (), 2U);
        BOOST_REQUIRE_EQUAL (alloc.calculateFreeMemory (), 5U);

        p = alloc.malloc (0);
        BOOST_REQUIRE_EQUAL (alloc.getNumberOfRegions (), 2U);
        BOOST_REQUIRE_EQUAL (alloc.calculateFreeMemory (), 5U);

        p = alloc.malloc (10);
        BOOST_REQUIRE_EQUAL (alloc.getNumberOfRegions (), 3U);
        BOOST_REQUIRE_EQUAL (alloc.calculateFreeMemory (), 0U);

        BOOST_REQUIRE_THROW (alloc.malloc (11), AllocationException);
}

BOOST_AUTO_TEST_SUITE_END ();
