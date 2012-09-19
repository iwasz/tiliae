/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FIELDWRAPPER_H_
#define FIELDWRAPPER_H_

#include "core/variant/Cast.h"

namespace Reflection {

struct IFieldWrapper {
        virtual ~IFieldWrapper () {}
        virtual Core::Variant get (Core::Variant const &object) = 0;
        virtual void set (Core::Variant const &object, Core::Variant const &value) = 0;
        virtual std::type_info const &getType () const = 0;
};

/*##########################################################################*/

template <typename T>
struct FieldWrapper {
};

/****************************************************************************/

template <typename T, typename C>
struct FieldWrapper <T C::*> : public IFieldWrapper {

        typedef T C::*FieldPtr;
        FieldWrapper (FieldPtr p = 0) : ptr (p) {}
        virtual ~FieldWrapper () {}

        Core::Variant get (Core::Variant const &object);
        void set (Core::Variant const &object, Core::Variant const &value);

        std::type_info const &getType () const { return typeid (typename Core::normalize<T>::type); }

private:

        FieldPtr ptr;

};

/****************************************************************************/

template <typename T, typename C>
Core::Variant FieldWrapper <T C::*>::get (Core::Variant const &object)
{
        return Core::Variant (ocast <C const *> (object)->*ptr);
}

/****************************************************************************/

template <typename T, typename C>
void FieldWrapper <T C::*>::set (Core::Variant const &object, Core::Variant const &value)
{
        ocast <C *> (object)->*ptr = ocast <T> (value);
}

/****************************************************************************/

template <typename T>
IFieldWrapper *createFieldWrapper (T t)
{
        return new FieldWrapper <T> (t);
}

/*##########################################################################*/

template <typename T>
struct FieldWrapperRetByPtr {
};

template <typename T, typename C>
struct FieldWrapperRetByPtr <T C::*> : public IFieldWrapper {

        typedef T C::*FieldPtr;
        FieldWrapperRetByPtr (FieldPtr p = 0) : ptr (p) {}
        virtual ~FieldWrapperRetByPtr () {}

        Core::Variant get (Core::Variant const &object);
        void set (Core::Variant const &object, Core::Variant const &value);

        std::type_info const &getType () const { return typeid (typename Core::normalize<T>::type); }

private:

        FieldPtr ptr;

};

/****************************************************************************/

template <typename T, typename C>
Core::Variant FieldWrapperRetByPtr <T C::*>::get (Core::Variant const &object)
{
        return Core::Variant (&(ocast <C *> (object)->*ptr));
}

/****************************************************************************/

template <typename T, typename C>
void FieldWrapperRetByPtr <T C::*>::set (Core::Variant const &object, Core::Variant const &value)
{
        ocast <C *> (object)->*ptr = ocast <T> (value);
}

/****************************************************************************/

template <typename T>
IFieldWrapper *createFieldWrapperRetByPtr (T t)
{
        return new FieldWrapperRetByPtr <T> (t);
}

/*##########################################################################*/

template <typename T>
struct FieldWrapperEnum {
};

template <typename T, typename C>
struct FieldWrapperEnum <T C::*> : public IFieldWrapper {

        typedef T C::*FieldPtr;
        FieldWrapperEnum (FieldPtr p = 0) : ptr (p) {}
        virtual ~FieldWrapperEnum () {}

        Core::Variant get (Core::Variant const &object);
        void set (Core::Variant const &object, Core::Variant const &value);

        std::type_info const &getType () const { return typeid (typename Core::normalize<T>::type); }

private:

        FieldPtr ptr;

};

/****************************************************************************/

template <typename T, typename C>
Core::Variant FieldWrapperEnum <T C::*>::get (Core::Variant const &object)
{
        return Core::Variant (static_cast <unsigned int> (ocast <C const *> (object)->*ptr));
}

/****************************************************************************/

template <typename T, typename C>
void FieldWrapperEnum <T C::*>::set (Core::Variant const &object, Core::Variant const &value)
{
        ocast <C *> (object)->*ptr = static_cast <T> (vcast <unsigned int> (value));
}

/****************************************************************************/

template <typename T>
IFieldWrapper *createFieldWrapperEnum (T t)
{
        return new FieldWrapperEnum <T> (t);
}

/*##########################################################################*/

} /* namespace Reflection */
#endif /* FIELDWRAPPER_H_ */
