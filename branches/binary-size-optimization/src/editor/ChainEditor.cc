/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ChainEditor.h"

namespace Editor {

ChainEditor::~ChainEditor ()
{
        if (deleteContents) {
                for (EditorVector::iterator i = editors.begin (); i != editors.end (); ++i) {
                        delete *i;
                }
        }
}

bool ChainEditor::convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        for (EditorVector::const_iterator i = editors.begin (); i != editors.end (); ++i) {

                bool success = (*i)->convert (input, output, context);

                // Udalo sie skonwertowac
                if (success || (output && !output->isNone ())) {
                        return true;
                }
        }

        dcError (context, "ChainEditor::convert : none of child editors has succeeded.");
        return false;
}

}
