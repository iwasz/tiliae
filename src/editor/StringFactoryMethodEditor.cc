/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "StringFactoryMethodEditor.h"
#include "../core/variant/Cast.h"

namespace Editor {

bool StringFactoryMethodEditor::convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        if (input.isNone ()) {
                dcError (context, "StringFactoryMethodEditor::convert input.isNone ()");
                return false;
        }

        if (!ccast <std::string> (input)) {
                dcError (context, "StringFactoryMethodEditor::convert !ccast <std::string> (input)");
                return false;
        }

        std::type_info const &outputType = output->getTypeInfo ();
#if 0
        std::cerr << outputType.name () << ", " << container.size () << std::endl;
#endif

        Container::iterator i = container.find (&outputType);

        if (i == container.end ()) {
                dcError (context, std::string ("StringFactoryMethodEditor::convert no conversion function for type_info : ") + outputType.name ());
                return false;
        }

        ConversionFunctionPtr ptr = i->second;
        *output = (*ptr) (vcast <std::string> (input));
        return true;
}


} /* namespace Editor */
