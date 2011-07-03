/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IIDGENERATOR_H_
#define IIDGENERATOR_H_

#include "../../../core/string/String.h"

namespace Container {
class IMeta;

/**
 * Klasa obiektów generujących ID.
 * \ingroup Container
 */
struct IIdGenerator {
        virtual ~IIdGenerator () {}
        virtual std::string generate (IMeta *) const = 0;
};

}

#endif /* IIDGENERATOR_H_ */
