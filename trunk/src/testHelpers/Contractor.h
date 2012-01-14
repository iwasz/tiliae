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
#include "Reflection.h"
#include "../core/string/String.h"
#include "../core/ApiMacro.h"

/**
 *  Firma
 */
class TILIAE_API Contractor {
public:

        c__ (void)

        Contractor () : addressList (NULL), telephoneList (NULL),
                zyd (false), mason (false), plec (WOMAN), wiek (0)
        {
        }

        virtual ~Contractor () {}

        m_ (getName) Core::String getName () const { return name; }
        m_ (setName) void setName (const Core::String &name) { this->name = name; }

        m_ (getSymbol) Core::String getSymbol () const { return symbol; }
        m_ (setSymbol) void setSymbol (const Core::String &symbol) { this->symbol = symbol; }

        m_ (getAddressList)  AddressList *getAddressList () const { return addressList; }
        m_ (setAddressList) void setAddressList (AddressList *addressList) { this->addressList = addressList; }

        m_ (getTelephoneList) TelephoneList *getTelephoneList () const { return telephoneList; }
        m_ (setTelephoneList) void setTelephoneList (TelephoneList *telephoneList) { this->telephoneList = telephoneList; }

        m_ (getZyd)  bool getZyd () const { return zyd; }
        m_ (setZyd) void setZyd (bool zyd) { this->zyd = zyd; }

        m_ (getMason) bool getMason () const { return mason; }
        m_ (setMason) void setMason (bool mason) { this->mason = mason; }

        m_ (getPlec) Gender getPlec () const { return plec; }
        m_ (setPlec) void setPlec (Gender plec) { this->plec = plec; }

        m_ (getWiek) int getWiek () const { return wiek; }
        m_ (setWiek) void setWiek (int wiek) { this->wiek = wiek; }

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

        e_ (Contractor)

};

#endif

