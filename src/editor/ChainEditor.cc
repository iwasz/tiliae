/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ChainEditor.h"

namespace Editor {

void ChainEditor::convert (const Core::Variant &input, Core::Variant *output, Common::Context *context)
{
        for (EditorList::const_iterator i = editors.begin (); i != editors.end (); ++i) {

                (*i)->convert (input, output, context);

                // Udalo sie skonwertowac
                if (output && !output->isNone ())
                        return;
        }
}

}
