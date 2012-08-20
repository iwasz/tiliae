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

        void init (Core::VariantMap *singletons);

/*--------------------------------------------------------------------------*/

        virtual bool onMappedMetaBegin (MetaObject const *data);
        virtual bool onIndexedMetaBegin (MetaObject const *data);
        virtual void onConstructorArgsBegin (MetaObject const *data);
        virtual void onConstructorArgsEnd (MetaObject const *data);
        virtual void onValueData (std::string const &key, ValueData const *data);
        virtual void onRefData (std::string const &key, RefData const *data);

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
