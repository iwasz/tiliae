/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TTEE_METHODWRAPPER_H_
#define TTEE_METHODWRAPPER_H_

#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>

#include "core/variant/Cast.h"
#include "core/Typedefs.h"
#include "core/variant/Variant.h"
#include "ICallableWrapper.h"
#include "core/Exception.h"
#include "core/ApiMacro.h"
#include "WrapperCommons.h"

namespace Reflection {

template<typename T>
struct MethodPtrWrapper {
};

/*### 0 ARG ################################################################*/

template<typename T, typename C>
struct MethodPtrWrapper <T (C::*) ()> : public ICallableWrapper {

        typedef T (C::*MethodPtr) ();
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (void*); }
        unsigned int getArity () const { return 0; }

private:
        MethodPtr ptr;
};

template<typename T, typename C>
Core::Variant MethodPtrWrapper <T (C::*) ()>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 0);
        return Core::PtrHelp::convert ((ocast <C*> (object)->*ptr) ());
}

/****************************************************************************/

template<typename C>
struct MethodPtrWrapper <void (C::*) ()> : public ICallableWrapper {

        typedef void (C::*MethodPtr) ();
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (void*); }
        unsigned int getArity () const { return 0; }

private:
        MethodPtr ptr;
};

template<typename C>
Core::Variant MethodPtrWrapper <void (C::*) ()>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 0);
        (ocast <C*> (object)->*ptr) ();
        return Core::Variant ();
}

/****************************************************************************/

template<typename T, typename C>
struct MethodPtrWrapper <T (C::*) () const> : public ICallableWrapper {

        typedef T (C::*MethodPtr) ()const;
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (void*); }
        unsigned int getArity () const { return 0; }

private:
        MethodPtr ptr;
};

template<typename T, typename C>
Core::Variant MethodPtrWrapper <T (C::*) () const>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 0);
        return Core::PtrHelp::convert ((ocast <C const *> (object)->*ptr) ());
}

/****************************************************************************/

template<typename C>
struct MethodPtrWrapper <void (C::*) () const> : public ICallableWrapper {

        typedef void (C::*MethodPtr) ()const;
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (void*); }
        unsigned int getArity () const { return 0; }

private:
        MethodPtr ptr;
};

template<typename C>
Core::Variant MethodPtrWrapper <void (C::*) () const>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 0);
        (ocast <C const *> (object)->*ptr) ();
        return Core::Variant ();
}

/*### 1 ARG ################################################################*/

template<typename T, typename C, typename A1>
struct MethodPtrWrapper <T (C::*) (A1)> : public ICallableWrapper {

        typedef T (C::*MethodPtr) (A1);
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 1; }

private:
        MethodPtr ptr;
};

template<typename T, typename C, typename A1>
Core::Variant MethodPtrWrapper <T (C::*) (A1)>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        Core::VariantVector::iterator i = args->begin ();
        return Core::PtrHelp::convert ((ocast <C*> (object)->*ptr) (ocast <A1> (*i)));
}

/****************************************************************************/

template<typename C, typename A1>
struct MethodPtrWrapper <void (C::*) (A1)> : public ICallableWrapper {

        typedef void (C::*MethodPtr) (A1);
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);/* { throwConstMethod (); exit (1); }*/
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 1; }

private:
        MethodPtr ptr;
};

template<typename C, typename A1>
Core::Variant MethodPtrWrapper <void (C::*) (A1)>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        Core::VariantVector::iterator i = args->begin ();
        (ocast <C*> (object)->*ptr) (ocast <A1> (*i));
        return Core::Variant ();
}

/****************************************************************************/

template<typename T, typename C, typename A1>
struct MethodPtrWrapper <T (C::*) (A1) const> : public ICallableWrapper {

        typedef T (C::*MethodPtr) (A1)const;
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 1; }

private:
        MethodPtr ptr;
};

template<typename T, typename C, typename A1>
Core::Variant MethodPtrWrapper <T (C::*) (A1) const>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        Core::VariantVector::iterator i = args->begin ();
        return Core::PtrHelp::convert ((ocast <C const *> (object)->*ptr) (ocast <A1> (*i)));
}

/****************************************************************************/

template<typename C, typename A1>
struct MethodPtrWrapper <void (C::*) (A1) const> : public ICallableWrapper {

        typedef void (C::*MethodPtr) (A1)const;
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 1; }

private:
        MethodPtr ptr;
};

template<typename C, typename A1>
Core::Variant MethodPtrWrapper <void (C::*) (A1) const>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        Core::VariantVector::iterator i = args->begin ();
        (ocast <C const *> (object)->*ptr) (ocast <A1> (*i));
        return Core::Variant ();
}

/*### 2 ARG ################################################################*/

template<typename T, typename C, typename A1, typename A2>
struct MethodPtrWrapper <T (C::*) (A1, A2)> : public ICallableWrapper {

        typedef T (C::*MethodPtr) (A1, A2);
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 2; }

private:
        MethodPtr ptr;
};

template<typename T, typename C, typename A1, typename A2>
Core::Variant MethodPtrWrapper <T (C::*) (A1, A2)>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 2);
        Core::VariantVector::iterator i = args->begin ();
        Core::VariantVector::iterator j = args->begin (); ++j;
        return Core::PtrHelp::convert ((ocast <C*> (object)->*ptr) (ocast <A1> (*i), ocast <A2> (*j)));
}

/****************************************************************************/

template<typename C, typename A1, typename A2>
struct MethodPtrWrapper <void (C::*) (A1, A2)> : public ICallableWrapper {

        typedef void (C::*MethodPtr) (A1, A2);
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);/* { throwConstMethod (); exit (1); }*/
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 2; }

private:
        MethodPtr ptr;
};

template<typename C, typename A1, typename A2>
Core::Variant MethodPtrWrapper <void (C::*) (A1, A2)>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 2);
        Core::VariantVector::iterator i = args->begin ();
        Core::VariantVector::iterator j = args->begin (); ++j;
        (ocast <C*> (object)->*ptr) (ocast <A1> (*i), ocast <A2> (*j));
        return Core::Variant ();
}

/****************************************************************************/

template<typename T, typename C, typename A1, typename A2>
struct MethodPtrWrapper <T (C::*) (A1, A2) const> : public ICallableWrapper {

        typedef T (C::*MethodPtr) (A1, A2)const;
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 2; }

private:
        MethodPtr ptr;
};

template<typename T, typename C, typename A1, typename A2>
Core::Variant MethodPtrWrapper <T (C::*) (A1, A2) const>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 2);
        Core::VariantVector::iterator i = args->begin ();
        Core::VariantVector::iterator j = args->begin (); ++j;
        return Core::PtrHelp::convert ((ocast <C const *> (object)->*ptr) (ocast <A1> (*i), ocast <A2> (*j)));
}

/****************************************************************************/

template<typename C, typename A1, typename A2>
struct MethodPtrWrapper <void (C::*) (A1, A2) const> : public ICallableWrapper {

        typedef void (C::*MethodPtr) (A1, A2)const;
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 2; }

private:
        MethodPtr ptr;
};

template<typename C, typename A1, typename A2>
Core::Variant MethodPtrWrapper <void (C::*) (A1, A2) const>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 2);
        Core::VariantVector::iterator i = args->begin ();
        Core::VariantVector::iterator j = args->begin (); ++j;
        (ocast <C const *> (object)->*ptr) (ocast <A1> (*i), ocast <A2> (*j));
        return Core::Variant ();
}

/*### 3 ARG ################################################################*/

template<typename T, typename C, typename A1, typename A2, typename A3>
struct MethodPtrWrapper <T (C::*) (A1, A2, A3)> : public ICallableWrapper {

        typedef T (C::*MethodPtr) (A1, A2, A3);
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 3; }

private:
        MethodPtr ptr;
};

template<typename T, typename C, typename A1, typename A2, typename A3>
Core::Variant MethodPtrWrapper <T (C::*) (A1, A2, A3)>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 3);
        return Core::PtrHelp::convert ((ocast <C*> (object)->*ptr) (ocast <A1> (args->operator[] (0)), ocast <A2> (args->operator[] (1)), ocast <A3> (args->operator[] (2))));
}

/****************************************************************************/

template<typename C, typename A1, typename A2, typename A3>
struct MethodPtrWrapper <void (C::*) (A1, A2, A3)> : public ICallableWrapper {

        typedef void (C::*MethodPtr) (A1, A2, A3);
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 3; }

private:
        MethodPtr ptr;
};

template<typename C, typename A1, typename A2, typename A3>
Core::Variant MethodPtrWrapper <void (C::*) (A1, A2, A3)>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 3);
        (ocast <C*> (object)->*ptr) (ocast <A1> (args->operator[] (0)), ocast <A2> (args->operator[] (1)), ocast <A3> (args->operator[] (2)));
        return Core::Variant ();
}

/****************************************************************************/

template<typename T, typename C, typename A1, typename A2, typename A3>
struct MethodPtrWrapper <T (C::*) (A1, A2, A3) const> : public ICallableWrapper {

        typedef T (C::*MethodPtr) (A1, A2, A3)const;
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 3; }

private:
        MethodPtr ptr;
};

template<typename T, typename C, typename A1, typename A2, typename A3>
Core::Variant MethodPtrWrapper <T (C::*) (A1, A2, A3) const>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 3);
        return Core::PtrHelp::convert ((ocast <C const *> (object)->*ptr) (ocast <A1> (args->operator[] (0)), ocast <A2> (args->operator[] (1)), ocast <A3> (args->operator[] (2))));
}

/****************************************************************************/

template<typename C, typename A1, typename A2, typename A3>
struct MethodPtrWrapper <void (C::*) (A1, A2, A3) const> : public ICallableWrapper {

        typedef void (C::*MethodPtr) (A1, A2, A3)const;
        MethodPtrWrapper (MethodPtr p = 0) : ptr (p) {}
        virtual ~MethodPtrWrapper () {}

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<A1>::type); }
        unsigned int getArity () const { return 3; }

private:
        MethodPtr ptr;
};

template<typename C, typename A1, typename A2, typename A3>
Core::Variant MethodPtrWrapper <void (C::*) (A1, A2, A3) const>::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 3);
        (ocast <C const *> (object)->*ptr) (ocast <A1> (args->operator[] (0)), ocast <A2> (args->operator[] (1)), ocast <A3> (args->operator[] (2)));
        return Core::Variant ();
}

/*##########################################################################*/

template <typename T>
MethodPtrWrapper <T> *createMethodWrapper (T t)
{
        return new MethodPtrWrapper <T> (t);
}

} // namespace

#	endif /* METHODWRAPPER_H_ */
