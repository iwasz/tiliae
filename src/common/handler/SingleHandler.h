/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SINGLEHANDLER_H_
#define SINGLEHANDLER_H_

#include "IHandler.h"
#include "adapters/List.h"
#include "adapters/Map.h"
#include "standardTypes/String.h"
#include "standardTypes/VariantList.h"
#include "Variant.h"
#include "core/Pointer.h"
#include <map>
#include <vector>

namespace Common {

/**
 * Handler, ktorego metoda run nie przyjmuje zadnego parametru.
 */
struct SingleHandler : public IHandler {

        SingleHandler () : handler (NULL) {}
        virtual ~SingleHandler () {}
        virtual Core::Variant run (const Core::VariantList &);
        virtual Core::Variant run (const Core::Variant &) const;

        IHandler *getHandler () const { return handler; }
        void setHandler (IHandler *handler) { this->handler = handler; }

private:

        IHandler *handler;
};

typedef std::vector <SingleHandler *> SingleHandlerList;
typedef std::map <std::string, SingleHandler *> SingleHandlerMap;

}

#endif /* SINGLEHANDLER_H_ */
