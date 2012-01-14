/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TTEE_SENDER_H_
#define TTEE_SENDER_H_

#include <string>
#include "Scope.h"
#include "Manager.h"
#include "Reflection.h"
#include "../core/string/String.h"
#include "../core/Typedefs.h"
#include "../core/Pointer.h"
#include "../core/ApiMacro.h"

namespace Signal {

/**
 * Odpowiednik sygnału w SigC, czy Boost.Signal. Ma metodę emit, która wysyła sygnał
 * do scope do którego jest zbindowany ten Sender. Drugim sposobem na wysłąnie sygnału
 * jest użycie jednej z globalnych metod Signal::emit, ale one potrafią być wolniejsze,
 * ponieważ nie przechowują wskaźnika do scope, tylko muszą go najpierw znaleźć (jest
 * jedna wersja emit, która przyjmuje wskaźnik do scope jako argument).
 * \ingroup Signal
 */
class TILIAE_API Sender {
public:
        c__ (void)

        Sender ();
        Sender (void *ownerObject);
        Sender (void *ownerObject, std::string const &path);
        // TODO Za dużo tych konstruktorów - wyjebać - zostawić tylko ten ze stringiem, bez możliwości bindowania.
        Sender (std::string const &path);
        ~Sender ();

        void *getOwnerObject () { return ownerObject; }
        void setOwnerObject (void *v) { ownerObject = v; }

        Ptr<Scope> getScope () const { return scope; }
        void setScope (Ptr<Scope> scope) { this->scope = scope; }

        m_ (setPath) void setPath (std::string const &s);
        std::string const &getPath () const { return path; }

        Core::Variant emit (const Core::VariantVector &paramVector,
                            const Core::VariantMap &params = Core::VariantMap ());

        Core::Variant emit ();

        Ptr <Core::VariantVector const> getParamVector () const { return paramVector; }
        m_ (setParamVector) void setParamVector (Ptr <Core::VariantVector> pv) { paramVector = pv; }

        Ptr <Core::VariantMap const> getParamMap () const { return paramMap; }
        m_ (setParamMap) void setParamMap (Ptr <Core::VariantMap> pm) { paramMap = pm; }

private:

        Ptr <Scope> scope;
        void *ownerObject;
        std::string path;

        Ptr <Core::VariantVector> paramVector;
        Ptr <Core::VariantMap> paramMap;

        e_ (Sender)
};

} // nam

#endif /* SENDER_H_ */
