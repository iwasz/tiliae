/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "LexicalEditor.h"

namespace Editor {

void LexicalEditor <std::string, bool>::convert (const Core::Variant &input, Core::Variant *output, Core::Context *context)
{
        assert (output);

        if (!ccast <std::string> (input)) {
                error (context, EditorException, Common::UNDEFINED_ERROR, "LexicalEditor <std::string, bool>::convert. Input type is not std::string. Input type is : " + input.toString ());
                return;
        }

        std::string const &s = vcast <std::string> (input);
        bool b = (s == "true" || s == "1" || s == "on" || s == "yes");
        *output = Core::Variant (b);
}

/****************************************************************************/

void LexicalEditor <Core::String, bool>::convert (const Core::Variant &input, Core::Variant *output, Core::Context *context)
{
        assert (output);

        if (!ccast <Core::String> (input)) {
                error (context, EditorException, Common::UNDEFINED_ERROR, "LexicalEditor <Core::String, bool>::convert. Input type is not Core::String. Input type is : " + input.toString ());
                return;
        }

        Core::String const &s = vcast <Core::String> (input);
        bool b = (s == "true" || s == "1" || s == "on" || s == "yes");
        *output = Core::Variant (b);
}

}
