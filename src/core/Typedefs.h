/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include <list>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <boost/foreach.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/add_reference.hpp>

#include "string/String.h"
#include "variant/Variant.h"
#include "../core/Pointer.h"

#define foreach BOOST_FOREACH

namespace Core{

#if 1
typedef std::list <std::string> StringList;
typedef std::vector <std::string> StringVector;
typedef std::set <std::string> StringSet;
typedef std::map <std::string, std::string> StringMap;

typedef std::list <Core::String> UStringList;
typedef std::vector <Core::String> UStringVector;
typedef std::set <Core::String> UStringSet;
typedef std::map <std::string, Core::String> UStringMap;
#else
typedef std::list <std::string> StdStringList;
typedef std::vector <std::string> StdStringVector;
typedef std::set <std::string> StdStringSet;
// TODO Uwaga, klucz ma być std:string - kiedy BeanWrapper będzie działał na std::stringach!
typedef std::map <Core::String, std::string> StdStringMap;

typedef std::list <Core::String> StringList;
typedef std::vector <Core::String> StringVector;
typedef std::set <Core::String> StringSet;
typedef std::map <Core::String, Core::String> StringMap;
#endif

typedef std::list <Core::Variant> VariantList;
typedef std::vector <Core::Variant> VariantVector;
typedef std::map <std::string, Core::Variant> VariantMap;

typedef std::vector <std::type_info const *> TypeList;

/**
 * To daje typ z któego można potem zrobić znormalizowane type_info. Usuwa CV i
 * usuwa wskaźnik (1).
 */
template <typename T>
struct normalize {
        typedef typename boost::add_reference <
                typename boost::remove_cv <
                typename Core::remove_ptrs <
                typename boost::remove_reference <T>::type>::type>::type>::type type;
};

} // namespace

#	endif /* TYPEDEFS_H_ */
