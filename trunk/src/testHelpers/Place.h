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
        c__ (void)

        virtual ~Place () {}
        m_ (init) int init () { static int cnt = 0; return ++cnt; }

        m_ (getPlace) Core::Variant getPlace () const { return place; }
        m_ (setPlace) void setPlace (const Core::Variant &p) { place = p; }

private:

        Core::Variant place;

        e_(Place)
};

#endif
