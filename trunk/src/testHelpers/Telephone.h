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

        c__ (const std::string &);
        Telephone (const std::string &n) : name (n) {}

        m_ (getName) std::string getName () const { return name; }
        m_ (setName) void setName (const std::string &name) { this->name = name; }

private:

        std::string name;

        e_ (Telephone)

};

/****************************************************************************/

typedef std::list <Ptr <Telephone> > TelephoneList;
g_(TelephoneList)

#endif

