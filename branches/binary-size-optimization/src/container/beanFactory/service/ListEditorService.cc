/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <FactoryEditor.h>
#include <LazyEditor.h>
#include <boost/make_shared.hpp>
#include "ListEditorService.h"
#include "Defs.h"
#include "metaStructure/model/MetaStructure.h"
#include "../../../core/Pointer.h"
#include "../../../beanWrapper/beanWrapper/BeanWrapper.h"
#include "../../../beanWrapper/misc/IndexedEditor.h"

namespace Container {
using namespace Core;

void ListEditorService::init (Core::VariantMap *singletons)
{
        Core::Variant v = singletons->operator[] (DEFAULT_INDEXED_EDITOR_NAME);
        defaultIndexedEditor = ocast <Editor::IEditor *> (v);

        v = singletons->operator[] (NOOP_EDITOR_NAME);
        noopEditor = ocast <Editor::IEditor *> (v);

        v = singletons->operator[] (NOOP_NO_COPY_EDITOR_NAME);
        noopNoCopyEditor = ocast <Editor::IEditor *> (v);

        v = singletons->operator[] (BEAN_WRAPPER_W_CONVERSION);
        defaultBeanWrapper = ocast <Wrapper::BeanWrapper *> (v);

        v = singletons->operator[] (BEAN_WRAPPER_SIMPLE);
        cArgsBeanWrapper = ocast <Wrapper::BeanWrapper *> (v);
}

/****************************************************************************/

bool ListEditorService::onIndexedMetaBegin (IndexedMeta *meta)
{
        // Tu powinien być beanFactory odpowiadający podanemu meta w parametrze.
        Ptr <BeanFactory> beanFactory = getBVFContext ()->getCurrentBF ();

        if (!beanFactory) {
                // Gdy abstract
                return false;
        }

        currentFieldIdx = -1;

        std::string customEditorName = meta->getEditor ();
        Editor::IEditor *editor = NULL;

        if (!customEditorName.empty ()) {
                BeanFactoryContainer *container = getBVFContext ()->getBeanFactoryContainer ();
                Ptr <BeanFactory> fact = container->getBeanFactory (customEditorName, beanFactory);
                editor = new Editor::LazyEditor (fact.get ());
                beanFactory->setEditor (editor, true);
        }
        else if (meta->getFields ().empty ()) {
                editor = noopNoCopyEditor;
                currentEditor = NULL;
                beanFactory->setEditor (editor, false);
        }
        else {
                editor = currentEditor = createIndexedEditor ();
                beanFactory->setEditor (editor, true);
        }

        if (!editor) {
                throw BeanNotFullyInitializedException ("Can't create editor for BeanFactory. Bean id : (" +
                        meta->getId () + "), editor name : (" + meta->getEditor () + ").");
        }

        return true;
}

/****************************************************************************/

void ListEditorService::onConstructorArgsBegin (IMeta *data)
{
        // TODO getConstructorArgs przez referencje powino być, bo tu się kopiuje bez sensu.
        if (!data || data->getConstructorArgs ().empty ()) {
                return;
        }

        Ptr <BeanFactory> beanFactory = getBVFContext ()->getCurrentBF ();

        if (!beanFactory) {
                // Gdy abstract
                return;
        }

        currentFieldIdx = -1;

        Editor::IndexedEditor *editor = new Editor::IndexedEditor ();
        editor->setDefaultEditor (defaultIndexedEditor);
        editor->setBeanWrapper (cArgsBeanWrapper);

        currentEditor = editor;
        beanFactory->setCArgsEditor (currentEditor);
}

/****************************************************************************/

void ListEditorService::onConstructorArgsEnd (IMeta *data)
{
        currentEditor = NULL;
        currentFieldIdx = -1;
}

/****************************************************************************/

Editor::IndexedEditor *ListEditorService::createIndexedEditor ()
{
        Editor::IndexedEditor *editor = new Editor::IndexedEditor ();
        editor->setDefaultEditor (defaultIndexedEditor);
        editor->setBeanWrapper (defaultBeanWrapper);
        return editor;
}


/****************************************************************************/

//void ListEditorService::onListElem (ListElem *data)
//{
//        currentFieldIdx++;
//}

/****************************************************************************/

// TODO Zdublowny kod!
void ListEditorService::onValueData (std::string const &key, ValueData *data)
{
        // Brak edytora, kiedy podano custom-editor, lub kiedy jest bark pól do edycji
        if (!currentEditor) {
                return;
        }

        std::string type = data->getType ();
        Ptr <BeanFactory> current = getBVFContext ()->getCurrentBF ();

        if (!current) {
                // Gdy abstract
                return;
        }

        // TODO Z tym stringami to trzeba jakoś sprytinej wymyślić.
        // TODO To nie może tak być.
        if (type == "" ||
                type == "int" ||
                type == "unsigned int" ||
                type == "char" ||
                type == "double" ||
                type == "bool" ||
                type == "string" ||
                type == "String" ||
                type == "text") {
                currentFieldIdx++;
                return;
        }

        BeanFactoryContainer *container = getBVFContext ()->getBeanFactoryContainer ();
        Ptr <BeanFactory> beanFactory = container->getBeanFactory (type, current);

        if (!beanFactory) {
                throw BeanNotFullyInitializedException ("Can't resolve editor for type [" + type + "].");
        }

        // TODO LazyEditor się nie skasuje.
        currentEditor->setEditor (++currentFieldIdx, new Editor::LazyEditor (beanFactory.get ()));
}

/****************************************************************************/

// TODO Zdublowny kod!
void ListEditorService::onRefData (std::string const &key, RefData *data)
{
        // Brak edytora, kiedy podano custom-editor, lub kiedy jest bark pól do edycji
        if (!currentEditor) {
                return;
        }

        Ptr <BeanFactory> current = getBVFContext ()->getCurrentBF ();

        if (!current) {
                // Gdy abstract
                return;
        }

        BeanFactoryContainer *container = getBVFContext ()->getBeanFactoryContainer ();
        Ptr <BeanFactory> beanFactory = container->getBeanFactory (data->getData (), current);

        if (!beanFactory) {
                throw BeanNotFullyInitializedException ("Can't resolve reference (" +
                                data->getData () + ").");
        }

        // TODO FactoryEditor się nie skasuje
        currentEditor->setEditor (++currentFieldIdx, new Editor::FactoryEditor (noopNoCopyEditor, beanFactory.get ()));
}

}
