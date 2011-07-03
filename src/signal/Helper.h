/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef _SIG_HELPER_H_
#define _SIG_HELPER_H_

#include <path/Path.h>

namespace Signal {

/**
 * Metody pomocnicze.
 * \ingroup Signal
 */
struct Helper {

        static bool isRelativeOneSegment (const Common::Path &p);
        static bool isAbsoluteMultiSegment (const Common::Path &p);

};

}

#endif /* HELPER_H_ */
