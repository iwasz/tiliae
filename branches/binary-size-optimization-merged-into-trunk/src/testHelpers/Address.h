/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ADDRESS_100A408_H
#define ADDRESS_100A408_H

#include <list>
#include "Reflection.h"
#include "Place.h"
#include "../core/string/String.h"
#include "../core/variant/Variant.h"
#include "../core/ApiMacro.h"

class City;
class Country;

/**
 *  Obiekt domeny : adres - no taki pocztowy.
 */
class TILIAE_API Address : public Place {
public:

        REFLECTION_CONSTRUCTOR_(void)
        REFLECTION_BASE_CLASS ("Place")

        Address () : city (NULL), country (NULL) {}
        virtual ~Address () {}

        REFLECTION_METHOD (getStreet)          Core::String getStreet () const { return street; }
        REFLECTION_METHOD (setStreet)          void setStreet (const Core::String &street) { this->street = street; }

        REFLECTION_METHOD (getPostalCode)      Core::String getPostalCode () const { return postalCode; }
        REFLECTION_METHOD (setPostalCode)      void setPostalCode (const Core::String &postalCode) { this->postalCode = postalCode; }

        REFLECTION_METHOD (getCity)            City *getCity () const { return city; }
        REFLECTION_METHOD (setCity)            void setCity (City *city) { this->city = city; }

        REFLECTION_METHOD (getCountry)         Country *getCountry () const { return country; }
        REFLECTION_METHOD (setCountry)         void setCountry (Country *country) { this->country = country; }

        REFLECTION_METHOD (getString)          Core::String getString () { return string; }
        REFLECTION_METHOD (setString)          void setString (const Core::String &string) { this->string = string; }

        REFLECTION_METHOD (getProperty)        Core::Variant getProperty () const { return property; }
        REFLECTION_METHOD (setProperty)        void setProperty (const Core::Variant &p) { property = p; }

private:

        Core::String street;
        Core::String postalCode;
        City *city;
        Country *country;
        Core::Variant property;
        Core::String string;

        REFLECTION_END (Address)
};


typedef std::list <Ptr <Address> > AddressList;
REFLECTION_COLLECTION (AddressList)

#endif

