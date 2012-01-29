/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ChainEditor.h"

namespace Editor {

bool ChainEditor::convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        dcBegin (context);

        for (EditorList::const_iterator i = editors.begin (); i != editors.end (); ++i) {

                bool success = (*i)->convert (input, output, context);

                // Udalo sie skonwertowac
                if (success || (output && !output->isNone ())) {
                        dcRollback (context);
                        return true;
                }
        }

        dcError (context, "ChainEditor::convert : none of child editors has succeeded.");
        dcCommit (context);
        return false;
}

}
