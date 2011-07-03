/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SillyFactory.h"

namespace Factory {

void SillyFactory::setOriginal (const Core::Variant &original)
{
        this->original = original;
}

}
