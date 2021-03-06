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
#include "reflection/Reflection.h"
#include <string>
#include "core/ApiMacro.h"

/****************************************************************************/

class TILIAE_API __tiliae_reflect__ Telephone  {
public:

        REFLECTION_CONSTRUCTOR_ (const std::string &);
        Telephone (const std::string &n) : name (n) {}

        REFLECTION_METHOD (getName) std::string getName () const { return name; }
        REFLECTION_METHOD (setName) void setName (const std::string &name) { this->name = name; }

private:

        std::string name;

        REFLECTION_END (Telephone)

};

/****************************************************************************/

typedef __tiliae_reflect__ std::list <Ptr <Telephone> > TelephoneList;
REFLECTION_COLLECTION(TelephoneList)

#endif

