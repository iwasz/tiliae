/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include "../core/Typedefs.h"
#include "../core/string/String.h"
#include "../core/ApiMacro.h"

namespace Common {

/**
 * Proste metody pomocnicze do operacji na stringach.
 */
struct TILIAE_API StringUtils {

        static Core::StringList split (const std::string &input, const std::string &separator);

        template <typename T>
        static std::string join (const T &s, const std::string &separator);

};

/****************************************************************************/

template <typename T>
std::string StringUtils::join (const T &s, const std::string &separator)
{
        if (!s.size ())
                return "";

        std::string ret;
        typename T::const_iterator i = s.begin ();

        for (;;) {
                ret += *i;

                if (++i != s.end ())
                        ret += separator;
                else
                        break;

        }

        return ret;
}

} // nam

#endif /* STRINGUTILS_H_ */
