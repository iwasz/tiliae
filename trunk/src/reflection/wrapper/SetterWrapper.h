/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TTEE_SETTER_WRAPPER_H_
#define TTEE_SETTER_WRAPPER_H_

#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>

#include "variant/Cast.h"
#include "../../core/Typedefs.h"
#include "../../core/variant/Variant.h"
#include "ICallableWrapper.h"
#include "../../core/Exception.h"
#include "../../core/ApiMacro.h"
#include "WrapperCommons.h"

namespace Reflection {

template<typename T>
struct SetterPtrWrapper {
};

/*##########################################################################*/

template<typename T, typename C, typename A1>
struct SetterPtrWrapper <T (C::*) (A1)> : public ICallableWrapper {

        typedef T (C::*MethodPtr) (A1);
        SetterPtrWrapper (MethodPtr p = 0) : ptr (p) {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 1; }

private:
        MethodPtr ptr;
};

template<typename T, typename C, typename A1>
Core::Variant SetterPtrWrapper <T (C::*) (A1)>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        Core::VariantVector::iterator i = args->begin ();
        return Core::Variant ((ocast <C*> (object)->*ptr) (ocast <A1> (*i)));
}

/****************************************************************************/

template<typename C, typename A1>
struct SetterPtrWrapper <void (C::*) (A1)> : public ICallableWrapper {

        typedef void (C::*MethodPtr) (A1);
        SetterPtrWrapper (MethodPtr p = 0) : ptr (p) {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);/* { throwConstMethod (); exit (1); }*/
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 1; }

private:
        MethodPtr ptr;
};

template<typename C, typename A1>
Core::Variant SetterPtrWrapper <void (C::*) (A1)>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        Core::VariantVector::iterator i = args->begin ();
        (ocast <C*> (object)->*ptr) (ocast <A1> (*i));
        return Core::Variant ();
}

/****************************************************************************/

template<typename T, typename C, typename A1>
struct SetterPtrWrapper <T (C::*) (A1) const> : public ICallableWrapper {

        typedef T (C::*MethodPtr) (A1)const;
        SetterPtrWrapper (MethodPtr p = 0) : ptr (p) {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 1; }

private:
        MethodPtr ptr;
};

template<typename T, typename C, typename A1>
Core::Variant SetterPtrWrapper <T (C::*) (A1) const>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        Core::VariantVector::iterator i = args->begin ();
        return Core::Variant ((ocast <C const *> (object)->*ptr) (ocast <A1> (*i)));
}

/****************************************************************************/

template<typename C, typename A1>
struct SetterPtrWrapper <void (C::*) (A1) const> : public ICallableWrapper {

        typedef void (C::*MethodPtr) (A1)const;
        SetterPtrWrapper (MethodPtr p = 0) : ptr (p) {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 1; }

private:
        MethodPtr ptr;
};

template<typename C, typename A1>
Core::Variant SetterPtrWrapper <void (C::*) (A1) const>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        Core::VariantVector::iterator i = args->begin ();
        (ocast <C const *> (object)->*ptr) (ocast <A1> (*i));
        return Core::Variant ();
}

/*##########################################################################*/

template <typename T>
boost::shared_ptr <SetterPtrWrapper <T> > createSetterWrapper (T t)
{
        return boost::make_shared <SetterPtrWrapper <T> > (t);
}

} // namespace

#	endif /* METHODWRAPPER_H_ */
