/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PLACESS_100408_H
#define PLACESS_100408_H

#include "Reflection.h"
#include "../core/string/String.h"
#include "../core/variant/Variant.h"
#include "../core/ApiMacro.h"

/**
 * Klasa bazowa dla adresu : do testów.
 */
class TILIAE_API Place : public Core::Object {
public:
        __c (void)

        virtual ~Place () {}
        _m (init) int init () { static int cnt = 0; return ++cnt; }

        _m (getPlace) Core::Variant getPlace () const { return place; }
        _m (setPlace) void setPlace (const Core::Variant &p) { place = p; }

private:

        Core::Variant place;

        _e(Place)
};

#endif
