/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include "ValueServiceHelper.h"
#include "Defs.h"
#include "common/Exceptions.h"
#include "IEditor.h"
#include "Typedefs.h"
#include "variant/Cast.h"
#include "IFactory.h"
#include "ReflectionFactory.h"

namespace Container {
using namespace Core;

const char *EDITOR_SPECIAL_CHAR = "&";

Core::Variant ValueServiceHelper::create (const char *typeC, const char *valueC) const
{
        std::string type;
        std::string value;

        if (typeC) {
                type = typeC;
        }

        if (valueC) {
                value = valueC;
        }

        if (type.empty ()) {
                params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant (std::string (DEFAULT_VALUE_TYPE));
        }
        else {
                params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant (type);
        }

        classArgs[0] = Core::Variant (value);
        params[Factory::ReflectionFactory::CONSTRUCTOR_ARGS] = Core::Variant (&classArgs);

        Variant v = defaultValueFactory->create (params);

#if 0
        std::cerr << v << std::endl;
#endif

        /*
         * Jeśli ScalarFactory nie utworzył nic, to znaczy że mamy podany jakiś customowy edytor.
         * Jednak potrzebna jest początkowa wartość.
         */

        return (v.isNone ()) ? Variant (value) : v;
}

}
