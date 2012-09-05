/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ByteCode.h"
#include "Script.h"
#include "Context.h"
#include <algorithm>

namespace k202 {
using namespace std;

Core::Variant Script::run (Context *ctx,
                           Core::Variant *domain,
                           const Core::VariantVector &paramVector,
                           const Core::VariantMap &argsMap)
{
        Core::VariantMap tmpMap;
        Core::VariantVector tmpVec;

        // Zeby uniknąć zbędnego kopiowania.
        if (!this->paramVector.empty () && paramVector.empty ()) {
                ctx->setParamVector (&this->paramVector);
        }
        else {
                tmpVec.reserve (this->paramVector.size () + paramVector.size ());
                copy (this->paramVector.begin (), this->paramVector.end (), back_inserter (tmpVec));
                copy (paramVector.begin (), paramVector.end (), back_inserter (tmpVec));
                ctx->setParamVector (&tmpVec);
        }

        // Analogicznie z mapą. Zeby uniknąć zbędnego kopiowania:
        if (!this->argsMap.empty () && argsMap.empty ()) {
                ctx->setArgsMap (&this->argsMap);
        }
        else {
                tmpMap = this->argsMap;
                std::copy (argsMap.begin (), argsMap.end (), std::inserter (tmpMap, tmpMap.begin ()));
                ctx->setArgsMap (&tmpMap);
        }

        if (!this->domain.isNone ()) {
                ctx->setDomain (&this->domain);
        }
        else if (domain && !domain->isNone ()) {
                ctx->setDomain (domain);
        }
        else {
                ctx->setDomain (NULL);
        }

        return byteCode->run (ctx);
}

}
