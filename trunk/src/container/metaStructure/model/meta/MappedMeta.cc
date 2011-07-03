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
        foreach (Ptr <MapElem> e, fields) {
                if (e->getKey () == key) {
                        return e;
                }
        }

        return Ptr <MapElem> ();
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

/****************************************************************************/

// TODO Implementacja 4 poniższych metod jest testowa!

void MappedMeta::addField (Ptr <MapElem> field)
{
        removeField (field->getKey ());
        fields.push_back (field);
}

void MappedMeta::addFields (const MapElemList &fields)
{
        foreach (Ptr <MapElem> e, fields) {
                addField (e);
        }
}

void MappedMeta::addFieldFront (Ptr <MapElem> field)
{
        removeField (field->getKey ());
        fields.push_front (field);
}

void MappedMeta::addFieldsFront (const MapElemList &fields)
{
        foreach (Ptr <MapElem> e, fields) {
                addFieldFront (e);
        }
}

} // nam
