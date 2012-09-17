/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IHANDLER_H_
#define IHANDLER_H_

#include "core/variant/Variant.h"
#include "core/Typedefs.h"
#include <vector>

namespace Common {

/**
 * No to jest Handler, czyli w ogolnosci obiekty tej klasy
 * sa wolane w roznych nieoczekiwanych momentach :) Implementuja
 * jakies akcje, ktore maja sie wowczas wykonac.
 */
struct IHandler {

        virtual ~IHandler () {}
        virtual Core::Variant run (const Core::VariantList &) = 0;
};

/**
 * Mapa handlerów.
 */
typedef std::vector <IHandler *> HandlerList;

}

#endif /* IHANDLER_H_ */
