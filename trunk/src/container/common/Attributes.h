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
        std::string const &getString (const std::string &key, bool getFromParent = true) const;

        void setInt (const std::string &key, int value);
        int getInt (const std::string &key, bool getFromParent = true) const;

        void setBool (const std::string &key, bool value);
        bool getBool (const std::string &key, bool getFromParent = true) const;

        void addAttributes (const Attributes &a);
        void removeAttributes (const Core::StringList &l);
        void removeAttribute (const std::string &key);
        bool containsKey (const std::string &key, bool getFromParent = true) const;

        void setParentAttributes (Ptr <Attributes const> a) { parent = a; }

private:

        typedef std::map <std::string, int> IntMap;

        Core::StringMap strMap;
        IntMap intMap;
        Ptr <Attributes const> parent;
};

}

#	endif /* ATTRIBUTES_H_ */
