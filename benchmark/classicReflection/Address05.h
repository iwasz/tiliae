/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ADDRESS_H05
#define ADDRESS_H05

//#include "Address05Type.h"
#include <string>
#include "ReflectionMacros.h"

struct Address05 {
        ctr__ (void)
        int prp_ (id);
        std::string prp_ (city);
        std::string prp_ (street);
        std::string prp_ (province);
        std::string prp_ (postalCode);
        std::string prp_ (country);
        std::string prp_ (streetNumber);
        std::string prp_ (building);
        std::string prp_ (unit);
//        Address05Type prr_ (addressType);
        end_ (Address05)
};

#endif /* ADDRESS_H05 */
