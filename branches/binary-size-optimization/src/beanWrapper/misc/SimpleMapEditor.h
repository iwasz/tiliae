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

        SimpleMapEditor () : defaultEditor (NULL), beanWrapper (NULL) {}
        SimpleMapEditor (EditorMap const &e) : editors (e), defaultEditor (NULL), beanWrapper (NULL) {}
        virtual ~SimpleMapEditor () {}

        virtual bool edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

/*--------------------------------------------------------------------------*/

        Wrapper::BeanWrapper *getBeanWrapper () const { return beanWrapper; }
        void setBeanWrapper (Wrapper::BeanWrapper *beanWrapper) { this->beanWrapper = beanWrapper; }

        EditorMap const &getEditors () const { return editors; }
        void setEditors (EditorMap const &editors) { this->editors = editors; }

        void setEditor (const std::string &name, IEditor *editor) { editors.operator[] (name) = editor; }
        IEditor *getEditor (const std::string & name) const;

        void setDefaultEditor (IEditor *editor) { defaultEditor = editor; }
        IEditor *getDefaultEditor () const { return defaultEditor; }

private:

        EditorMap editors;
        IEditor *defaultEditor;
        Wrapper::BeanWrapper *beanWrapper;

};

}

#endif /* SIMPLEMAPEDITOR_H_ */
