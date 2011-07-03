/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Functions.h"
#include "Scope.h"

namespace Signal {

Core::Variant emit (const std::string &path,
        const Core::VariantVector &paramVector,
        const Core::VariantMap &argsMap)
{
        return Signal::Manager::instance ().emit (path, paramVector, argsMap);
}

Core::Variant emit (Ptr <Scope> scope, /*const std::string &signalName,*/
        const Core::VariantVector &paramVector,
        const Core::VariantMap &argsMap)
{
        return Signal::Manager::instance ().emit (scope, /*signalName,*/ paramVector, argsMap);
}

void bind (const std::string &scope, void *receiver)
{
        Signal::Manager::instance ().bind (receiver, scope);
}

void bind (const std::string &scope, void *r1, void *r2)
{
        Signal::Manager::instance ().bind (r1, scope);
        Signal::Manager::instance ().bind (r2, scope);
}

void bind (const std::string &scope, void *r1, void *r2, void *r3)
{
        Signal::Manager::instance ().bind (r1, scope);
        Signal::Manager::instance ().bind (r2, scope);
        Signal::Manager::instance ().bind (r3, scope);
}

Ptr <Scope> findScope (const std::string &scopePath)
{
        return Signal::Manager::instance ().findScope (scopePath);
}

} // nam.
