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
#include "BFIndexedEditor.h"

namespace Wrapper {
class BeanWrapper;
}

namespace Container {

/**
 * Create map-editors for mapped-meta.
 */
class EditorService : public BeanFactoryService {
public:

        EditorService () :
                currentMapEditor (NULL),
                currentIndexedEditor (NULL),
                currentFieldIdx (-1),
                defaultBeanWrapper (NULL),
                cArgsBeanWrapper (NULL),
                noopNoCopyEditor (NULL) {}

        virtual ~EditorService () {}

/*--------------------------------------------------------------------------*/

        virtual bool onMappedMetaBegin (const MetaObject* data);
        virtual bool onIndexedMetaBegin(const MetaObject* data);
        virtual void onConstructorArgsBegin(const MetaObject* data);
        virtual void onConstructorArgsEnd(const MetaObject* data);
        virtual void onValueData(const std::string& key, const ValueData* data);
        virtual void onRefData(const std::string& key, const RefData* data);

/*--------------------------------------------------------------------------*/

        void setCArgsBeanWrapper(Wrapper::BeanWrapper* argsBeanWrapper) { this->cArgsBeanWrapper = argsBeanWrapper; }
        void setDefaultBeanWrapper(Wrapper::BeanWrapper* defaultBeanWrapper) { this->defaultBeanWrapper = defaultBeanWrapper; }
        void setNoopNoCopyEditor(Editor::IEditor* noopNoCopyEditor) { this->noopNoCopyEditor = noopNoCopyEditor; }

/*--------------------------------------------------------------------------*/

private:

        BFMapEditor *createMappedEditor ();
        BFIndexedEditor *createIndexedEditor ();

private:

        // Current mappedEditor / state variables
        BFMapEditor *currentMapEditor;
        BFIndexedEditor *currentIndexedEditor;
        int currentFieldIdx;

        // Singleton
        Wrapper::BeanWrapper *defaultBeanWrapper;
        Wrapper::BeanWrapper *cArgsBeanWrapper;
        Editor::IEditor *noopNoCopyEditor;
};

}

#	endif /* EDITORSERVICE_H_ */
