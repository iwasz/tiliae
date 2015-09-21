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

struct Address10 {
	Address10(int) {}
        int id;
        std::string city;
        std::string street;
        std::string province;
        std::string postalCode;
        std::string country;
        std::string streetNumber;
        std::string building;
        std::string unit;
//        Address10Type prr_ (addressType);
};

#endif /* ADDRESS_H10 */
