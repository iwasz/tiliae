/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STRINGTOMEGATONEDITOR_H_
#define STRINGTOMEGATONEDITOR_H_

#include "JEditor.h"
#include <cassert>
#include "../../factory/testHelpers/MegaTon.h"
#include "../../core/variant/Variant.h"
#include "../../core/variant/Cast.h"
#include "../../core/string/String.h"

/**
 * Edytory dzialaja w jedna strone, nie tak jak w javie.
 * Ten konwertuje stringa do MegaTona.
 */
struct StringToMegatonEditor : public Editor::JEditor {

        virtual ~StringToMegatonEditor () {}

        virtual void edit (const Core::Variant &input, Core::Variant *output, Common::Context *context = NULL)
        {
                // Sprawdzanie typow parametrow.
                assert (ccast <Core::String> (input));
                assert (output);
                assert (ccast <MegaTon *> (*output));
//                ASSERT (output-getContaining () == Core::HANDLE, "");

                Core::String inStr = vcast <Core::String> (input);
                MegaTon *mt = vcast <MegaTon *> (*output);

                mt->setHeavyProperty (inStr);
        }

};

#endif /* STRINGTOMEGATONEDITOR_H_ */
