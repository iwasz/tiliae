/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef COUNTRY_920296_H
#define COUNTRY_920296_H

#include <list>
#include "../core/string/String.h"
#include "../core/Pointer.h"
#include "Reflection.h"
#include <vector>
#include "../core/ApiMacro.h"

/****************************************************************************/

class TILIAE_API Country {
public:

        __c (void)

        _m (getName) Core::String getName () const { return name; }
        _m (setName) void setName (const Core::String &name) { this->name = name; }

private:

        Core::String name;

        _e (Country)

};

typedef std::vector <Ptr <Country> > CountryVector;
_g (CountryVector)

typedef std::list <Ptr <Country> > CountryList;
_g (CountryList)

#endif

