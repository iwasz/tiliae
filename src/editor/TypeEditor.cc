/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TypeEditor.h"
#include "core/variant/Variant.h"

namespace Editor {

TypeEditor::~TypeEditor ()
{
        if (!deleteContents) {
                return;
        }

        delete eqType;
        delete nullType;

        for (Container::iterator i = container.begin (); i != container.end (); ++i) {
                delete i->editor;
        }
}

bool TypeEditor::convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        // Znajdź odpowiedni do typów edytor.
        std::type_info const &inputType = input.getTypeInfo ();
        std::type_info const &outputType = output->getTypeInfo ();

        // Jeżeli typy się nie różnią, to użyj standardowego w edytora.
        if (inputType == outputType || input.isNull ()) {
                return getEqType ()->convert (input, output, context);
        }

        // Jeśli są różne, to znajdź z listy.
        Container::iterator i = container.find (boost::make_tuple (&inputType, &outputType));

        // Użyj go i daj wynik.
        if (i != container.end ()) {
                return i->editor->convert (input, output, context);
        }

        // Nie powiodło się.
        return false;
}

}
