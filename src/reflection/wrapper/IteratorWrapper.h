/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ITER_WRAPPER_H_
#define ITER_WRAPPER_H_

#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <set>
#include <boost/make_shared.hpp>

#include "core/variant/Variant.h"
#include "reflection/wrapper/ICallableWrapper.h"
#include "core/Typedefs.h"
#include "WrapperCommons.h"
#include "core/Iterator.h"

using Core::TIterator;

namespace Reflection {

/**
 * Wrappery do pobierania iteratora dp kolekcji. Jest to seria wrapperów do kolekcji
 * STL (ale można je rozszerzyć o inne typy), które umożliwiają pobieranie iteratora
 * z wrapowanej kolekcji. Interfejs jest oczywiście typu ICallableWrapper.
 */
template <typename T>
struct IteratorWrapper {};

/**
 *
 */
template <typename T>
struct IteratorWrapper <std::vector<T> > : public ICallableWrapper {

        virtual ~IteratorWrapper () {}
        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T>::type); }
        unsigned int getArity () const { return 0; }
};

template <typename T>
Core::Variant IteratorWrapper <std::vector<T> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        std::vector<T> const *vec = vcast <std::vector<T> const *> (object);
        return Core::Variant (std::make_shared <TIterator <std::vector <T> > > (vec->begin (), vec->end ()));
}

/****************************************************************************/

template <typename T>
struct IteratorWrapper <std::list <T> > : public ICallableWrapper {

        virtual ~IteratorWrapper () {}
        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T>::type); }
        unsigned int getArity () const { return 0; }
};

template <typename T>
Core::Variant IteratorWrapper <std::list <T> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        std::list<T> const *vec = vcast <std::list<T> const *> (object);
        return Core::Variant (std::make_shared <TIterator <std::list <T> > > (vec->begin (), vec->end ()));
}

/****************************************************************************/

template <typename T>
struct IteratorWrapper <std::set<T> > : public ICallableWrapper {

        virtual ~IteratorWrapper () {}
        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T>::type); }
        unsigned int getArity () const { return 0; }
};

template <typename T>
Core::Variant IteratorWrapper <std::set <T> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        std::set<T> const *vec = vcast <std::set<T> const *> (object);
        return Core::Variant (std::make_shared <TIterator <std::set <T> > > (vec->begin (), vec->end ()));
}

/****************************************************************************/

template <typename K, typename V>
struct IteratorWrapper <std::map <K, V> > : public ICallableWrapper {

        virtual ~IteratorWrapper () {}
        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<V>::type); }
        unsigned int getArity () const { return 0; }
};

template <typename K, typename V>
Core::Variant IteratorWrapper <std::map <K, V> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        std::map <K, V> const *vec = vcast <std::map <K, V> const *> (object);
        return Core::Variant (std::make_shared <TIterator <std::map <K, V> > > (vec->begin (), vec->end ()));
}

} // nam

#endif /* GETWRAPPER_H_ */
