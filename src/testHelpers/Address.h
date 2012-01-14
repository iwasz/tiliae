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

        c__(void)
        b_ ("Place")

        Address () : city (NULL), country (NULL) {}
        virtual ~Address () {}

        m_ (getStreet)          Core::String getStreet () const { return street; }
        m_ (setStreet)          void setStreet (const Core::String &street) { this->street = street; }

        m_ (getPostalCode)      Core::String getPostalCode () const { return postalCode; }
        m_ (setPostalCode)      void setPostalCode (const Core::String &postalCode) { this->postalCode = postalCode; }

        m_ (getCity)            City *getCity () const { return city; }
        m_ (setCity)            void setCity (City *city) { this->city = city; }

        m_ (getCountry)         Country *getCountry () const { return country; }
        m_ (setCountry)         void setCountry (Country *country) { this->country = country; }

        m_ (getString)          Core::String getString () { return string; }
        m_ (setString)          void setString (const Core::String &string) { this->string = string; }

        m_ (getProperty)        Core::Variant getProperty () const { return property; }
        m_ (setProperty)        void setProperty (const Core::Variant &p) { property = p; }

private:

        Core::String street;
        Core::String postalCode;
        City *city;
        Country *country;
        Core::Variant property;
        Core::String string;

        e_ (Address)
};


typedef std::list <Ptr <Address> > AddressList;
g_ (AddressList)

#endif

