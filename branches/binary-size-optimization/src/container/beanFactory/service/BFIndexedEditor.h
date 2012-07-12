/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BFINDEXEDEDITOR_H_
#define BFINDEXEDEDITOR_H_

#include "JEditor.h"
#include <map>
#include "../core/Pointer.h"
#include "BFMapEditor.h"

namespace Wrapper {
class BeanWrapper;
}

namespace Container {

/**
 * Natomiast ta klasa traktuje swój wejściowy obiekt jako kolekcję,
 * po której da się iterować.
 *
 * Działa tak, że konwertuje obiekty we i wy do IIterable iteruje po nich
 * i dla każdego wykonuje jakis wewnetrzny edytor. Edytorów można ustawić
 * kilka i zostaną one żyte po kolei. Pierwszy dla pierwszego elementu,
 * drugi dla drugiego, etc. Jesli elementów wejściowych jest więcej
 * niż edytorów, to dla tych nadmiarowych zostanie użyty ostatni edytor.
 * W szczególnosci oznacza to, ze jeżeli ustawimy tu tylko jeden wew.
 * edytor, to zostanie on uzyty dla wszystkich elementów listy.
 *
 * Mam nieśmiały pomysł, żeby podczas iteracji ten Edytor tworzył pary
 * index, wartość i dopiero takie pary podawał do edytora editor jako
 * obiekt wejściowy. Do tego stworzyłoby się edytor PairEditor, który
 * pozwalałby dostosować zwykłe edytory do tego zachowania. Poniżej
 * BFIndexedEditor przedstawiam PairEditor.
 *
 * EDIT : przerobione na razie, że akceptuje tylko VariantList ne wejściu
 * i VariantVector na wyjściu.
 */
struct BFIndexedEditor : public BFMapEditor {

        typedef std::map <int, Element> ElementMap;

        virtual ~BFIndexedEditor () {}

/*--------------------------------------------------------------------------*/

        virtual bool edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

/*--------------------------------------------------------------------------*/

        void setElement (int i, Element &e) { elements[i] = e; }

private:

        ElementMap elements;

};

}

#endif /* BFIndexedEditor_H_ */
