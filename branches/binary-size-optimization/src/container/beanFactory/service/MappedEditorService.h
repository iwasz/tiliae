/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MAPPED_EDITORSERVICE_H_
#define MAPPED_EDITORSERVICE_H_

#include "beanFactory/service/BeanFactoryService.h"
#include "BFMapEditor.h"

namespace Wrapper {
class BeanWrapper;
}

namespace Container {

/**
 * Create map-editors for mapped-meta.
 */
class MappedEditorService : public BeanFactoryService {
public:

        MappedEditorService () : currentEditor (NULL), defaultBeanWrapper (NULL) {}
        virtual ~MappedEditorService () {}

        void init (Core::VariantMap *singletons);

/*--------------------------------------------------------------------------*/

        virtual bool onMappedMetaBegin (MappedMeta *data);
        virtual void onConstructorArgsBegin (IMeta *data);
        virtual void onConstructorArgsEnd (IMeta *data);
        virtual void onValueData (std::string const &key, ValueData *data);
        virtual void onRefData (std::string const &key, RefData *data);

private:

        BFMapEditor *createMappedEditor ();

private:

        // Current mappedEditor / state variables
        BFMapEditor *currentEditor;

        // Singleton
        Wrapper::BeanWrapper *defaultBeanWrapper;
};

}

#	endif /* EDITORSERVICE_H_ */
