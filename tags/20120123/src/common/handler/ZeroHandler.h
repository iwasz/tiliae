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
#include <list>
#include <string>
#include "IHandler.h"
#include "../../core/Pointer.h"
#include "../../core/variant/Variant.h"

namespace Common {

/**
 * Handler, ktorego metoda run nie przyjmuje zadnego parametru.
 */
struct ZeroHandler : public IHandler {

        virtual ~ZeroHandler () {}
        virtual Core::Variant run (const Core::VariantList &);
        virtual Core::Variant run ();

        Ptr <IHandler> getHandler () const { return handler; }
        void setHandler (Ptr <IHandler> handler) { this->handler = handler; }

private:

        Ptr <IHandler> handler;
};

typedef std::list <ZeroHandler *> ZeroHandlerList;
typedef std::map <std::string, Ptr <ZeroHandler> > ZeroHandlerMap;

}

#endif /* ZEROHANDLER_H_ */
