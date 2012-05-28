/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <algorithm>
#include <iterator>
#include "IndexedMeta.h"

namespace Container {

IndexedMeta::~IndexedMeta ()
{
        for (DataVector::iterator i = fields.begin (); i != fields.end (); ++i) {
                delete *i;
        }
}

//void IndexedMeta::addFields (const ListElemList &fields)
//{
//        std::copy (fields.begin (), fields.end (), std::back_inserter (this->fields));
//}

/****************************************************************************/

DataVector IndexedMeta::getFields () const
{
        if (parent) {
                IndexedMeta *indexedParent = dynamic_cast <IndexedMeta *> (parent);
                assert (indexedParent);
                DataVector ret = indexedParent->getFields ();
                std::copy (fields.begin (), fields.end (), std::back_inserter (ret));
                return ret;
        }

        return fields;
}

}// nam
