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

}// nam
