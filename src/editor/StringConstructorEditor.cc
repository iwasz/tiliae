/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <string>
#include "StringConstructorEditor.h"
#include "../core/variant/Cast.h"
#include "Reflection.h"

namespace Editor {
using namespace Reflection;

bool StringConstructorEditor::convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        if (input.isNone ()) {
                dcError (context, "StringConstructorEditor::convert input.isNone ()");
                return false;
        }

        if (!ccast <std::string> (input)) {
                dcError (context, "StringConstructorEditor::convert !ccast <std::string> (input)");
                return false;
        }

        std::type_info const &outputType = output->getTypeInfo ();

        Reflection::Class *cls = Manager::classForType (outputType);

#if 0
        std::cerr << outputType.name () << std::endl;
#endif

        if (!cls) {
                dcError (context, "StringConstructorEditor::convert no class for type_info : [" + std::string (outputType.name ()) + "]");
                return false;
        }

        Constructor *ctr = cls->getConstructor (typeid (std::string const));

        if (!ctr) {
                dcError (context, "StringConstructorEditor::convert no constructor (std::string const &) for class : [" + cls->getName () + "]");
                return false;
        }

        try {
                *output = ctr->newInstance (input);
        }
        catch (Core::Exception const &e) {
                context->addContext (e.getContext());
                dcError (context, std::string ("StringConstructorEditor::convert : constructor hast thrown an exception."));
                return false;
        }
        catch (std::exception const &e) {
                dcError (context, std::string ("StringConstructorEditor::convert : constructor hast thrown an exception : ") + e.what ());
                return false;
        }

        return true;
}

}
