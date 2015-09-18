/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ADDRESS_H01
#define ADDRESS_H01

//#include "Address01Type.h"
#include <string>
#include "ReflectionMacros.h"

struct Address01 {
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
//        Address01Type prr_ (addressType);
        end_ (Address01)
};

#endif /* ADDRESS_H01 */
