/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "StringUtils.h"

namespace Common {

// TODO zronic tego test w tools.
Core::StringList StringUtils::split (const std::string &input, const std::string &separator)
{
        Core::StringList  ret;
        std::string::size_type h = 0, i = 0, length = input.length ();

        do {
                i = input.find (separator, h);
                ret.push_back (input.substr (h, i - h));
                h = i + 1;

        } while (i < length);

        return ret;
}

}
