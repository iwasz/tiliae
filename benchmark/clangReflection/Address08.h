/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ADDRESS_H08
#define ADDRESS_H08

//#include "Address08Type.h"
#include <string>

struct Address08 {
        int id;
        std::string city;
        std::string street;
        std::string province;
        std::string postalCode;
        std::string country;
        std::string streetNumber;
        std::string building;
        std::string unit;
//        Address08Type prr_ (addressType);
};

#endif /* ADDRESS_H08 */
