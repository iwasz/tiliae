/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ITYPE_H_
#define ITYPE_H_

#include <typeinfo>
#include "../../core/variant/Variant.h"
#include "../../core/variant/Cast.h"

namespace k202 {

struct IType {

        virtual ~IType () {}
        virtual bool operator== (const IType &) const = 0;
        virtual const std::type_info *getTypeInfo () const = 0;
        virtual bool equals (const Core::Variant &lhs, const Core::Variant &rhs) const = 0;
};

struct AbstractType : public IType {

        virtual ~AbstractType () {}
        bool operator== (const IType &t) const { return t.getTypeInfo () == getTypeInfo (); }
};

template <typename T>
struct Type : public AbstractType {

        virtual ~Type () {}
        const std::type_info *getTypeInfo () const { return &typeid (T); }
        bool equals (const Core::Variant &lhs, const Core::Variant &rhs) const;
};

template <typename T>
bool Type<T>::equals (const Core::Variant &lhs, const Core::Variant &rhs) const
{
        if (lhs.isNone () && rhs.isNone ()) {
                return true;
        }

        if (lhs.isNone () || rhs.isNone ()) {
                return false;
        }

        return vcast <T> (lhs) == vcast <T> (rhs);
}

/**
 * Nie za bardzo wiem skąd się instancjonuje ten szabon dla Variant. Trzeba by to
 * miesjce znaleźć, poprawić, żeby się nie instancjonował i skasować tą specjalizację.
 */
template <>
struct Type <Core::Variant> : public AbstractType {

        virtual ~Type () {}
        const std::type_info *getTypeInfo () const { return &typeid (Core::Variant); }
        bool equals (const Core::Variant &lhs, const Core::Variant &rhs) const { return false; }
};
}

#endif /* ITYPE_H_ */
