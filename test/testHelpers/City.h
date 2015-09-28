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
#include "reflection/Reflection.h"
#include <string>
#include <vector>
#include "core/ApiMacro.h"

class TILIAE_API __tiliae_reflect__ City {
public:

        REFLECTION_CONSTRUCTOR_ (void)
        City () {}

        REFLECTION_CONSTRUCTOR (std::string const &)
        City (std::string const &n) : name (n) {}

        ~City () {}

        REFLECTION_METHOD (init) void init () { name += "_INIT"; }
        REFLECTION_METHOD (initThrow) void initThrow () { throw Core::Exception ("aaa"); }

        REFLECTION_METHOD (getName) std::string getName () const { return name; }
        REFLECTION_METHOD (setName) void setName (const std::string &name) { this->name = name; }

private:

        std::string name;

        REFLECTION_END (City)

};

typedef std::vector <City *> CityVector;
REFLECTION_COLLECTION_NAME (CityVector, "CityVector")

typedef std::list <City *> CityList;
REFLECTION_COLLECTION_NAME (CityList, "CityList")

typedef std::map <std::string, City *> CityMap;
REFLECTION_COLLECTION (CityMap)

#endif

