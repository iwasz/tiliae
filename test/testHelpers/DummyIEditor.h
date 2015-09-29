/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DUMMYIEDITOR_H_
#define DUMMYIEDITOR_H_

#include "reflection/Reflection.h"
#include "editor/IEditor.h"
#include "core/ApiMacro.h"

/**
 * Kolejny przyklad, ale tym razem dla
 * klasy typu IEditor, czyli tej najgłówniejszej.
 */
struct TILIAE_API __tiliae_reflect__ DummyIEditor : public Editor::IEditor {

        bool convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

        REFLECTION_END_ (DummyIEditor)
};

#endif /* DUMMYIEDITOR_H_ */
