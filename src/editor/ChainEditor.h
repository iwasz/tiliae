/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CHAINOFRESPONSIBILITYEDITOR_H_
#define CHAINOFRESPONSIBILITYEDITOR_H_

#include "IEditor.h"
#include "../core/ApiMacro.h"

namespace Editor {

/**
 *  Trzyma liste adapterow i podczas konwersji uzywa ich po kolei.
 *  Jesli jakims z nich uda sie dokonac konwersje, zwraca wynik.
 *  Dzieki temu mamy lancuch odpowiedzialnosci - reaguje ten adapter,
 *  ktory sie nadaje.
 */
class TILIAE_API ChainEditor : public IEditor  {
public:

        virtual ~ChainEditor () {}
        virtual void convert (const Core::Variant &input, Core::Variant *output, bool *error = NULL, Core::DebugContext *context = NULL);

        EditorList const &getEditors () const { return editors; }
        void setEditors (EditorList const &e) { this->editors = e; }
        void addEditor (Ptr <IEditor> e) { editors.push_back (e); }

private:

        EditorList editors;

};

}

#endif /* CHAINOFRESPONSIBILITYEDITOR_H_ */
