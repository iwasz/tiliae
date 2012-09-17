/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SCOPE_H_
#define SCOPE_H_

#include <string>
#include "Listener.h"
#include "core/string/String.h"
#include "core/Pointer.h"
#include "core/ApiMacro.h"

namespace Signal {

/**
 * Scope to takie "worki" do których można wrzucać zarówno wysyłających i jak i nasłuchujących.
 * Obiekty wewnątrz jednego scope "słyszą się nawzajem".
 * \ingroup Signal
 */
class TILIAE_API Scope {
public:

        Scope (const std::string &p) : path (p) {}
        static Ptr <Scope> create (const std::string &p) { return Ptr <Scope> (new Scope (p)); }

        void addListener (IListener *listener);
        void removeListener (IListener *listener);

        bool isEmpty () const;
        int countListeners () const;

        Core::Variant emit (const Core::VariantVector &paramVector,
                            const Core::VariantMap &params);

        std::string getPath () const { return path; }
        void setPath (const std::string &path) { this->path = path; }

private:

        ListenerList listeners;
        std::string path;

};

}

#endif /* SCOPE_H_ */
