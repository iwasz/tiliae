/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

/*
 * UWAGA. Nazwa tego pliku musi byc Pointer, gdyż koliduje z innym plikiem
 * o nazwie Ptr.h. Dla uproszczenia zostawiam wiec Pointer.h
 */

#include <boost/shared_ptr.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include "ApiMacro.h"

#ifndef CORE_78954789_PTR_H_
#define CORE_78954789_PTR_H_

namespace Core {

/**
 * Krótsza nazwa dla boost::shared_ptr.
 * Jest to zrobione po to, żeby uprościć korzystaine z shared_ptr, który imho ma
 * za długą nazwę. Przyzwyczaiłem się do Ptr. Dlaczego #define jest lepsze niż moja
 * klasa Ptr? Ponieważ:
 * 1. Ptr nie implementuje NIC nowego w stosunku do shared_ptr, więc po co klasa.
 * 2. Chodzi tylko o skrócenie nazwy do Ptr, więc po co tyle prądu.
 * 3. boost::mem_fn nie działa z Ptr, bo definiuje specjalne funkcje akceptujące
 * shared_ptr.
 * 4. Możliwe, że są inne miejsca w boost, gdzie Ptr nie będzie działać, a shared_ptr
 * będzie.
 * \ingroup CoreAPI
 */
#define Ptr ::boost::shared_ptr

using boost::dynamic_pointer_cast;
using boost::const_pointer_cast;
using boost::static_pointer_cast;

/*--------------------------------------------------------------------------*/

template <typename T>
struct __is_Ptr_helper {
        enum { value = false };
};

template <typename T>
struct __is_Ptr_helper <Ptr <T> > {
        enum { value = true };
};

template<typename _Tp>
struct TILIAE_API is_ptr : public boost::integral_constant<bool, (__is_Ptr_helper <typename boost::remove_cv<_Tp>::type>::value)>
  { };

/*--------------------------------------------------------------------------*/

template <typename _T, typename>
struct __remove_Ptr_helper{
        typedef _T type;
};

template <typename _T, typename _U>
struct __remove_Ptr_helper <_T, Ptr <_U> > {
        typedef _U type;
};

/// remove_pointer
template <typename _T>
struct TILIAE_API remove_ptr : public __remove_Ptr_helper<_T, typename boost::remove_cv <_T>::type>
{ };

/*--------------------------------------------------------------------------*/

template <typename _T, typename>
struct __remove_Ptrs_helper{
        typedef _T type;
};

template <typename _T, typename _U>
struct __remove_Ptrs_helper <_T, Ptr <_U> > {
        typedef _U type;
};

template <typename _T, typename _U>
struct __remove_Ptrs_helper <_T, _U*> {
        typedef _U type;
};

/// rmove_ptr + remove_pointer
template <typename _T>
struct TILIAE_API remove_ptrs : public __remove_Ptrs_helper<_T, typename boost::remove_cv <_T>::type>
{ };

/*--------------------------------------------------------------------------*/

template<typename _Tp>
  struct TILIAE_API add_ptr
  { typedef Ptr <typename boost::remove_reference<_Tp>::type> type; };

} // namespace

#endif /* PTR_H_ */
