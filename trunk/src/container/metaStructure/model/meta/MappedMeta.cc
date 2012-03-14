/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MappedMeta.h"
#include "../../../../core/Typedefs.h"

namespace Container {

Ptr <MapElem> MappedMeta::getField (const std::string &key)
{
        for (MapElemList::const_iterator i = fields.begin (); i != fields.end (); ++i) {
                if ((*i)->getKey () == key) {
                        return *i;
                }
        }

        if (parent) {
                MappedMeta *mappedParent = dynamic_cast <MappedMeta *> (parent);
                assert (mappedParent);
                return mappedParent->getField (key);
        }

        return Ptr <MapElem> ();
}

/****************************************************************************/

void MappedMeta::addField (Ptr <MapElem> field)
{
        removeField (field->getKey ());
        fields.push_back (field);
}

/****************************************************************************/

/*
 * FIXME To można za pomocą STL zrobić w 2 razy mniej linijek i może szybciej.
 */
MapElemList MappedMeta::getFieldsAsList () const
{
        if (parent) {
                MappedMeta *mappedParent = dynamic_cast <MappedMeta *> (parent);
                assert (mappedParent);

                MapElemList parList = mappedParent->getFieldsAsList ();
                MapElemList ret;

                for (MapElemList::const_iterator i = parList.begin (); i != parList.end (); ++i) {

                        bool found = false;

                        for (MapElemList::const_iterator j = fields.begin (); j != fields.end (); ++j) {
                                if ((*i)->getKey () == (*j)->getKey ()) {
                                        found = true;
                                        break;
                                }
                        }

                        if (!found) {
                                ret.push_back (*i);
                        }
                }

                std::copy (fields.begin (), fields.end (), std::back_inserter (ret));
                return ret;
        }

        return fields;
}

/****************************************************************************/

void MappedMeta::removeField (const std::string &key)
{
        MapElemList::iterator j;
        for (MapElemList::iterator i = fields.begin (); i != fields.end ();) {
                Ptr <MapElem> el = *i;
                j = i++;

                if (el->getKey () == key) {
                         fields.erase (j);
                }
        }
}

} // nam
