/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef JEDITOR_H_
#define JEDITOR_H_

#include "IEditor.h"
#include "../core/ApiMacro.h"

namespace Editor {

/**
 * To jest edytor, który oczekuje spełnienia określonych
 * warunków przez wariant output. Są to :
 * - output nie jest pustym wskaznikiem NULL,
 * - output nie jest none-variant,
 * - output nie jest null-variant.
 *
 * Dodatkowo oczekuje się od input, że:
 * - input nie jest none-variant,
 * - input nie jest null-variant.
 *
 * Jest to klasa abstrakcyjna i służy jako baza dla innych
 * edytorów, które nie muszą się martwić o stworzenie swojego
 * obiektu wyjściowego. Jesli obiekt wyściowy jest none, lub
 * null, to po prostu zrzucany jest wyjątek.
 *
 * TODO Wymyslic nazwe
 */
class TILIAE_API JEditor : public IEditor {
public:

        /**
         * Ta metoda nie jest wirtualna, poniewaz nie chce, zeby
         * ktos ja przedefiniowywal. Edytor jest albo IEditorem,
         * albo JEditorem i koniec. Jesli ktos chce zawrzec jakas
         * dodatkowa funkcjonalnosc w tej metodzie, powinien uzyc
         * zwyklego IEditor.
         */
        void convert (const Core::Variant &input, Core::Variant *output, Core::Context *context = NULL)
        {
                if (input.isNone () || input.isNull ()) {
                        error (context, EditorException, Common::UNDEFINED_ERROR, "Input argument must not be none variant (!isNone ()) and must not be null variant (!isNull ()).");
                	return;
                }

                if (!output) {
                        error (context, EditorException, Common::UNDEFINED_ERROR, "Output argument must not be NULL (output != NULL).");
                        return;
                }

                if (output->isNone () || output->isNull ()) {
                        error (context, EditorException, Common::UNDEFINED_ERROR, "Output argument must not be none variant (!isNone ()) and must not be null variant (!isNull ()).");
                        return;
                }

                edit (input, output, context);
        }

        /**
         * Chce, zeby to byla inna nazwa niz convert - ma sie odrozniac, zeby bylo wiadomo co sie dzieje.
         */
        virtual void edit (const Core::Variant &input, Core::Variant *output, Core::Context *context = NULL) = 0;
};

}

#endif /* JEDITOR_H_ */
