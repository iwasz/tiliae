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

        c__ (void)
        City () {}

        c_ (std::string const &)
        City (std::string const &n) : name (n) {}

        virtual ~City () {}

        m_ (init) void init () { name += "_INIT"; }

        m_ (getName) std::string getName () const { return name; }
        m_ (setName) void setName (const std::string &name) { this->name = name; }

private:

        std::string name;

        e_ (City)

};

typedef std::vector <Ptr <City> > CityVector;
_gn (CityVector, "CityVector")

typedef std::list <Ptr <City> > CityList;
_gn (CityList, "CityList")

typedef std::map <std::string, Ptr <City> > CityMap;
g_ (CityMap)

#endif

