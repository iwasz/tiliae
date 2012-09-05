/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef INDEXEDEDITOR_H_
#define INDEXEDEDITOR_H_

#include "IEditor.h"
#include "JEditor.h"
#include <map>
#include "../core/Pointer.h"
#include "../core/ApiMacro.h"

namespace Wrapper {
class BeanWrapper;
}

namespace Editor {

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
 * IndexedEditor przedstawiam PairEditor.
 *
 * EDIT : przerobione na razie, że akceptuje tylko VariantList ne wejściu
 * i VariantVector na wyjściu.
 */
struct TILIAE_API IndexedEditor : public JEditor {

        typedef std::map <int, IEditor *> EditorMap;

        IndexedEditor () : defaultEditor (NULL), beanWrapper (NULL) {}
        IndexedEditor (EditorMap const &m) : editors (m), defaultEditor (NULL), beanWrapper (NULL) {}
        virtual ~IndexedEditor () {}

/*--------------------------------------------------------------------------*/

        virtual bool edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

/*--------------------------------------------------------------------------*/

        /**
         * Zwraca całą listę edytorów.
         */
        EditorMap const &getEditors () const { return editors; }
        void setEditors (EditorMap const &editors) { this->editors = editors; }
        void setEditors (EditorVector const &editors);
        void setEditor (int index, IEditor *editor) { editors[index] = editor; }
        IEditor *getEditor (int index);

        /**
         * DefaultEditor jest edytorem, który jest używany w przypadku, gdy
         * nie znaleziono edytora o pasującym kluczu na mapie editors.
         */
        void setDefaultEditor (IEditor *editor) { defaultEditor = editor; }
        IEditor *getDefaultEditor () const { return defaultEditor; }

        Wrapper::BeanWrapper *getBeanWrapper () const { return beanWrapper; }
        void setBeanWrapper (Wrapper::BeanWrapper *beanWrapper) { this->beanWrapper = beanWrapper; }

private:

        EditorMap editors;
        IEditor *defaultEditor;
        Wrapper::BeanWrapper *beanWrapper;

};

}

#endif /* INDEXEDEDITOR_H_ */
