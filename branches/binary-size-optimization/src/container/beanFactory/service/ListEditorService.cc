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
#include "../../../factory/ScalarFactory.h"

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

        BFIndexedEditor *editor = new BFIndexedEditor ();
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

BFIndexedEditor *ListEditorService::createIndexedEditor ()
{
        BFIndexedEditor *editor = new BFIndexedEditor ();
        editor->setBeanWrapper (defaultBeanWrapper);
        return editor;
}

/****************************************************************************/

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

        if (type == "" || Factory::ScalarFactory::isTypeSupported (type.c_str ())) {
                currentFieldIdx++;
                return;
        }

        BeanFactoryContainer *container = getBVFContext ()->getBeanFactoryContainer ();
        Ptr <BeanFactory> beanFactory = container->getBeanFactory (type, current);

        if (!beanFactory) {
                throw BeanNotFullyInitializedException ("Can't resolve editor for type [" + type + "].");
        }

        Element element;
        element.factory = beanFactory.get ();
        element.type = Element::EDITOR_FROM_BF;
        currentEditor->setElement (++currentFieldIdx, element);
}

/****************************************************************************/

void ListEditorService::onRefData (std::string const &key, RefData *data)
{
        // Brak edytora, kiedy podano custom-editor, lub kiedy jest bark pól do edycji
        if (!currentEditor) {
                return;
        }

        Ptr <BeanFactory> current = getBVFContext ()->getCurrentBF ();

        // Gdy abstract
        if (!current) {
                return;
        }

        BeanFactoryContainer *container = getBVFContext ()->getBeanFactoryContainer ();
        std::string referenceName = data->getData ();
        Element element;

        // Specjalne referencje (referencja do kontenera).
        if (referenceName == REFERENCE_TO_CONTAINER_ITSELF) {
                element.singleton = Core::Variant (container);
                element.type = Element::EXTERNAL_SINGLETON;
        }
        else {
                Factory::IFactory *factory = container->getBeanFactory (referenceName, current).get ();

                // Zwykłe beany zdefiniowane w XML
                if (factory) {
                        element.factory = factory;
                        element.type = Element::BEAN_FACTORY;
                }
                // Szukaj singletonu zewnętrznego w mapie siongletons
                else {
                        Core::VariantMap *singletons = container->getSingletons ();
                        Core::VariantMap::const_iterator i = singletons->find (referenceName);

                        if (i != singletons->end ()) {
                                element.singleton = i->second;
                                element.type = Element::EXTERNAL_SINGLETON;
                        }

                }
        }

        if (element.type == Element::EMPTY) {
                throw BeanNotFullyInitializedException ("Can't resolve reference (" + data->getData () + ").");
        }

        currentEditor->setElement (++currentFieldIdx, element);
}

}
