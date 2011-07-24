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
        Common::Context tmpCtx;
        unsigned int errCnt = 0;

        for (EditorList::const_iterator i = editors.begin (); i != editors.end (); ++i) {

                (*i)->convert (input, output, &tmpCtx);

                // Udalo sie skonwertowac
                if (output && !output->isNone ())
                        return;

                if (tmpCtx.isError ()) {
                        ++errCnt;
                }
        }

        if (errCnt >= editors.size ()) {
                error (context, EditorException, UNDEFINED_ERROR, "ChainEditor::convert : none of child editors has succeeded.");
        }
}

}
