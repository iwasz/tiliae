/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TypeEditor.h"
#include "../core/variant/Variant.h"

namespace Editor {

void TypeEditor::convert (const Core::Variant &input, Core::Variant *output, bool *error, Core::DebugContext *context)
{
        // Znajdź odpowiedni do typów edytor.
        std::type_info const &inputType = input.getTypeInfo ();
        std::type_info const &outputType = output->getTypeInfo ();

        // Jeżeli typy się nie różnią, to użyj standardowego w edytora.
        if (inputType == outputType || input.isNull ()) {
                getEqType ()->convert (input, output, error, context);
                clearError (error);
                return;
        }

        // Jeśli są różne, to znajdź z listy.
        Container::iterator i = container.find (boost::make_tuple (&inputType, &outputType));

        // Użyj go i daj wynik.
        if (i != container.end ()) {
                i->editor->convert (input, output, error, context);
                clearError (error);
        }

        // Nie powiodło się.
        setError (error);
}

}
