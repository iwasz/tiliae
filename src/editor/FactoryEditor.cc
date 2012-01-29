/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "FactoryEditor.h"

namespace Editor {

void FactoryEditor::convert (const Core::Variant &input, Core::Variant *output, bool *error, Core::DebugContext *context)
{
        if (!output) {
                dcError (context, "FactoryEditor : !output");
                setError (error);
                return;
        }

        if (!factory) {
                dcError (context, "FactoryEditor : !factory");
                setError (error);
                return;
        }

        if (output->isNone () || output->isNull ()) {
                // Stworz output fabryką.
                *output = factory->create (factoryParams, context);
        }

        // Konwertuj.
        if (!editor) {
                dcError (context, "FactoryEditor : !editor");
                setError (error);
                return;
        }

        editor->convert (input, output, error, context);
}

}
