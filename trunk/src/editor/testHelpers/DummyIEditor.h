/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DUMMYIEDITOR_H_
#define DUMMYIEDITOR_H_

#include <Reflection.h>
#include "IEditor.h"
#include "../../core/ApiMacro.h"

/**
 * Kolejny przyklad, ale tym razem dla
 * klasy typu IEditor, czyli tej najgłówniejszej.
 */
struct TILIAE_API DummyIEditor : public Editor::IEditor {

        void convert (const Core::Variant &input, Core::Variant *output, Common::Context *context = NULL);

        REFLECTION_END_ (DummyIEditor)
};

#endif /* DUMMYIEDITOR_H_ */
