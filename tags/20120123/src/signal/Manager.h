/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SIGNAL_MANAGER_H_
#define SIGNAL_MANAGER_H_

#include <map>
#include <string>
#include "K202.h"
#include "../core/Exception.h"
#include "../core/string/String.h"
#include "../core/Pointer.h"

namespace Signal {
class IListener;
class Sender;
class Scope;

/**
 * Wyjątek oznaczający brak scope o zadanej nazwie.
 * \ingroup Signal
 */
struct TILIAE_API NoSuchScopeException : public Core::Exception {
        NoSuchScopeException (std::string const &msg) : Core::Exception (msg) {}
        virtual ~NoSuchScopeException () throw () {}
};

/**
 * Path should be relative.
 * \ingroup Signal
 */
struct TILIAE_API PathRelativeException : public Core::Exception {
        PathRelativeException (std::string const &msg) : Core::Exception (msg) {}
        virtual ~PathRelativeException () throw () {}
};

/**
 * Path should be absolute.
 * \ingroup Signal
 */
struct TILIAE_API PathAbsoluteException : public Core::Exception {
        PathAbsoluteException (std::string const &msg) : Core::Exception (msg) {}
        virtual ~PathAbsoluteException () throw () {}
};

/**
 * Mediator pomiędzy obiektami wysyłającymi, a odbierającymi sygnały.
 * \ingroup Signal
 */
class Manager {
public:

        typedef std::multimap <void *, IListener *> RecvMap;
        typedef std::multimap <void *, Sender *> SendMap;
        typedef std::map <std::string, Ptr <Scope> > ScopeMap;

        virtual ~Manager () {}

        static TILIAE_API Manager &instance ();

        void registerListener (IListener *);
        void registerSender (Sender *);

        void addListenerToScope (IListener *listener, const std::string &scope);
        void addSenderToScope (Sender *sen, const std::string &scopePath);

        // O(N)
        void removeListeners (void *ptr);
        void removeSenders (void *ptr);

        Core::Variant emit (const std::string &signalName,
                        const Core::VariantVector &paramVector,
                        const Core::VariantMap &params);

        Core::Variant emit (Ptr <Scope> scope,
                            /*const std::string &signalName,*/
                            const Core::VariantVector &paramVector,
                            const Core::VariantMap &params);


        /**
         * O(N)
         */
        void bind (void *, const std::string &scope);

        Ptr <Scope> findScope (const std::string &scope) const;
        Ptr <Scope> createNewScope (const std::string &scope);
        bool removeScope (const std::string &scope);
        int countScopes () const { return scopeMap.size (); }

private:

        RecvMap recvMap;
        SendMap sendMap;
        ScopeMap scopeMap;
};

} // nam

#endif /* MANAGER_H_ */
