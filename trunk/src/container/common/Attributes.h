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
#include "core/string/String.h"
#include "core/Typedefs.h"
#include "core/ApiMacro.h"

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
                ID_ARGUMENT,          // s
                CLASS_ARGUMENT,       // s
                PARENT_ARGUMENT,      // s
                INITMETHOD_ARGUMENT,  // s
                FACTORY_ARGUMENT,     // s
                EDITOR_ARGUMENT,      // s
                DEPENDS_ON_ARGUMENT,  // s
                LAST_STRING,
                ABSTRACT_ARGUMENT,
                LAZYINIT_ARGUMENT,
                SCOPE_ARGUMENT,
                IS_PARENT_ARGUMENT
        };

        Attributes ();

        void setString (AttributeName key, const char *value);
        const char *getString (AttributeName key, bool getFromParent = true) const;

        void setInt (AttributeName key, int value);
        int getInt (AttributeName key, bool getFromParent = true) const;

        void setBool (AttributeName key, bool value) { setInt (key, value); }
        bool getBool (AttributeName key, bool getFromParent = true) const { int i = getInt (key, getFromParent); return (i > 0); }

        bool containsKey (AttributeName key, bool getFromParent = true) const;
        void setParentAttributes (Attributes const *a) { parent = a; }

        /**
         * Tworzy kopię zainicjowaną wartościami z tego Attributes i z jego rodziców.
         */
        Attributes *makeCopyOnHeap () const;
        static void deleteHeapCopy (Attributes *a);

private:

        enum IntegerAttributeMaskAndSet {
                ABSTRACT_ARGUMENT_MASK = 0x01,
                ABSTRACT_ARGUMENT_SET = 0x02,
                LAZYINIT_ARGUMENT_MASK = 0x04,
                LAZYINIT_ARGUMENT_SET = 0x08,
                SCOPE_ARGUMENT_MASK = 0x30,
                SCOPE_ARGUMENT_SET = 0x40,
        };

        int getIntPriv (AttributeName key) const;
        const char *copyString (AttributeName key) const;

private:

        const char *strMapData[LAST_STRING];
        Attributes const *parent;

        struct {
                unsigned int abstract:1;
                unsigned int abstractSet:1;
                unsigned int lazyInit:1;
                unsigned int lazyInitSet:1;
                unsigned int scope:2;
                unsigned int scopeSet:1;
                unsigned int isParent:1;
        } intData;

};

}

#	endif /* ATTRIBUTES_H_ */
