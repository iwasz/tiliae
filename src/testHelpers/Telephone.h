/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TELEPHONE_633075_H
#define TELEPHONE_633075_H

#include <list>
#include "Reflection.h"
#include "../core/string/String.h"
#include "../core/ApiMacro.h"

/****************************************************************************/

class TILIAE_API Telephone  {
public:

        __c (const std::string &);
        Telephone (const std::string &n) : name (n) {}

        _m (getName) std::string getName () const { return name; }
        _m (setName) void setName (const std::string &name) { this->name = name; }

private:

        std::string name;

        _e (Telephone)

};

/****************************************************************************/

typedef std::list <Ptr <Telephone> > TelephoneList;
_g(TelephoneList)

#endif

