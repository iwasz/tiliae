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
        c__ (void)
        HelperAT () : cnt (0) {}

        m_ (inc) void inc () { cnt++; }
        m_ (dec) void dec () { cnt--; }
        m_ (set) void set (int i) { cnt = i; }

        int cnt;

        e_ (HelperAT)
};

#endif /* HELPER_H_ */
