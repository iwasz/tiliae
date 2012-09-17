/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include "core/IToStringEnabled.h"

/****************************************************************************/

std::ostream &operator<< (std::ostream &o, const Core::IToStringEnabled &fld)
{
        o << fld.toString ();
        return o;
}


