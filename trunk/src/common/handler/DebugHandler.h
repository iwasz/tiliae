/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DEBUGHANDLER_H_
#define DEBUGHANDLER_H_

#include <string>
#include "standardTypes/VariantList.h"
#include "Variant.h"
#include "IHandler.h"

namespace Common {

/**
 * Wypisuje dany string na konsole. Probuje kastowac
 * swoje argumenty na std::string i tez je wypisze.
 *
 * Jeżeli ustwaiono wskaźnik do output, to wyniki będą
 * tam dopisywane.
 */
struct DebugHandler : public IHandler {

        DebugHandler () : output (NULL) {}
        virtual ~DebugHandler () {}

        virtual Core::Variant run (const Core::VariantList &);

        std::string getDebug () const { return debug; }
        void setDebug (std::string debug) { this->debug = debug; }

        std::string *getOutput () const { return output; }
        void setOutput (std::string *output) { this->output = output; }

private:

        std::string debug;
        std::string *output;

};

}

#endif /* DEBUGHANDLER_H_ */
