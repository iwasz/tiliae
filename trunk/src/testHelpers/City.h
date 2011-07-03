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

        __c (void)
        City () {}

        _c (std::string const &)
        City (std::string const &n) : name (n) {}

        virtual ~City () {}

        _m (init) void init () { name += "_INIT"; }

        _m (getName) std::string getName () const { return name; }
        _m (setName) void setName (const std::string &name) { this->name = name; }

private:

        std::string name;

        _e (City)

};

typedef std::vector <Ptr <City> > CityVector;
_gn (CityVector, "CityVector")

typedef std::list <Ptr <City> > CityList;
_gn (CityList, "CityList")

typedef std::map <std::string, Ptr <City> > CityMap;
_g (CityMap)

#endif

