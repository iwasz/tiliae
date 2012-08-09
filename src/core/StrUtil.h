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
#include "ApiMacro.h"

inline std::string toStr (const char *s)
{
        return (s) ? (s) : ("");
}

TILIAE_API extern int strcmpNull (const char *a, const char *b);
TILIAE_API extern const char *mkCopy (const char *s);

#endif /* STRUTIL_H_ */
