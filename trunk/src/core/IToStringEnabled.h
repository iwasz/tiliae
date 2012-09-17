/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ITOSTRINGENABLED_H_
#define ITOSTRINGENABLED_H_

#include <iosfwd>
#include <string>
#include "core/ApiMacro.h"

namespace Core {

/**
 * Interfejs pomocniczy z metodą dającą napisową informację. To jest na wzór Javowego
 * Object.toString.
 * \ingroup CoreAPI
 */
struct TILIAE_API IToStringEnabled {

        virtual ~IToStringEnabled () {}
        virtual std::string toString () const = 0;

};

extern TILIAE_API std::ostream &operator<< (std::ostream &o, const Core::IToStringEnabled &fld);

}//namespace

#	endif /* ITOSTRINGENABLED_H_ */
