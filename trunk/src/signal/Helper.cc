/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Helper.h"

namespace Signal {


bool Helper::isRelativeOneSegment (const Common::Path &p)
{
        return p.isRelative () && (p.countSegments() == 1);
}

bool Helper::isAbsoluteMultiSegment (const Common::Path &p)
{
        return p.isAbsolute() &&  (p.countSegments() > 1);
}

}
