/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include <string>
#include "DummyIEditor.h"
#include "../../core/variant/Cast.h"
#include "../../editor/IEditor.h"

using namespace Core;
using Editor::EditorException;

void DummyIEditor::convert (const Core::Variant &input, Core::Variant *output, Core::Context *context)
{
        /*
         * Input nie moż być pustym wariantem. Output nie
         * może być pustym wskaźnikiem.
         */
        if (input.isNone ()) {
                error (context, EditorException, Common::UNDEFINED_ERROR, "DummyIEditor::convert input is NONE");
                return;
        }

        if (!output) {
                error (context, EditorException, Common::UNDEFINED_ERROR, "DummyIEditor::convert !output");
                return;
        }

        /*
         * Input musi mieć typ wymagany przez ten edytor.
         * Output też.
         */
        if (!ccast <std::string> (input)) {
                error (context, EditorException, Common::UNDEFINED_ERROR, "DummyIEditor::convert can't cast input to std::string.");
                return;
        }

        /*
         * Alternatywnie, jeśli output nie zawiera zadnego obiektu
         * wyjsciowego, to mamy szanse go stworzyc i przekazac na
         * zewnatrz.
         */
        if (output->isNone ()) {
                // Normalnie uzyjemy operatora new:
                // *output = Core::Variant (new std::string ());
                // Jednak dla zwyklego stringa nie warto i wystarczy value.
                *output = Core::Variant (std::string ());
        }
        else {
                /*
                 * Jesli jednak przekazano obiekt wejsciowy w output,
                 * to musi to byc uchwyt. Inaczej nie
                 */
                assert (output->isHandle());
        }

        /*
         * Bądź co bądź, output musi dac sie skonwertowac
         * do zwykłego (nie const) wskaźnika lub referencji,
         * zebysmy mogli zmienic mu wartosc.
         */
        if (!ccast <std::string &> (*output) &&
            !ccast <std::string *> (*output)) {

                error (context, EditorException, Common::UNDEFINED_ERROR, "DummyIEditor::convert can't cast output to std::string.");
                return;
        }


        std::string strIn = vcast <std::string> (input);

        /*
         * Troche bez sensu, bo stworzylismy juz ten string.
         * Ale gdyby wariant zawieral jakis ciezki obiekt,
         * wzialbym do niego wskaznik i pozmenial to co ma
         * w srodku, jak ponizej:
         *
         * Heavy *h = var_cas <Heavy *> (*output);
         * h.setA ("aaa");
         * h.setHeavyProp (megaTonObject);
         */

        std::string *s = vcast <std::string *> (*output);
        *s = "(" + strIn + ")";
}
