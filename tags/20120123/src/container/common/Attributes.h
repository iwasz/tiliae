/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ATTRIBUTES_H_
#define ATTRIBUTES_H_

#include <map>
#include "../../core/string/String.h"
#include "../../core/Typedefs.h"
#include "../../core/ApiMacro.h"

namespace Container {

/**
 * Attributes of Meta and BeanFactory objects. It holds things
 * such as ID, scope, parent etc. Nie jest częścią interfejsu,
 * ale metody inline tego potrzebują.
 * \ingroup Container
 */
class TILIAE_API Attributes {
public:

        void setString (const std::string &key, const std::string &value);
        std::string getString (const std::string &key) const;

        void setInt (const std::string &key, int value);
        int getInt (const std::string &key) const;

        void setBool (const std::string &key, bool value);
        bool getBool (const std::string &key) const;

        void addAttributes (const Attributes &a);
        void removeAttributes (const Core::StringList &l);
        void removeAttribute (const std::string &key);
        bool containsKey (const std::string &key) const;

private:

        Core::StringMap strMap;
        typedef std::map <std::string, int> IntMap;
        IntMap intMap;
};

}

#	endif /* ATTRIBUTES_H_ */
