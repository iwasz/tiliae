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

inline std::string toStr (const char *s)
{
        return (s) ? (s) : ("");
}

inline int strcmpNull (const char *a, const char *b)
{
        if (!a && !b) {
                return 0;
        }

        if ((!a && b) || (a && !b)) {
                return 1;
        }

        return strcmp (a, b);
}

#endif /* STRUTIL_H_ */
