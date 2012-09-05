/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LISTENER_H_
#define LISTENER_H_

#include <list>
#include <string>
#include "Manager.h"
#include "Helper.h"
#include "../core/Object.h"
#include "../core/variant/Variant.h"
#include "../core/Typedefs.h"
#include "../core/ApiMacro.h"

namespace Signal {
class Scope;
typedef std::list <Scope *> ScopeList;


struct TILIAE_API IListener : public Core::Object {

        virtual ~IListener () {}
        virtual Core::Variant run (const Core::VariantVector &paramVector,
                                   const Core::VariantMap &argsMap) = 0;

        virtual void *getOwnerObject () = 0;
        virtual void addScope (Scope *) = 0;
};

/**
 * Domyślna implementacja wspólnych metod dla wszystkich Listener'ów. Prosta implementacja
 * niektórych metod. Są to settery, które powtarzają się we wszystkich implementacjach.
 */
class TILIAE_API AbstractListener : public IListener {
public:

        AbstractListener () : ownerObject () {}

        AbstractListener (void *v,
                          const std::string &path = std::string ());

        AbstractListener (void *v,
                          const std::string &path,
                          const Core::VariantVector &paramVector,
                          const Core::VariantMap &argsMap = Core::VariantMap ());

        virtual ~AbstractListener () {}

        void *getOwnerObject () { return ownerObject; }
        void setOwnerObject (void *v) { ownerObject = v; }

        ScopeList &getScopeList () { return scopeList; }
        ScopeList const &getScopeList () const { return scopeList; }
        void addScope (Scope *s) { scopeList.push_back (s); }

private:

        void *ownerObject;
        ScopeList scopeList;
};

/**
 * Odpowiednik socketa nasłuchującego.
 * \ingroup Signal
 */
class TILIAE_API Listener : public AbstractListener {
public:

        /**
         *
         * @param receiver Pointer to object which owns this Listener.
         * @param signalName Nae of signal to listen to. Without path to scope. If
         * you wish to bind this Listener at startup, bind in to some scope in receiver
         * constructor. For example : Recv::Recv () : onClicked (...) { bind (&onClicked, "/window"); }
         * @param code
         * @return
         */
        template <typename T>
        Listener (T *receiver,
                const std::string &code,
                const std::string &path = std::string (),
                const Core::VariantVector &paramVector = Core::VariantVector (),
                const Core::VariantMap &argsMap = Core::VariantMap ());

        ~Listener ();

        Core::Variant run (const Core::VariantVector &paramVector,
                           const Core::VariantMap &argsMap);

//        void *getOwnerObject () { return ownerObject; }
        Ptr <k202::Script> getScript () const { return script; }

//        const ScopeList &getScopeList () const { return scopeList; }
//        void addScope (Ptr<Scope> scope) { scopeList.add (scope); }

        Core::VariantVector getParamVector () const;
        void setParamVector (const Core::VariantVector &paramVector);

        Core::VariantMap getArgsMap () const;
        void setArgsMap (const Core::VariantMap &map);

private:

//        void *ownerObject;
        Ptr <k202::Script> script;
//        ScopeList scopeList;
};

/****************************************************************************/

extern void bind (const std::string &scope, void *receiver);

/****************************************************************************/

template <typename T>
Listener::Listener (T *receiver,
                    const std::string &code,
                    const std::string &path,
                    const Core::VariantVector &paramVector,
                    const Core::VariantMap &argsMap) :
                    AbstractListener (receiver, path, paramVector, argsMap)
{
        k202::K202 *k = k202::K202::instance ();
        Core::Variant v = Core::Variant (receiver);
        this->script = k->prepare (code, v, paramVector, argsMap);
}

typedef std::list <IListener *> ListenerList;

} // nam

#endif /* LISTENER_H_ */
