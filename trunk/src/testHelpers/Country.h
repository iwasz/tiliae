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
#include "core/string/String.h"
#include "core/Pointer.h"
#include "reflection/Reflection.h"
#include <vector>
#include "core/ApiMacro.h"

/****************************************************************************/

class TILIAE_API Country {
public:

        REFLECTION_CONSTRUCTOR_ (void)

        REFLECTION_METHOD (getName) Core::String getName () const { return name; }
        REFLECTION_METHOD (setName) void setName (const Core::String &name) { this->name = name; }

private:

        Core::String name;

        REFLECTION_END (Country)

};

typedef std::vector <Ptr <Country> > CountryVector;
REFLECTION_COLLECTION (CountryVector)

typedef std::list <Ptr <Country> > CountryList;
REFLECTION_COLLECTION (CountryList)

#endif

