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
#include "../../../editor/IEditor.h"
#include "../../../core/Typedefs.h"
#include "../../../core/variant/Cast.h"
#include "../../../factory/IFactory.h"
#include "../../../factory/ReflectionFactory.h"

namespace Container {
using namespace Core;

const char *EDITOR_SPECIAL_CHAR = "&";

Core::Variant ValueServiceHelper::create (const std::string &type, const std::string &value) const
{
        assert (getSingletonMap ());
        VariantMap::const_iterator i = getSingletonMap ()->find (DEFAULT_VALUE_FACTORY_NAME);

        // Jeśli nie ma odpowiedniego edytora, to zostawiamy nieprzeedytowane
        if (i == getSingletonMap ()->end ()) {
                return Core::Variant (value);
        }

        if (!occast <Factory::IFactory *> (i->second)) {
                throw ContainerException ("ValueServiceHelper::create : !occast <Factory::IFactory *> (i->second)");
        }

        Factory::IFactory *factory = ocast <Factory::IFactory *> (i->second);
        assert (factory);

        if (type.empty ()) {
                params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant (std::string (DEFAULT_VALUE_TYPE));
        }
        else {
                params[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant (type);
        }

        classArgs[0] = Core::Variant (value);
        params[Factory::ReflectionFactory::CONSTRUCTOR_ARGS] = Core::Variant (&classArgs);

        Variant v = factory->create (params);

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
