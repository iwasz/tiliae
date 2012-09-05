/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Script.h>
#include <cassert>

#include "Manager.h"
#include "Listener.h"
#include "K202.h"
#include "Sender.h"
#include "Scope.h"

namespace Signal {

/*
 * http://www.parashift.com/c++-faq-lite/ctors.html#faq-10.12
 * http://www.parashift.com/c++-faq-lite/ctors.html#faq-10.13
 * http://www.parashift.com/c++-faq-lite/ctors.html#faq-10.14
 */
Manager &Manager::instance ()
{
        static Manager *neverDelete = new Manager ();
        return *neverDelete;
}

/****************************************************************************/

void Manager::registerListener (IListener *lis)
{
        recvMap.insert (std::make_pair (lis->getOwnerObject (), lis));
}

/****************************************************************************/

void Manager::registerSender (Sender *sen)
{
        sendMap.insert (std::make_pair (sen->getOwnerObject (), sen));
}

/****************************************************************************/

void Manager::bind (void *object, const std::string &scope)
{
        typedef RecvMap::const_iterator Iter;
        typedef std::pair <Iter, Iter> Pair;

        Pair p = recvMap.equal_range (object);

        for (Iter i = p.first; i != p.second; i++) {
                IListener *lis = i->second;

//        Tu do zastanowienia, czy juz podpięty listener powinien się dać podpiąć, czy nie.
//                if (!lis->getRelative ()) {
//                        continue;
//                }

                addListenerToScope (lis, scope);
        }

        typedef SendMap::const_iterator SIter;
        typedef std::pair <SIter, SIter> SPair;

        SPair sp = sendMap.equal_range (object);

        for (SIter i = sp.first; i != sp.second; i++) {
                Sender *sen = i->second;
                addSenderToScope (sen, scope);
        }
}

/****************************************************************************/

void Manager::addListenerToScope (IListener *lis, const std::string &scopePath)
{
        assert (lis);

        Ptr <Scope> scope = findScope (scopePath);

        if (!scope) {
                scope = createNewScope (scopePath);
        }

        scope->addListener (lis);
        lis->addScope (scope.get ());
}

/****************************************************************************/

void Manager::addSenderToScope (Sender *sen, const std::string &scopePath)
{
        assert (sen);

        Ptr <Scope> scope = findScope (scopePath);

        if (!scope) {
                scope = createNewScope (scopePath);
        }

        sen->setScope (scope);
}

/****************************************************************************/

Core::Variant Manager::emit (const std::string &path,
        const Core::VariantVector &paramVector,
        const Core::VariantMap &argsMap)
{
        Ptr <Scope> scope = findScope (path);

        if (!scope) {
                // Zamiast zrzcać wyjątek olewamy sprawę - przecież nie raz będą niepodpęte sygnały!
                return Core::Variant ();
        }

        return emit (scope, paramVector, argsMap);
}

/****************************************************************************/

Core::Variant Manager::emit (Ptr <Scope> scope,
                    const Core::VariantVector &paramVector,
                    const Core::VariantMap &argsMap)
{
        return scope->emit (paramVector, argsMap);
}

/****************************************************************************/

Ptr <Scope> Manager::findScope (const std::string &scope) const
{
        ScopeMap::const_iterator i = scopeMap.find (scope);
        return (i == scopeMap.end ()) ? (Ptr <Scope> ()) : (i->second);
}

/****************************************************************************/

bool Manager::removeScope (const std::string &scope)
{
        return (bool)scopeMap.erase (scope);
}

/****************************************************************************/

Ptr <Scope> Manager::createNewScope (const std::string &scope)
{
        Ptr <Scope> ret = Scope::create (scope);
        scopeMap[scope] = ret;
        return ret;
}

/****************************************************************************/

void Manager::removeListeners (void *ptr)
{
        recvMap.erase (ptr);
}

/****************************************************************************/

void Manager::removeSenders (void *ptr)
{
        sendMap.erase (ptr);
}

} // nam
