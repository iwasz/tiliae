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

void TypeEditor::convert (const Core::Variant &input, Core::Variant *output, Common::Context *context)
{
        // Znajdź odpowiedni do typów edytor.
        std::type_info const &inputType = input.getTypeInfo ();
        std::type_info const &outputType = output->getTypeInfo ();

        if (input.isNull ()) {
                getEqType ()->convert (input, output, context);
        }

        // Jeżeli typy się nie różnią, to użyj standardowego w edytora.
        if (inputType == outputType) {
                getEqType ()->convert (input, output, context);
                return;
        }

        // Jeśli są różne, to znajdź z listy.
        Container::iterator i = container.find (boost::make_tuple (&inputType, &outputType));

        // Użyj go i daj wynik.
        if (i != container.end ()) {
                i->editor->convert (input, output, context);
        }
}

}
