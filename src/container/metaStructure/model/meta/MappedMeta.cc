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

MappedMeta::~MappedMeta ()
{
        for (DataKeyIterator0 i = fields.begin (); i != fields.end (); ++i) {
                delete i->data;
        }
}

/****************************************************************************/

IData *MappedMeta::getField (const std::string &key)
{
//        for (MapElemList::const_iterator i = fields.begin (); i != fields.end (); ++i) {
//                if ((*i)->getKey () == key) {
//                        return *i;
//                }
//        }

        DataKeyIterator0 iter = fields.get <0> ().find (key);

        if (iter != fields.get <0> ().end ()) {
                return iter->data;
        }

        if (parent) {
                MappedMeta *mappedParent = dynamic_cast <MappedMeta *> (parent);
                assert (mappedParent);
                return mappedParent->getField (key);
        }

        return NULL;
}

/****************************************************************************/

void MappedMeta::addField (DataKey const &dataKey)
{
        fields.erase (dataKey.key);
        fields.get <1> ().push_back (dataKey);
//        fields.insert (dataKey);
}

/****************************************************************************/

DataMap MappedMeta::getFields () const
{
        if (parent) {
                MappedMeta *mappedParent = dynamic_cast <MappedMeta *> (parent);
                assert (mappedParent);
                DataMap ret = mappedParent->getFields ();


                std::copy (fields.get <1> ().begin (), fields.get <1> ().end (), std::back_inserter (ret.get <1> ()));

                for (DataKeyIterator1 i = fields.get <1> ().begin (); i != fields.get <1> ().end (); ++i) {
                        ret.erase (i->key);
                        ret.get <1> ().push_back (*i);
                }

                return ret;
        }

        return fields;
}

/*
 * FIXME To można za pomocą STL zrobić w 2 razy mniej linijek i może szybciej.
 */
//MapElemList MappedMeta::getFieldsAsList () const
//{
//        if (parent) {
//                MappedMeta *mappedParent = dynamic_cast <MappedMeta *> (parent);
//                assert (mappedParent);
//
//                MapElemList parList = mappedParent->getFieldsAsList ();
//                MapElemList ret;
//
//                for (MapElemList::const_iterator i = parList.begin (); i != parList.end (); ++i) {
//
//                        bool found = false;
//
//                        for (MapElemList::const_iterator j = fields.begin (); j != fields.end (); ++j) {
//                                if ((*i)->getKey () == (*j)->getKey ()) {
//                                        found = true;
//                                        break;
//                                }
//                        }
//
//                        if (!found) {
//                                ret.push_back (*i);
//                        }
//                }
//
//                std::copy (fields.begin (), fields.end (), std::back_inserter (ret));
//                return ret;
//        }
//
//        return fields;
//}

/****************************************************************************/

//void MappedMeta::removeField (const std::string &key)
//{
//        MapElemList::iterator j;
//        for (MapElemList::iterator i = fields.begin (); i != fields.end ();) {
//                Ptr <MapElem> el = *i;
//                j = i++;
//
//                if (el->getKey () == key) {
//                         fields.erase (j);
//                }
//        }
//}

} // nam
