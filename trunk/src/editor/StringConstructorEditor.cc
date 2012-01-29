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

void StringConstructorEditor::convert (const Core::Variant &input, Core::Variant *output, bool *error, Core::DebugContext *context)
{
        if (input.isNone ()) {
                dcError (context, "StringConstructorEditor::convert input.isNone ()");
                setError (error);
                return;
        }

        if (!ccast <std::string> (input)) {
                dcError (context, "StringConstructorEditor::convert !ccast <std::string> (input)");
                setError (error);
                return;
        }

        std::type_info const &outputType = output->getTypeInfo ();

        Ptr <Class> cls = Manager::classForType (outputType);

#if 0
        std::cerr << outputType.name () << std::endl;
#endif

        if (!cls) {
                dcError (context, "StringConstructorEditor::convert no class for type_info : [" + std::string (outputType.name ()) + "]");
                setError (error);
                return;
        }

        Ptr <Constructor> ctr = cls->getConstructor (typeid (std::string const));

        if (!ctr) {
                dcError (context, "StringConstructorEditor::convert no constructor (std::string const &) for class : [" + cls->getName () + "]");
                setError (error);
                return;
        }

        try {
                *output = ctr->newInstance (input);
        }
        catch (std::exception const &e) {
                dcError (context, std::string ("StringConstructorEditor::convert : constructor hast thrown an exception : ") + e.what ());
                setError (error);
        }

        clearError (error);
}

}
