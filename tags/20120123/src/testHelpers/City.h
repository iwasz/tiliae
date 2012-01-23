/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CITY_633075_H
#define CITY_633075_H

#include <list>
#include <map>
#include "Reflection.h"
#include "../core/string/String.h"
#include <vector>
#include "../core/ApiMacro.h"

class TILIAE_API City {
public:

        REFLECTION_CONSTRUCTOR_ (void)
        City () {}

        REFLECTION_CONSTRUCTOR (std::string const &)
        City (std::string const &n) : name (n) {}

        virtual ~City () {}

        REFLECTION_METHOD (init) void init () { name += "_INIT"; }

        REFLECTION_METHOD (getName) std::string getName () const { return name; }
        REFLECTION_METHOD (setName) void setName (const std::string &name) { this->name = name; }

private:

        std::string name;

        REFLECTION_END (City)

};

typedef std::vector <Ptr <City> > CityVector;
_gn (CityVector, "CityVector")

typedef std::list <Ptr <City> > CityList;
_gn (CityList, "CityList")

typedef std::map <std::string, Ptr <City> > CityMap;
REFLECTION_COLLECTION (CityMap)

#endif

