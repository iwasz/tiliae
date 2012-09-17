/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DUMMYJEDITOR_H_
#define DUMMYJEDITOR_H_

#include <string>
#include "editor/JEditor.h"

/**
 * JEditor, ktory oczekuje Stringow i zwraca
 * wejsciowe stringi opakowane w kwadratowe
 * nawiasy.
 */
struct DummyJEditor : public Editor::JEditor {

        DummyJEditor () : left ("["), right ("]") {}
        DummyJEditor (const std::string &l, const std::string &r) : left (l), right (r) {}

        virtual bool edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

        std::string getLeft () const { return left; }
        void setLeft (const std::string &left) { this->left = left; }

        std::string getRight () const { return right; }
        void setRight (const std::string &right) { this->right = right; }

private:

        std::string left;
        std::string right;
};

#endif /* DUMMYJEDITOR_H_ */
