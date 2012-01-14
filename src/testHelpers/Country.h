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

        c__ (void)

        m_ (getName) Core::String getName () const { return name; }
        m_ (setName) void setName (const Core::String &name) { this->name = name; }

private:

        Core::String name;

        e_ (Country)

};

typedef std::vector <Ptr <Country> > CountryVector;
g_ (CountryVector)

typedef std::list <Ptr <Country> > CountryList;
g_ (CountryList)

#endif

