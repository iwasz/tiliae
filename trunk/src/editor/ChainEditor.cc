/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ChainEditor.h"

namespace Editor {

void ChainEditor::convert (const Core::Variant &input, Core::Variant *output, bool *error, Core::DebugContext *context)
{
        dcBegin (context);

        for (EditorList::const_iterator i = editors.begin (); i != editors.end (); ++i) {

                bool err;
                (*i)->convert (input, output, &err, context);

                // Udalo sie skonwertowac
                if (!err || (output && !output->isNone ())) {
                        dcRollback (context);
                        clearError (error);
                        return;
                }
        }

        dcError (context, "ChainEditor::convert : none of child editors has succeeded.");
        dcCommit (context);
        setError (error);
}

}
