/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONTRACTOR_213672_H
#define CONTRACTOR_213672_H

#include "Note.h"
#include "Address.h"
#include "Telephone.h"
#include "Gender.h"
#include "reflection/Reflection.h"
#include "core/string/String.h"
#include "core/ApiMacro.h"

/**
 *  Firma
 */
class TILIAE_API Contractor {
public:

        REFLECTION_CONSTRUCTOR_ (void)

        Contractor () : addressList (NULL), telephoneList (NULL),
                zyd (false), mason (false), plec (WOMAN), wiek (0)
        {
        }

        virtual ~Contractor () {}

        REFLECTION_METHOD (getName) Core::String getName () const { return name; }
        REFLECTION_METHOD (setName) void setName (const Core::String &name) { this->name = name; }

        REFLECTION_METHOD (getSymbol) Core::String getSymbol () const { return symbol; }
        REFLECTION_METHOD (setSymbol) void setSymbol (const Core::String &symbol) { this->symbol = symbol; }

        REFLECTION_METHOD (getAddressList)  AddressList *getAddressList () const { return addressList; }
        REFLECTION_METHOD (setAddressList) void setAddressList (AddressList *addressList) { this->addressList = addressList; }

        REFLECTION_METHOD (getTelephoneList) TelephoneList *getTelephoneList () const { return telephoneList; }
        REFLECTION_METHOD (setTelephoneList) void setTelephoneList (TelephoneList *telephoneList) { this->telephoneList = telephoneList; }

        REFLECTION_METHOD (getZyd)  bool getZyd () const { return zyd; }
        REFLECTION_METHOD (setZyd) void setZyd (bool zyd) { this->zyd = zyd; }

        REFLECTION_METHOD (getMason) bool getMason () const { return mason; }
        REFLECTION_METHOD (setMason) void setMason (bool mason) { this->mason = mason; }

        REFLECTION_METHOD (getPlec) Gender getPlec () const { return plec; }
        REFLECTION_METHOD (setPlec) void setPlec (Gender plec) { this->plec = plec; }

        REFLECTION_METHOD (getWiek) int getWiek () const { return wiek; }
        REFLECTION_METHOD (setWiek) void setWiek (int wiek) { this->wiek = wiek; }

private:

        Core::String name;
        Core::String symbol;

        /**
         *  Lista adresikow.
         */
        AddressList *addressList;

        /**
         *  Lista adresikow.
         */
        TelephoneList *telephoneList;

        bool zyd;
        bool mason;

        Gender plec;

        int wiek;

        REFLECTION_END (Contractor)

};

#endif

