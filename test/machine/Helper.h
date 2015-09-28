/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STT_HELPER_H_
#define STT_HELPER_H_

#include "reflection/Reflection.h"

/**
 * Helper structure.
 */
struct HelperAT {
        REFLECTION_CONSTRUCTOR_ (void)
        HelperAT () : cnt (0) {}

        REFLECTION_METHOD (inc) void inc () { cnt++; }
        REFLECTION_METHOD (dec) void dec () { cnt--; }
        REFLECTION_METHOD (set) void set (int i) { cnt = i; }

        int cnt;

        REFLECTION_END (HelperAT)
};

#endif /* HELPER_H_ */
