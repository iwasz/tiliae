/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/preprocessor/repetition/repeat.hpp>
#include "ListHelper.h"

namespace Reflection {

Core::StringList ListHelper::createStringList (const std::string &b0,
                                             const std::string &b1,
                                             const std::string &b2,
                                             const std::string &b3,
                                             const std::string &b4,
                                             const std::string &b5,
                                             const std::string &b6,
                                             const std::string &b7,
                                             const std::string &b8,
                                             const std::string &b9)
{
        Core::StringList ret;

        #define DECL(z, n, data) if (!b ## n.empty ()) { ret.push_back (b ## n); }
        BOOST_PP_REPEAT (10, DECL, ~);
        #undef DECL

        return ret;
}

}
