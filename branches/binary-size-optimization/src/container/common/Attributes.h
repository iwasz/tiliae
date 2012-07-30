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

        enum AttributeName {
                ABSTRACT_ARGUMENT,    // b
                LAZYINIT_ARGUMENT,    // b
                ID_ARGUMENT,          // s
                CLASS_ARGUMENT,       // s
                PARENT_ARGUMENT,      // s
                INITMETHOD_ARGUMENT,  // s
                FACTORY_ARGUMENT,     // s
                EDITOR_ARGUMENT,      // s
                SCOPE_ARGUMENT,       // s
        };

        void setString (AttributeName key, const std::string &value);
        std::string const &getString (AttributeName key, bool getFromParent = true) const;

        void setInt (AttributeName key, int value);
        int getInt (AttributeName key, bool getFromParent = true) const;

        void setBool (AttributeName key, bool value);
        bool getBool (AttributeName key, bool getFromParent = true) const;

        void removeAttribute (AttributeName key);
        bool containsKey (AttributeName key, bool getFromParent = true) const;

        void setParentAttributes (Ptr <Attributes const> a) { parent = a; }

private:

        typedef std::map <unsigned char, int> AttribIntMap;
        typedef std::map <unsigned char, std::string> AttribStrMap;

        AttribStrMap strMap;
        AttribIntMap intMap;
        Ptr <Attributes const> parent;
};

}

#	endif /* ATTRIBUTES_H_ */
