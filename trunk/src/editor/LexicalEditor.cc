/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "LexicalEditor.h"

namespace Editor {

void LexicalEditor <std::string, bool>::convert (const Core::Variant &input, Core::Variant *output, bool *error, Core::DebugContext *context)
{
        assert (output);

        if (!ccast <std::string> (input)) {
                dcError (context, "LexicalEditor <std::string, bool>::convert. Input type is not std::string. Input type is : " + input.toString ());
                setError (error);
                return;
        }

        std::string const &s = vcast <std::string> (input);
        bool b = (s == "true" || s == "1" || s == "on" || s == "yes");
        *output = Core::Variant (b);
        clearError (error);
}

/****************************************************************************/

void LexicalEditor <Core::String, bool>::convert (const Core::Variant &input, Core::Variant *output, bool *error, Core::DebugContext *context)
{
        assert (output);

        if (!ccast <Core::String> (input)) {
                dcError (context, "LexicalEditor <Core::String, bool>::convert. Input type is not Core::String. Input type is : " + input.toString ());
                setError (error);
                return;
        }

        Core::String const &s = vcast <Core::String> (input);
        bool b = (s == "true" || s == "1" || s == "on" || s == "yes");
        *output = Core::Variant (b);
        clearError (error);
}

}
