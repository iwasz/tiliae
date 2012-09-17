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
#include "reflection/Reflection.h"
#include "core/ApiMacro.h"

namespace k202 {

/**
 * Helper class. Executes custom query. Does not store
 * Script object.
 */
class TILIAE_API K202Proxy {
public:
        REFLECTION_CONSTRUCTOR_ (void)

        virtual ~K202Proxy () {}

        REFLECTION_METHOD (run)
        Core::Variant run ()
        {
                return k202::K202::instance ()->run (sourceCode, domain, paramVector, argsMap);
        }

        std::string getSourceCode () const { return sourceCode; }
        REFLECTION_METHOD (setSourceCode) void setSourceCode (std::string sourceCode) { this->sourceCode = sourceCode; }

        const Core::Variant &getDomain () { return domain; }
        REFLECTION_METHOD (setDomain) void setDomain (const Core::Variant &d) { domain = d; }

        const Core::VariantVector &getParamVector () const { return paramVector; }
        REFLECTION_METHOD (setParamVector) void setParamVector (const Core::VariantVector &paramVector) { this->paramVector = paramVector; }

        const Core::VariantMap &getArgsMap () const { return argsMap; }
        REFLECTION_METHOD (setArgsMap) void setArgsMap (const Core::VariantMap &map) { argsMap = map; }

private:

        std::string sourceCode;
        Core::Variant domain;
        Core::VariantVector paramVector;
        Core::VariantMap argsMap;

        REFLECTION_END (K202Proxy)
};

}

#endif /* K202EXECUTOR_H_ */
