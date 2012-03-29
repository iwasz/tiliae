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
                ABSTRACT_ARGUMENT,
                LAZYINIT_ARGUMENT,
                ID_ARGUMENT,
                CLASS_ARGUMENT,
                PARENT_ARGUMENT,
                DEPENDSON_ARGUMENT,
                INITMETHOD_ARGUMENT,
                FACTORY_ARGUMENT,
                EDITOR_ARGUMENT,
                DESCRIPTION_ARGUMENT,
                OUTER_ARGUMENT,
                SCOPE_ARGUMENT,
        };

        void setString (AttributeName key, const std::string &value);
        std::string const &getString (AttributeName key, bool getFromParent = true) const;

        void setInt (AttributeName key, int value);
        int getInt (AttributeName key, bool getFromParent = true) const;

        void setBool (AttributeName key, bool value);
        bool getBool (AttributeName key, bool getFromParent = true) const;

//        void addAttributes (const Attributes &a);
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
