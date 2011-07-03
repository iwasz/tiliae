/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Script.h"
#include "Listener.h"
#include "Scope.h"

//#define DBG

namespace Signal {

/****************************************************************************/

AbstractListener::AbstractListener (void *v,
                  const std::string &path) :
                  ownerObject (v)
{
        Signal::Manager::instance ().registerListener (this);

        if (!path.empty ()) {
                Manager::instance ().addListenerToScope (this, path);
        }
}

/****************************************************************************/

AbstractListener::AbstractListener (void *v,
                  const std::string &path,
                  const Core::VariantVector &paramVector,
                  const Core::VariantMap &argsMap) :
                  ownerObject (v)
{
        Signal::Manager::instance ().registerListener (this);

        if (!path.empty ()) {
                Manager::instance ().addListenerToScope (this, path);
        }
}

/****************************************************************************/

Listener::~Listener ()
{
        Signal::Manager::instance ().removeListeners (getOwnerObject ());

        #ifdef DBG
        std::cerr << "Remove listener signal=[" + signalName + "]. Scope : " << ((scope) ? ("true") : ("false"));
        #endif

        foreach (Scope *scope, getScopeList ()) {

                scope->removeListener (this);

                #ifdef DBG
                std::cerr << " from scope named=[" << scope->getPath () << "]. Scope.isEmpty : "
                                << ((scope->isEmpty ()) ? ("true") : ("false")) << ". Scope.count : "
                                << scope->countListeners ();

                #endif

                if (scope->isEmpty ()) {
                        #ifdef DBG
                        std::cerr << " Remove scope named=[" << scope->getPath () << "] from manager.";
                        #endif

                        Signal::Manager::instance ().removeScope (scope->getPath ());
                }

        }

        #ifdef DBG
        std::cerr << std::endl;
        #endif
}

/****************************************************************************/

Core::VariantVector Listener::getParamVector () const
{
        if (!script) {
                return Core::VariantVector ();
        }

        return script->getParamVector ();
}

/****************************************************************************/

void Listener::setParamVector (const Core::VariantVector &paramVector)
{
        if (!script) {
                return;
        }

        script->setParamVector (paramVector);
}

/****************************************************************************/

Core::VariantMap Listener::getArgsMap () const
{
        if (!script) {
                return Core::VariantMap ();
        }

        return script->getArgsMap ();
}

/****************************************************************************/

void Listener::setArgsMap (const Core::VariantMap &map)
{
        if (!script) {
                return;
        }

        script->setArgsMap (map);
}

/****************************************************************************/

Core::Variant Listener::run (const Core::VariantVector &paramVector,
                             const Core::VariantMap &argsMap)
{
        k202::K202 *k = k202::K202::instance ();
        return k->run (getScript (), NULL, paramVector, argsMap);
}

} // nam
