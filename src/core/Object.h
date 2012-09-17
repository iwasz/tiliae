/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef OBJECT_539568_H
#define OBJECT_539568_H

#include "core/ApiMacro.h"

namespace Core {

/**
 * Klasa pomocnicza do polimorficznego ocast.
 * Ta klasa spelnia podobne zadanie do klasy Object w Javie. Wspolna struktura
 * dziedziczenia umozliwia dynamic_castowanie i wiele innych fajnych dynamicznych
 * trikow.
 * Object ma tez specjalne znaczenie dla Variant i vcast. Kiedy Variant
 * przechowuje cos co dziedziczy z Object, to vcast potrafi dokonac
 * dynamic_cast i rzutowac z variant na typ inny niz aktualny typ uzyty do
 * zainicjowania warianta.
 * \ingroup CoreAPI
 */
class TILIAE_API Object {
public:

        virtual ~Object () {}

};

} // namespace

#endif

