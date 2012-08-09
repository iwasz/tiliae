/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "StrUtil.h"

int strcmpNull (const char *a, const char *b)
{
        if (!a && !b) {
                return 0;
        }

        if ((!a && b) || (a && !b)) {
                return 1;
        }

        return strcmp (a, b);
}

const char *mkCopy (const char *s)
{
        if (!s) {
                return NULL;
        }

        int len = strlen (s);
        char *ret = new char [len + 1];
        strcpy (ret, s);
        return ret;
}
