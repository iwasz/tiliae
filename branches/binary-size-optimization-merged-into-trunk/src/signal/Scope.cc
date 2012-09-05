/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Scope.h"
#include "Manager.h"

namespace Signal {

void Scope::addListener (IListener *listener)
{
        listeners.push_back (listener);
}

/****************************************************************************/

void Scope::removeListener (IListener *listener)
{
        listeners.erase (std::remove (listeners.begin (), listeners.end (), listener), listeners.end ());
}

/****************************************************************************/

bool Scope::isEmpty () const
{
//        return listenerMap.empty ();
        return listeners.empty ();
}

/****************************************************************************/

int Scope::countListeners () const
{
        return listeners.size ();
}

/****************************************************************************/

Core::Variant Scope::emit (const Core::VariantVector &paramVector,
                           const Core::VariantMap &argsMap)
{
        for (ListenerList::iterator i = listeners.begin (); i != listeners.end ();) {

                IListener *lis = *i;

                if (!lis) {
                        ++i;
                        continue;
                }

                // Wykonaj kod wszystkich listenerów, a dla ostatniego zwróć wartość.
                if (++i == listeners.end ()) {
                        return lis->run (paramVector, argsMap);
                } else {
                        lis->run (paramVector, argsMap);
                }
        }

        return Core::Variant (); // Nie powinno tu dojść, bo powinno zwrócić z pętli.
}

} // nam
