/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SIMPLEIDGENERATOR_H_
#define SIMPLEIDGENERATOR_H_

#include "IIdGenerator.h"
#include "../../../core/string/String.h"

namespace Container {

extern const char *SIMPLE_ID_GENERATOR_PREFIX;

/**
 * Generator ID.
 * Generuje ID o postaci <PREFIX><NUM>, gdzie <PREFIX> to jakis
 * ustalony napis, a <NUM>, to kolejna liczba naturalna od 0.
 * \ingroup Container
 * TODO To będzie do usunięcia, kiedy MXML będzie działać. Tam używamy zwykłej metody.
 */
struct SimpleIdGenerator : public IIdGenerator {

        SimpleIdGenerator () : prefix (SIMPLE_ID_GENERATOR_PREFIX), num (0) {}
        virtual ~SimpleIdGenerator () {}

        virtual std::string generate (IMeta *) const;

private:

        std::string prefix;
        mutable int num;

};

}

#endif /* SIMPLEIDGENERATOR_H_ */
