/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LISTEDITORSERVICE_H_
#define LISTEDITORSERVICE_H_

#include "beanFactory/service/BeanFactoryService.h"

namespace Wrapper {
class BeanWrapper;
}

namespace Editor {
class IndexedEditor;
}

namespace Container {

class IndexedMeta;
class IMeta;
class ListElem;
class ValueData;
class RefData;

/**
 * Create map-editors for mapped-meta.
 */
class ListEditorService : public BeanFactoryService {
public:

        ListEditorService () :
                currentEditor (NULL),
                currentFieldIdx (-1),
                defaultIndexedEditor (NULL),
                noopEditor (NULL),
                noopNoCopyEditor (NULL),
                defaultBeanWrapper (NULL),
                cArgsBeanWrapper (NULL) {}

        virtual ~ListEditorService () {}
        static Ptr <ListEditorService> create () { return Ptr <ListEditorService> (new ListEditorService); }
        void init (Core::VariantMap *singletons);

/*--------------------------------------------------------------------------*/

        virtual bool onIndexedMetaBegin (IndexedMeta *data);
        virtual void onConstructorArgsBegin (IMeta *data);
        virtual void onConstructorArgsEnd (IMeta *data);
        virtual void onValueData (std::string const &key, ValueData *data);
        virtual void onRefData (std::string const &key, RefData *data);

private:

        Editor::IndexedEditor *createIndexedEditor ();

private:

        // Current mappedEditor / state variables
        Editor::IndexedEditor *currentEditor;
        int currentFieldIdx;

        // Singletons
        Editor::IEditor *defaultIndexedEditor;
        Editor::IEditor *noopEditor;
        Editor::IEditor *noopNoCopyEditor;
        Wrapper::BeanWrapper *defaultBeanWrapper;
        Wrapper::BeanWrapper *cArgsBeanWrapper;
};

}

#	endif /* LISTEDITORSERVICE_H_ */
