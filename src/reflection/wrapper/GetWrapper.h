/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GETWRAPPER_H_
#define GETWRAPPER_H_

#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <set>

#include "../../core/variant/Variant.h"
#include "../wrapper/ICallableWrapper.h"
#include "../../core/Typedefs.h"
#include "WrapperCommons.h"

namespace Reflection {

/**
 * Wrappery do pobierania elementow kolekcji. Jest to seria wrapperów do kolekcji
 * STL (ale można je rozszerzyć o inne typy), które umożliwiają pobieranie elementu
 * (stąd nazwa Get) z wrapowanej kolekcji. Interfejs jest oczywiście typu ICallableWrapper.
 */
template <typename T>
struct GetWrapper {};

/**
 * Wymaga unsigned int jako indexu.
 */
template <typename T>
struct GetWrapper <std::vector<T> > : public ICallableWrapper {

        virtual ~GetWrapper () {}
        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T>::type); }
        unsigned int getArity () const { return 1; }
};

template <typename T>
Core::Variant GetWrapper <std::vector<T> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        unsigned int idx = lcast <unsigned int> (args->front ());
        std::vector<T> const *vec = vcast <std::vector<T> const *> (object);
        checkCollectionSize (idx, vec->size ());
        return Core::Variant ((*vec)[idx]);
}

/****************************************************************************/

template <typename T>
struct GetWrapper <std::list<T> > : public ICallableWrapper {

        virtual ~GetWrapper () {}
        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T>::type); }
        unsigned int getArity () const { return 1; }
};

template <typename T>
Core::Variant GetWrapper <std::list<T> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        unsigned int idx = lcast <unsigned int> (args->front ());
        std::list<T> const *list = vcast <std::list<T> const *> (object);
        checkCollectionSize (idx, list->size ());
        typename std::list<T>::const_iterator i = list->begin ();
        std::advance (i, idx);
        return Core::Variant (*i);
}

/**
 * Dla map.
 */
template <typename K, typename V>
struct GetWrapper <std::map<K, V> > : public ICallableWrapper {

        virtual ~GetWrapper () {}
        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<V>::type); }
        unsigned int getArity () const { return 1; }
};

template <typename K, typename V>
Core::Variant GetWrapper <std::map<K, V> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        std::map<K, V> const *map = vcast <std::map<K, V> const *> (object);
        typename std::map<K, V>::const_iterator i = map->find (lcast <K> (args->front ()));
        if (i == map->end ()) {
                return Core::Variant ();
        }
        return Core::Variant (i->second);
}

/**
 * Dla setów.
 */
template <typename T>
struct GetWrapper <std::set <T> > : public ICallableWrapper {

        virtual ~GetWrapper () {}
        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T>::type); }
        unsigned int getArity () const { return 1; }
};

template <typename T>
Core::Variant GetWrapper <std::set <T> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        std::set<T> const *set = vcast <std::set<T> const *> (object);
        typename std::set <T>::const_iterator i = set->find (vcast <T> (args->front ()));
        if (i == set->end ()) {
                return Core::Variant ();
        }
        return Core::Variant (*i);
}

} // nam

#endif /* GETWRAPPER_H_ */
