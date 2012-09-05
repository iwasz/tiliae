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
                beanWrapperConversionForSingletons (NULL),
                beanWrapperConversionForPrototypes (NULL),
                cArgsBeanWrapper (NULL),
                noopNoCopyEditor (NULL) {}

        virtual ~EditorService () {}

/*--------------------------------------------------------------------------*/

        virtual bool onMappedMetaBegin (const MetaObject* data);
        virtual bool onIndexedMetaBegin(const MetaObject* data);
        virtual void onConstructorArgsBegin(const MetaObject* data);
        virtual void onConstructorArgsEnd(const MetaObject* data);
        virtual void onValueData (DataKey const *dk, const ValueData* data);
        virtual void onRefData (DataKey const *dk, const RefData* data);
        virtual void onNullData (DataKey const *dk, NullData const *data);

/*--------------------------------------------------------------------------*/

        void setCArgsBeanWrapper(Wrapper::BeanWrapper* argsBeanWrapper) { this->cArgsBeanWrapper = argsBeanWrapper; }
        void setBeanWrapperConversionForPrototypes (Wrapper::BeanWrapper* beanWrapperConversionForPrototypes) { this->beanWrapperConversionForPrototypes = beanWrapperConversionForPrototypes; }
        void setBeanWrapperConversionForSingletons (Wrapper::BeanWrapper* beanWrapperConversionForSingletons) { this->beanWrapperConversionForSingletons = beanWrapperConversionForSingletons; }
        void setNoopNoCopyEditor(Editor::IEditor* noopNoCopyEditor) { this->noopNoCopyEditor = noopNoCopyEditor; }

/*--------------------------------------------------------------------------*/

private:

        BFMapEditor *createMappedEditor (bool);
        BFIndexedEditor *createIndexedEditor (bool);

private:

        // Current mappedEditor / state variables
        BFMapEditor *currentMapEditor;
        BFIndexedEditor *currentIndexedEditor;
        int currentFieldIdx;

        // Singleton
        Wrapper::BeanWrapper *beanWrapperConversionForSingletons;
        Wrapper::BeanWrapper *beanWrapperConversionForPrototypes;
        Wrapper::BeanWrapper *cArgsBeanWrapper;
        Editor::IEditor *noopNoCopyEditor;
};

}

#	endif /* EDITORSERVICE_H_ */
