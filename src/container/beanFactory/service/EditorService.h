/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EDITORSERVICE_H_
#define EDITORSERVICE_H_

#include "beanFactory/service/BeanFactoryService.h"

namespace Factory {
class IFactory;
}

namespace Wrapper {
class BeanWrapper;
}

namespace Editor {
class SimpleMapEditor;
class IndexedEditor;
}

namespace Editor {
class IEditor;
}

namespace Container {

/**
 * Create map-editors for mapped-meta.
 * TODO zmienić nazwę  na MapEditorService
 */
class EditorService : public BeanFactoryService {
public:

        virtual ~EditorService () {}
        static Ptr <EditorService> create () { return Ptr <EditorService> (new EditorService); }
        void init (Core::VariantMap *singletons);

/*--------------------------------------------------------------------------*/

        virtual bool onMappedMetaBegin (MappedMeta *data);
        virtual void onConstructorArgsBegin (IMeta *data);
        virtual void onConstructorArgsEnd (IMeta *data);
        virtual void onMapElem (MapElem *data);
        virtual void onValueData (ValueData *data);
        virtual void onRefData (RefData *data);

private:

        Ptr <Editor::SimpleMapEditor> createMappedEditor ();

private:

        // Current mappedEditor / state variables
        Ptr <Editor::SimpleMapEditor> currentEditor;
        std::string currentFieldName;

        // Singletons
        Ptr <Editor::IEditor> defaultMappedEditor;
        Ptr <Editor::IEditor> noopEditor;
        Ptr <Editor::IEditor> noopNoCopyEditor;
        Ptr <Wrapper::BeanWrapper> defaultBeanWrapper;
};

}

#	endif /* EDITORSERVICE_H_ */
