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
class MetaObject;

/**
 * Klasa obiektów generujących ID.
 * \ingroup Container
 */
struct IIdGenerator {
        virtual ~IIdGenerator () {}
        virtual std::string generate (MetaObject *) const = 0;
};

}

#endif /* IIDGENERATOR_H_ */
