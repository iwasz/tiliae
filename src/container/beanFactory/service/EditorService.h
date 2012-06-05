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

        EditorService () : currentEditor (NULL), defaultMappedEditor (NULL), noopEditor (NULL), noopNoCopyEditor (NULL), defaultBeanWrapper (NULL) {}
        virtual ~EditorService () {}

        void init (Core::VariantMap *singletons);

/*--------------------------------------------------------------------------*/

        virtual bool onMappedMetaBegin (MappedMeta *data);
        virtual void onConstructorArgsBegin (IMeta *data);
        virtual void onConstructorArgsEnd (IMeta *data);
        virtual void onValueData (std::string const &key, ValueData *data);
        virtual void onRefData (std::string const &key, RefData *data);

private:

        Editor::SimpleMapEditor *createMappedEditor ();

private:

        // Current mappedEditor / state variables
        Editor::SimpleMapEditor *currentEditor;

        // Singletons
        Editor::IEditor *defaultMappedEditor;
        Editor::IEditor *noopEditor;
        Editor::IEditor *noopNoCopyEditor;
        Wrapper::BeanWrapper *defaultBeanWrapper;
};

}

#	endif /* EDITORSERVICE_H_ */
