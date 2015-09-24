/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ADDRESS_H_
#define ADDRESS_H_

//#include "AddressType.h"
#include <string>


#define reflect /**__tiliae_reflect__*/


#define tilref __attribute__((annotate("__reflect__")))


struct tilref Address {
//        Address () {}
//        Address (int i) {}
//        Address (double d, float f) {}
        int id;
        std::string city;
        std::string street;
        std::string province;
        std::string postalCode;
        std::string country;
        std::string streetNumber;
        std::string building;
        std::string unit;
        int func (int a, int b, int c) { return 0; }
        void fun (int i) {}
        //        AddressType prr_ (addressType);
};

#endif /* ADDRESS_H_ */
