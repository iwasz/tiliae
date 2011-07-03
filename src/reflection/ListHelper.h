/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TTE_LISTHELPER_H_
#define TTE_LISTHELPER_H_

#include "../core/string/String.h"
#include "../core/Typedefs.h"
#include "../core/ApiMacro.h"

namespace Reflection {

/**
 * Stosowane do tworzenia list w _b. Nie jest to częścią API, tylko pomocniczą
 * klasą, ale musi mieć TILIAE_API, bo makra tego używają.
 */
struct TILIAE_API ListHelper {

        static Core::StringList createStringList (const std::string &b0,
                                             const std::string &b1 = std::string (),
                                             const std::string &b2 = std::string (),
                                             const std::string &b3 = std::string (),
                                             const std::string &b4 = std::string (),
                                             const std::string &b5 = std::string (),
                                             const std::string &b6 = std::string (),
                                             const std::string &b7 = std::string (),
                                             const std::string &b8 = std::string (),
                                             const std::string &b9 = std::string ());
};

}

#endif /* LISTHELPER_H_ */
