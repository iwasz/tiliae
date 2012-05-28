/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SIMPLEMAPEDITOR_H_
#define SIMPLEMAPEDITOR_H_

#include <string>
#include "IEditor.h"
#include "JEditor.h"
#include "../core/Pointer.h"
#include "../core/ApiMacro.h"

namespace Wrapper {
class BeanWrapper;
}

namespace Editor {

/**
 * Podobny do IndexedEditor, z tym że wejściowy i wyjściowy obiekt ma być
 * typu Core::Map.
 * Klucze map muszą być typu std::string.
 */
class TILIAE_API SimpleMapEditor : public JEditor {
public:

        SimpleMapEditor () : editors (new EditorMap ()) {}
        SimpleMapEditor (Ptr <EditorMap> e) : editors (e) {}
        virtual ~SimpleMapEditor () {}

        virtual bool edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

/*--------------------------------------------------------------------------*/

        Ptr<Wrapper::BeanWrapper> getBeanWrapper () const { return beanWrapper; }
        void setBeanWrapper (Ptr<Wrapper::BeanWrapper> beanWrapper) { this->beanWrapper = beanWrapper; }

        Ptr<EditorMap> getEditors () const { return editors; }
        void setEditors (Ptr<EditorMap> editors) { this->editors = editors; }

        void setEditor (const std::string &name, Ptr<IEditor> editor) { editors->operator[] (name) = editor; }
        Ptr<IEditor> getEditor (const std::string & name) const;

        void setDefaultEditor (Ptr <IEditor> editor) { defaultEditor = editor; }
        Ptr <IEditor> getDefaultEditor () const { return defaultEditor; }

private:

        Ptr <EditorMap> editors;
        Ptr <IEditor> defaultEditor;
        Ptr <Wrapper::BeanWrapper> beanWrapper;

};

}

#endif /* SIMPLEMAPEDITOR_H_ */
