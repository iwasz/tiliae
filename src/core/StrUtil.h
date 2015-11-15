/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_STRUTIL_H_
#define TILIAE_STRUTIL_H_

#include <cstring>
#include <string>
#include "core/ApiMacro.h"

inline std::string toStr (const char *s)
{
        return (s) ? (s) : ("");
}

TILIAE_API extern int strcmpNull (const char *a, const char *b);
TILIAE_API extern const char *mkCopy (const char *s);

struct Eqstr {
        bool operator()(const char* s1, const char* s2) const {
                return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
        }
};

struct StrLess {
        bool operator() (const char *x, const char *y) const { return std::strcmp (x, y) < 0; }
};

#endif /* STRUTIL_H_ */
