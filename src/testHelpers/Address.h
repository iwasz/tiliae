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
#include "reflection/Reflection.h"
#include "Place.h"
#include "core/variant/Variant.h"
#include "core/ApiMacro.h"
#include <string>

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

        REFLECTION_METHOD (getStreet)          std::string getStreet () const { return street; }
        REFLECTION_METHOD (setStreet)          void setStreet (const std::string &street) { this->street = street; }

        REFLECTION_METHOD (getPostalCode)      std::string getPostalCode () const { return postalCode; }
        REFLECTION_METHOD (setPostalCode)      void setPostalCode (const std::string &postalCode) { this->postalCode = postalCode; }

        REFLECTION_METHOD (getCity)            City *getCity () const { return city; }
        REFLECTION_METHOD (setCity)            void setCity (City *city) { this->city = city; }

        REFLECTION_METHOD (getCountry)         Country *getCountry () const { return country; }
        REFLECTION_METHOD (setCountry)         void setCountry (Country *country) { this->country = country; }

        REFLECTION_METHOD (getString)          std::string getString () { return string; }
        REFLECTION_METHOD (setString)          void setString (const std::string &string) { this->string = string; }

        REFLECTION_METHOD (getProperty)        Core::Variant getProperty () const { return property; }
        REFLECTION_METHOD (setProperty)        void setProperty (const Core::Variant &p) { property = p; }

private:

        std::string street;
        std::string postalCode;
        City *city;
        Country *country;
        Core::Variant property;
        std::string string;

        REFLECTION_END (Address)
};


typedef std::list <Ptr <Address> > AddressList;
REFLECTION_COLLECTION (AddressList)

#endif

