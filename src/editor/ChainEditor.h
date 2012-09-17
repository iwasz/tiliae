/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CHAINOFRESPONSIBILITYEDITOR_H_
#define CHAINOFRESPONSIBILITYEDITOR_H_

#include "editor/IEditor.h"
#include "core/ApiMacro.h"

namespace Editor {

/**
 *  Trzyma liste adapterow i podczas konwersji uzywa ich po kolei.
 *  Jesli jakims z nich uda sie dokonac konwersje, zwraca wynik.
 *  Dzieki temu mamy lancuch odpowiedzialnosci - reaguje ten adapter,
 *  ktory sie nadaje.
 */
class TILIAE_API ChainEditor : public IEditor  {
public:

        ChainEditor (bool d = false) : deleteContents (d) {}
        virtual ~ChainEditor ();
        virtual bool convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

        EditorVector const &getEditors () const { return editors; }
        void setEditors (EditorVector const &e) { this->editors = e; }
        void addEditor (IEditor *e) { editors.push_back (e); }

private:

        EditorVector editors;
        bool deleteContents;

};

}

#endif /* CHAINOFRESPONSIBILITYEDITOR_H_ */
