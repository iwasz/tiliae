/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Sender.h"

namespace Signal {

Sender::Sender () : ownerObject ()
{
        Signal::Manager::instance ().registerSender (this);
}

/****************************************************************************/

Sender::Sender (void *ownerObject) :
                ownerObject (ownerObject)
{
//        Signal::Manager::instance ().registerSender (this);
}

/****************************************************************************/

Sender::Sender (void *ownerObject, std::string const &p) :
                ownerObject (ownerObject), path (p)
{
//        Signal::Manager::instance ().registerSender (this);
//        Signal::Manager::instance ().bind (ownerObject, p);


        Signal::Manager::instance ().addSenderToScope (this, path);

}

/****************************************************************************/

Sender::Sender (std::string const &path)
{
        Signal::Manager::instance ().addSenderToScope (this, path);
}

/****************************************************************************/

Sender::~Sender ()
{
//        Signal::Manager::instance ().removeSenders (ownerObject);
}

/****************************************************************************/

void Sender::setPath (std::string const &p)
{
        path = p;
//        assert (ownerObject);
//        Signal::Manager::instance ().bind (ownerObject, p);
        Signal::Manager::instance ().addSenderToScope (this, path);
}

/****************************************************************************/

Core::Variant Sender::emit (const Core::VariantVector &pv,
                            const Core::VariantMap &pm)
{
        if (scope) {
                return scope->emit (pv, pm);
        }

        return Core::Variant ();
}

/****************************************************************************/

Core::Variant Sender::emit ()
{
        if (scope) {
                return scope->emit ((paramVector) ? (*paramVector) : (Core::VariantVector ()),
                                (paramMap) ? (*paramMap) : (Core::VariantMap ()));
        }

        return Core::Variant ();
}

}
