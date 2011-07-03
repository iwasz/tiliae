/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SETWRAPPER_H_
#define SETWRAPPER_H_

#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <set>

#include "../../core/variant/Variant.h"
#include "../wrapper/ICallableWrapper.h"
#include "../../core/Typedefs.h"
#include "WrapperCommons.h"
#include "../../core/variant/Cast.h"

namespace Reflection {

/**
 * Wrappery do ustawiania elementow kolekcji. Jest to seria wrapperów do kolekcji
 * STL (ale można je rozszerzyć o inne typy), które umożliwiają ustawianie elementu
 * (stąd nazwa Set) do wrapowanej kolekcji. Interfejs jest oczywiście typu ICallableWrapper.
 */
template <typename T>
struct SetWrapper {};

/**
 * Wrapper dla wektorów. Wymaga unsigned int jako indexu.
 */
template <typename T>
struct SetWrapper <std::vector<T> > : public ICallableWrapper {

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T>::type); }
        unsigned int getArity () const { return 2; }
};

/*--------------------------------------------------------------------------*/

template <typename T>
Core::Variant SetWrapper <std::vector<T> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 2);
        std::vector<T> *vec = vcast <std::vector<T> *> (object);
        Core::VariantVector::iterator i = args->begin ();
        unsigned int idx = lcast <unsigned int> (*i++);
        checkCollectionSize (idx, vec->size ());
        (*vec)[idx] = vcast <T> (*i);
        return Core::Variant ();
}

/**
 * Wrapper dla wektorów. Wymaga unsigned int jako indexu.
 */
template <typename T>
struct SetWrapper <std::list<T> > : public ICallableWrapper {

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T>::type); }
        unsigned int getArity () const { return 2; }
};

/*--------------------------------------------------------------------------*/

template <typename T>
Core::Variant SetWrapper <std::list<T> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 2);
        std::list <T> *list = vcast <std::list <T> *> (object);
        Core::VariantVector::iterator i = args->begin ();
        unsigned int idx = lcast <unsigned int> (*i++);
        checkCollectionSize (idx, list->size ());
        typename std::list<T>::iterator listI = list->begin ();
        std::advance (listI, idx);
        *listI = vcast <T> (*i);
        return Core::Variant ();
}

/**
 * Dla map.
 */
template <typename K, typename V>
struct SetWrapper <std::map<K, V> > : public ICallableWrapper {

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<V>::type); }
        unsigned int getArity () const { return 2; }
};

template <typename K, typename V>
Core::Variant SetWrapper <std::map<K, V> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 2);
        std::map <K, V> *map = vcast <std::map <K, V> *> (object);
        Core::VariantVector::iterator k = args->begin ();
        Core::VariantVector::iterator v = k + 1;
        map->operator[] (lcast <K> (*k)) = vcast <V> (*v);
        return Core::Variant ();
}

}// namespace

#	endif /* SETWRAPPER_H_ */
