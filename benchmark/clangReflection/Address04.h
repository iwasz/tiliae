/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ADDRESS_H04
#define ADDRESS_H04

//#include "Address04Type.h"
#include <string>

struct Address04 {
        int id;
        std::string city;
        std::string street;
        std::string province;
        std::string postalCode;
        std::string country;
        std::string streetNumber;
        std::string building;
        std::string unit;
//        Address04Type prr_ (addressType);
};

#endif /* ADDRESS_H04 */
