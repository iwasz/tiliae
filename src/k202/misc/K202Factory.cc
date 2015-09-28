/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "K202Factory.h"
#include "core/variant/Variant.h"
#include "core/Typedefs.h"
#include "core/ApiMacro.h"
#include "k202/K202.h"
#include "k202/compiler/Compiler.h"

namespace k202 {

Core::Variant K202Factory::create (const Core::VariantMap &parameters, Core::DebugContext *context) const
{
        return Core::Variant (K202::create ());
}

}
