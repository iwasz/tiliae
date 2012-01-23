/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DummyJEditor.h"
#include <cassert>
#include "../../core/variant/Cast.h"
#include "../../core/string/String.h"
#include "../../core/variant/Variant.h"

void DummyJEditor::edit (const Core::Variant &input, Core::Variant *output, Core::Context *context)
{
//        assert (ccast <Core::String> (input));
//        assert (output);
//        assert (ccast <Core::String &> (*output) ||
//                ccast <Core::String *> (*output));

        /*
         * A ta asercja jest bardzo kontrowersyjna. Jezeli bedzie odkomentowana,
         * to bedzie oznaczalo, ze ten edytor ma modyfikowac jakies zewnetrzne
         * oibekty, ktore istnieja w oderwaniu od warianta. Na przyklad :
         *
         * MegaTon mt;
         * Variant out = Core::Variant (&mt);
         * editor.edit (in, out);
         *
         * // Teraz mt ma juz inna wartosc, mozna go uzyc.
         *
         * Jesli natomiast zakomentujemy ja, bedzie mozna wowczas zwracac wartosc
         * w wariancie-wartosci. Wariant wartosc zawiera obiekt, ktory nie istnieje
         * poza nim (moga istniec do niego wskazniki). Poprzedni kod wowczas nie
         * zadziala. Trzebaby go przerobic :
         *
         * MegaTon mt
         * Variant out = Core::Variant (mt);
         * editor.edit (in, out);
         * MegaTon *pmt = vcast <MegaTon *> (out);
         *
         * // Dopiero teraz mozna uzyc pmt, ale uwaga, kiedy out zyjdzie z zakresu,
         * // to wskazink bedzie wskazywal w kosmos.
         *
         * Konkluzja 1 : mimo, ze edytory maja ten sam interfejs, to sposob ich
         * uzywania moze sie roznic w zaleznosci od tego co przekazujemy parametrem
         * out.
         *
         * Konkluzja 2 : aby kod sie nie roznil (a to ma duze znaczenie, kiedy
         * chcemy, zeby jeden kod dzialal i dla uchwytow i dla wartosci, nalezy
         * uzyc podejscia 2, bo ono dziala i dla handle i dla value.
         */

        // ASSERT (output.isHandle ());

        /*
         * Oczywiscie te 3 powyzsze sprawdzenia powtarzaja sie.
         * Wystarczyloby sprawdzic tylko to co jest w punkcie
         * ad 2. i 3.
         */

        Core::String inStr = vcast <Core::String> (input);
        Core::String *outStr = vcast <Core::String *> (*output);

        *outStr = getLeft () + inStr + getRight ();
}
