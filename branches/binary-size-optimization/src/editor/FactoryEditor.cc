/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "FactoryEditor.h"

namespace Editor {

bool FactoryEditor::convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        if (!output) {
                dcError (context, "FactoryEditor : !output");
                return false;
        }

        if (!factory) {
                dcError (context, "FactoryEditor : !factory");
                return false;
        }

        if (output->isNone () || output->isNull ()) {
                // Stworz output fabryką.
                *output = factory->create (factoryParams, context);
        }

        // Konwertuj.
        if (!editor) {
                dcError (context, "FactoryEditor : !editor");
                return false;
        }

        return editor->convert (input, output, context);
}

}
