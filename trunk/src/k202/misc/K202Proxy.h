/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef K202EXECUTOR_H_
#define K202EXECUTOR_H_

#include <K202.h>
#include <Reflection.h>
#include "../../core/ApiMacro.h"

namespace k202 {

/**
 * Helper class. Executes custom query. Does not store
 * Script object.
 */
class TILIAE_API K202Proxy {
public:
        c__ (void)

        virtual ~K202Proxy () {}

        m_ (run)
        Core::Variant run ()
        {
                return k202::K202::instance ()->run (sourceCode, domain, paramVector, argsMap);
        }

        std::string getSourceCode () const { return sourceCode; }
        m_ (setSourceCode) void setSourceCode (std::string sourceCode) { this->sourceCode = sourceCode; }

        const Core::Variant &getDomain () { return domain; }
        m_ (setDomain) void setDomain (const Core::Variant &d) { domain = d; }

        const Core::VariantVector &getParamVector () const { return paramVector; }
        m_ (setParamVector) void setParamVector (const Core::VariantVector &paramVector) { this->paramVector = paramVector; }

        const Core::VariantMap &getArgsMap () const { return argsMap; }
        m_ (setArgsMap) void setArgsMap (const Core::VariantMap &map) { argsMap = map; }

private:

        std::string sourceCode;
        Core::Variant domain;
        Core::VariantVector paramVector;
        Core::VariantMap argsMap;

        e_ (K202Proxy)
};

}

#endif /* K202EXECUTOR_H_ */
