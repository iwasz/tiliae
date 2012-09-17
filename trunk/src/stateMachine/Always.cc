/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Always.h"
#include "core/Typedefs.h"

namespace StateMachine {

void Always::run (MachineContext *context)
{
        Core::VariantMap *mp = context->getMap (MachineContext::RUN);

        if (mp) {
                mp->operator[] ("ALWAYS") = Core::Variant (true);
        }
}

}
