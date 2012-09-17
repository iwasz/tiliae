/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include <string>
#include "ListToStringEditor.h"
#include "core/variant/Cast.h"
#include "core/Typedefs.h"
#include "core/string/String.h"

namespace Editor {
using namespace Core;

bool ListToStringEditor::edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        // TODO Szczerze mówiąc, nie wiem czemu to ma być VariantList, ale inaczej test testBeanWithCustomEditor nie przechodzi
        VariantList const *in = vcast <VariantList const *> (input);
        std::string *outStr = vcast <std::string *> (*output);

        *outStr = "";
        VariantList::const_iterator i = in->begin ();

        while (true) {
                *outStr += quotation + vcast <std::string> (*i) + quotation;

                if (++i != in->end ()) {
                        *outStr += delimiter;
                }
                else {
                        break;
                }
        }

        return true;
}

}
