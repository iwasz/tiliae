/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TTEE_ADDSETWRAPPER_H_
#define TTEE_ADDSETWRAPPER_H_

#include <vector>
#include <list>
#include <iterator>
#include <set>

#include "../../core/variant/Variant.h"
#include "../wrapper/ICallableWrapper.h"
#include "../../core/Typedefs.h"
#include "WrapperCommons.h"

namespace Reflection {

/**
 * Wrappery do ustawiania elementow kolekcji. Jest to seria wrapperów do kolekcji
 * STL (ale można je rozszerzyć o inne typy), które umożliwiają ustawianie elementu
 * (stąd nazwa Set) do wrapowanej kolekcji. Interfejs jest oczywiście typu ICallableWrapper.
 */
template <typename T>
struct AddWrapper {};

/**
 * Wrapper dla wektorów. Wymaga unsigned int jako indexu.
 */
template <typename T>
struct AddWrapper <std::vector<T> > : public ICallableWrapper {

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T>::type); }
        unsigned int getArity () const { return 1; }
};

/*--------------------------------------------------------------------------*/

template <typename T>
Core::Variant AddWrapper <std::vector<T> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        std::vector<T> *vec = vcast <std::vector<T> *> (object);
        vec->push_back (ocast <T> (args->front ()));
        return Core::Variant ();
}

/**
 * Wrapper dla wektorów. Wymaga unsigned int jako indexu.
 */
template <typename T>
struct AddWrapper <std::list<T> > : public ICallableWrapper {

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T>::type); }
        unsigned int getArity () const { return 1; }
};

/*--------------------------------------------------------------------------*/

template <typename T>
Core::Variant AddWrapper <std::list<T> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        std::list <T> *list = vcast <std::list <T> *> (object);
        list->push_back (ocast <T> (args->front ()));
        return Core::Variant ();
}

/**
 * Dla setów.
 */
template <typename K>
struct AddWrapper <std::set <K> > : public ICallableWrapper {

        Core::Variant call (Core::Variant const &object, Core::VariantVector *args);
        std::type_info const &getType () const { return typeid (typename Core::normalize<K>::type); }
        unsigned int getArity () const { return 1; }
};

template <typename K>
Core::Variant AddWrapper <std::set <K> >::call (Core::Variant const &object, Core::VariantVector *args)
{
        checkArgList (args, 1);
        std::set <K> *set = vcast <std::set <K> *> (object);
        set->insert (ocast <K> (args->front ()));
        return Core::Variant ();
}

}// namespace

#	endif /* SETWRAPPER_H_ */
