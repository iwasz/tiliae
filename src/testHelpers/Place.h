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
        REFLECTION_CONSTRUCTOR_ (void)

        virtual ~Place () {}
        REFLECTION_METHOD (init) int init () { static int cnt = 0; return ++cnt; }
        REFLECTION_METHOD (init2) int init2 () { static int cnt2 = 0; return ++cnt2; }

        REFLECTION_METHOD (getPlace) Core::Variant getPlace () const { return place; }
        REFLECTION_METHOD (setPlace) void setPlace (const Core::Variant &p) { place = p; }

private:

        Core::Variant place;

        REFLECTION_END(Place)
};

#endif
