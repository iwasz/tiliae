/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ADDRESS_H10
#define ADDRESS_H10

//#include "Address10Type.h"
#include <string>
#include "ReflectionMacros.h"

struct Address10 {
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
//        Address10Type prr_ (addressType);
        end_ (Address10)
};

#endif /* ADDRESS_H10 */
