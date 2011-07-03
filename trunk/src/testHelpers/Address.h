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

        __c(void)
        _b ("Place")

        Address () : city (NULL), country (NULL) {}
        virtual ~Address () {}

        _m (getStreet)          Core::String getStreet () const { return street; }
        _m (setStreet)          void setStreet (const Core::String &street) { this->street = street; }

        _m (getPostalCode)      Core::String getPostalCode () const { return postalCode; }
        _m (setPostalCode)      void setPostalCode (const Core::String &postalCode) { this->postalCode = postalCode; }

        _m (getCity)            City *getCity () const { return city; }
        _m (setCity)            void setCity (City *city) { this->city = city; }

        _m (getCountry)         Country *getCountry () const { return country; }
        _m (setCountry)         void setCountry (Country *country) { this->country = country; }

        _m (getString)          Core::String getString () { return string; }
        _m (setString)          void setString (const Core::String &string) { this->string = string; }

        _m (getProperty)        Core::Variant getProperty () const { return property; }
        _m (setProperty)        void setProperty (const Core::Variant &p) { property = p; }

private:

        Core::String street;
        Core::String postalCode;
        City *city;
        Country *country;
        Core::Variant property;
        Core::String string;

        _e (Address)
};


typedef std::list <Ptr <Address> > AddressList;
_g (AddressList)

#endif

