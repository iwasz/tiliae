/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/lexical_cast.hpp>
#include "OrderedVariantMap.h"
#include "../../core/Exception.h"
#include "../../core/variant/Cast.h"
#include "../../core/variant/Variant.h"

namespace Common {
using namespace Core;

void OrderedVariantMap::clear ()
{
        container.get <0> ().clear ();
        container.get <1> ().clear ();
}

/****************************************************************************/

bool OrderedVariantMap::containsKey (const Core::Variant &key) const
{
        return containsKey (vcast <std::string> (key));
}

/****************************************************************************/

bool OrderedVariantMap::containsKey (const std::string &key) const
{
        Iterator0 i = container.get<0> ().find (key);
        return i != container.get<0> ().end ();
}

/****************************************************************************/

bool OrderedVariantMap::containsValue (const Core::Variant &value) const
{
        throw Core::Exception ("UnsupportedOperationException (OrderedVariantMap::containsValue)");
}

/****************************************************************************/

Core::Variant OrderedVariantMap::get (const Core::Variant &key) const
{
        return get (vcast <std::string> (key));
}

/****************************************************************************/

Core::Variant OrderedVariantMap::get (const std::string &key) const
{
        Iterator0 i = container.get<0> ().find (key);

        if (i == container.get<0> ().end ()) {
                return Core::Variant ();
        }

        return i->second;
}

/****************************************************************************/

void OrderedVariantMap::set (const Core::Variant &key, const Core::Variant &value)
{
        set (vcast <std::string> (key), value);
}

/****************************************************************************/

void OrderedVariantMap::set (const std::string &key, const Core::Variant &value)
{
        container.insert (std::make_pair (key, value));
}

/****************************************************************************/

void OrderedVariantMap::remove (const Core::Variant &key)
{
        remove (vcast <std::string> (key));
}

/****************************************************************************/

void OrderedVariantMap::remove (const std::string &key)
{
        Iterator0 i = container.get<0> ().find (key);

        if (i == container.get<0> ().end ()) {
                return;
        }

        container.get<0> ().erase (i);
}

/****************************************************************************/

int OrderedVariantMap::size () const
{
        return container.get <0> ().size ();
}

/****************************************************************************/

bool OrderedVariantMap::isEmpty () const
{
        return container.get <0> ().empty ();
}

/****************************************************************************/

std::string OrderedVariantMap::toString () const
{
        return std::string ("OrderedVariantMap (size=") + boost::lexical_cast <std::string> (size ()) + ")";
}

}
