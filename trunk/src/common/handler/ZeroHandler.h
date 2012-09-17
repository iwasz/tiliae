/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ZEROHANDLER_H_
#define ZEROHANDLER_H_

#include <map>
#include <vector>
#include <string>
#include "IHandler.h"
#include "core/Pointer.h"
#include "core/variant/Variant.h"

namespace Common {

/**
 * Handler, ktorego metoda run nie przyjmuje zadnego parametru.
 */
struct ZeroHandler : public IHandler {

        ZeroHandler () : handler (NULL) {}
        virtual ~ZeroHandler () {}
        virtual Core::Variant run (const Core::VariantList &);
        virtual Core::Variant run ();

        IHandler *getHandler () const { return handler; }
        void setHandler (IHandler *handler) { this->handler = handler; }

private:

        IHandler *handler;
};

typedef std::vector <ZeroHandler *> ZeroHandlerList;
typedef std::map <std::string, ZeroHandler *> ZeroHandlerMap;

}

#endif /* ZEROHANDLER_H_ */
