/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef HELPER_H_
#define HELPER_H_

#include <Reflection.h>

/**
 * Helper structure.
 */
struct HelperAT {
        __c (void)
        HelperAT () : cnt (0) {}

        _m (inc) void inc () { cnt++; }
        _m (dec) void dec () { cnt--; }
        _m (set) void set (int i) { cnt = i; }

        int cnt;

        _e (HelperAT)
};

#endif /* HELPER_H_ */
