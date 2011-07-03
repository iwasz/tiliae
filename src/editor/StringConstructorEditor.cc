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

void StringConstructorEditor::convert (const Core::Variant &input, Core::Variant *output, Common::Context *context)
{
        if (input.isNone ()) {
                error (context, EditorException, Common::UNDEFINED_ERROR, "StringConstructorEditor::convert input.isNone ()");
                return;
        }

        if (!ccast <std::string> (input)) {
                error (context, EditorException, Common::UNDEFINED_ERROR, "StringConstructorEditor::convert !ccast <std::string> (input)");
                return;
        }

        std::type_info const &outputType = output->getTypeInfo ();

        Ptr <Class> cls = Manager::classForType (outputType);

#if 0
        std::cerr << outputType.name () << std::endl;
#endif

        if (!cls) {
                error (context, EditorException, Common::UNDEFINED_ERROR, "StringConstructorEditor::convert no class for type_info : [" + std::string (outputType.name ()) + "]");
                return;
        }

        Ptr <Constructor> ctr = cls->getConstructor (typeid (std::string const));

        if (!ctr) {
                error (context, EditorException, Common::UNDEFINED_ERROR, "StringConstructorEditor::convert no constructor (std::string const &) for class : [" + cls->getName () + "]");
                return;
        }

        *output = ctr->newInstance (input);
}

}
