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

void IndexedMeta::addFields (const ListElemList &fields)
{
        std::copy (fields.begin (), fields.end (), std::back_inserter (this->fields));
}

/****************************************************************************/

ListElemList IndexedMeta::getFields () const
{
        if (parent) {
                IndexedMeta *indexedParent = dynamic_cast <IndexedMeta *> (parent);
                assert (indexedParent);
                ListElemList ret = indexedParent->getFields ();
                std::copy (fields.begin (), fields.end (), std::back_inserter (ret));
                return ret;
        }

        return fields;
}

}// nam
