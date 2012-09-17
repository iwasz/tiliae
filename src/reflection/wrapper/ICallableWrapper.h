/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ICALLABLE_WRAPPER_H_
#define ICALLABLE_WRAPPER_H_

#include <typeinfo>
#include "core/variant/Variant.h"
#include "core/Typedefs.h"

namespace Reflection {

/**
 * Interfejs wrapperów metod, których argumenty i wartość zwracana są wariantami. Czyli
 * klasy konkretne tego interfejsu mają metodę call  ktora przyjmuje warianty jako argumenty,
 * wywołuje wrapowaną metodę i zwraca jej wynik w postaci warianta. Klasy konkretne tego
 * interfejsu zwracają też informację dodatkową w postaci type_info const *. Jest to jeden
 * wskaźnik do type_info i jego znaczenie jest zależne od konkretnej klasy.
 *
 * Pobieranie metod za pomocą getMethod jest tylko w:
 * - GetPutMethodRWBeanWrapperPlugin.cc
 * - ReflectionTools.cc
 */
struct ICallableWrapper {
        virtual ~ICallableWrapper () {}

        /**
         * Wywołanie wrapowanej metody.
         */
        virtual Core::Variant call (Core::Variant const &object, Core::VariantVector *args) = 0;

        /**
         * Zwraca jeden obiekt type_info. Ten obiekt służy do rozróżniania metod - prócz nazwy
         * jest dodatkową informacja o metodzie. Znaczenie tego type_info jest zalezne od konkretnej
         * klasy implementującej ICallableWrapper.
         */
        virtual std::type_info const &getType () const = 0;

        /**
         * Liczba argumentów.
         */
        virtual unsigned int getArity () const = 0;
};

} //name

#endif /* ICALLABLEWRAPPER_H_ */
