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
        MapElemMap::iterator i = fields.find (key);

        if (i != fields.end ()) {
                return i->second;
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
        fields[field->getKey ()] = field;
}

/****************************************************************************/

MapElemList MappedMeta::getFieldsAsList () const
{
        MapElemMap tmp;

        if (parent) {
                MappedMeta *mappedParent = dynamic_cast <MappedMeta *> (parent);
                assert (mappedParent);
                tmp = mappedParent->getFields ();
        }

        std::copy (fields.begin (), fields.end (), std::inserter (tmp, tmp.end ()));

        MapElemList ret;

        for (MapElemMap::const_iterator i = tmp.begin (); i != tmp.end (); ++i) {
                ret.push_back (i->second);
        }

        return ret;
}

} // nam
