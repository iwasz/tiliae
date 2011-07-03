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

        __c (void)

        Contractor () : addressList (NULL), telephoneList (NULL),
                zyd (false), mason (false), plec (WOMAN), wiek (0)
        {
        }

        virtual ~Contractor () {}

        _m (getName) Core::String getName () const { return name; }
        _m (setName) void setName (const Core::String &name) { this->name = name; }

        _m (getSymbol) Core::String getSymbol () const { return symbol; }
        _m (setSymbol) void setSymbol (const Core::String &symbol) { this->symbol = symbol; }

        _m (getAddressList)  AddressList *getAddressList () const { return addressList; }
        _m (setAddressList) void setAddressList (AddressList *addressList) { this->addressList = addressList; }

        _m (getTelephoneList) TelephoneList *getTelephoneList () const { return telephoneList; }
        _m (setTelephoneList) void setTelephoneList (TelephoneList *telephoneList) { this->telephoneList = telephoneList; }

        _m (getZyd)  bool getZyd () const { return zyd; }
        _m (setZyd) void setZyd (bool zyd) { this->zyd = zyd; }

        _m (getMason) bool getMason () const { return mason; }
        _m (setMason) void setMason (bool mason) { this->mason = mason; }

        _m (getPlec) Gender getPlec () const { return plec; }
        _m (setPlec) void setPlec (Gender plec) { this->plec = plec; }

        _m (getWiek) int getWiek () const { return wiek; }
        _m (setWiek) void setWiek (int wiek) { this->wiek = wiek; }

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

        _e (Contractor)

};

#endif

