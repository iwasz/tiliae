/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Attributes.h"

namespace Container {

void Attributes::setString (const std::string &key, const std::string &value)
{
        strMap[key] = value;
}

/****************************************************************************/

std::string Attributes::getString (const std::string &key) const
{
        Core::StringMap::const_iterator i = strMap.find (key);

        if (i != strMap.end ()) {
                return i->second;
        }

        return "";
}

/****************************************************************************/

void Attributes::setInt (const std::string &key, int value)
{
        intMap[key] = value;
}

/****************************************************************************/

int Attributes::getInt (const std::string &key) const
{
        IntMap::const_iterator i = intMap.find (key);
        if (i != intMap.end ()) {
                return i->second;
        }

        return 0;
}

/****************************************************************************/

void Attributes::setBool (const std::string &key, bool value)
{
        intMap[key] = value;
}

/****************************************************************************/

bool Attributes::getBool (const std::string &key) const
{
        IntMap::const_iterator i = intMap.find (key);
        if (i != intMap.end ()) {
                return i->second;
        }

        return false;
}

/****************************************************************************/

void Attributes::addAttributes (const Attributes &a)
{
        // TODO to się aż prosi o przeronieine tego na STL.
        foreach (Core::StringMap::value_type v, a.strMap) {
                Core::StringMap::iterator i = strMap.find (v.first);
                if (i == strMap.end ()) {
                        strMap[v.first] = v.second;
                }
        }

        foreach (IntMap::value_type v, a.intMap) {
                IntMap::iterator i = intMap.find (v.first);
                if (i == intMap.end ()) {
                        intMap[v.first] = v.second;
                }
        }
}

/****************************************************************************/

void Attributes::removeAttribute (const std::string &s)
{
        strMap.erase (s);
        intMap.erase (s);
}

/****************************************************************************/

void Attributes::removeAttributes (const Core::StringList &l)
{
        foreach (std::string s, l) {
                removeAttribute (s);
        }
}

/****************************************************************************/

bool Attributes::containsKey (const std::string &key) const
{
        return strMap.find (key) != strMap.end () || intMap.find (key) != intMap.end ();
}


}
