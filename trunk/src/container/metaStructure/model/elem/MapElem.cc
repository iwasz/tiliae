/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MapElem.h"

namespace Container {

Ptr <MapElem> MapElem::create (const std::string &key, Ptr<IData> data/*, const Core::StringMap &attributes*/)
{
        Ptr <MapElem> ret (new MapElem);
        ret->setKey (key);
        ret->setData (data);
//        ret->setAttributes (attributes);
        return ret;
}

}
