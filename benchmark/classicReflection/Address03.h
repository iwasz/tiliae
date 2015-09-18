/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ADDRESS_H03
#define ADDRESS_H03

//#include "Address03Type.h"
#include <string>
#include "ReflectionMacros.h"

struct Address03 {
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
//        Address03Type prr_ (addressType);
        end_ (Address03)
};

#endif /* ADDRESS_H03 */
