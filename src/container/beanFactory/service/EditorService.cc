/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/make_shared.hpp>
#include "EditorService.h"
#include "metaStructure/model/MetaStructure.h"
#include "common/Exceptions.h"
#include "Defs.h"
#include "../../../core/variant/Variant.h"
#include "../../../core/Typedefs.h"
#include "../../../core/variant/Cast.h"
#include "../../../beanWrapper/beanWrapper/BeanWrapper.h"
#include "../../../factory/ScalarFactory.h"
#include "../../../editor/LazyEditor.h"
#include "StrUtil.h"

namespace Container {
using namespace Core;

/**
 * Początek procesowania MappedMeta (odpowiada tagom <map> oraz <bean>). Tu wpadają
 * obiekty MappedMeta będące w obrębie jednego kontenera (te ze zlinkowanych nie
 * wpadają). Tworzony jest Editor::SimpleMapEditor lub jeśli user sobie zażyczył,
 * ustawiany jest jakiś inny customowy (atrybut editor). Edytor jest ustawiany do
 * odpowiedniego BeanFactory.
 */
bool EditorService::onMappedMetaBegin (MetaObject const *meta)
{
        currentFieldIdx = -1;
        currentIndexedEditor = NULL;

        // Tu powinien być beanFactory odpowiadający podanemu meta w parametrze.
        BeanFactory *beanFactory = getBVFContext ()->getCurrentBF ();

        if (!beanFactory) {
                // Gdy abstract
                return false;
        }

        std::string customEditorName = toStr (meta->getEditor ());
        Editor::IEditor *editor = NULL;

        if (!customEditorName.empty ()) {
                BeanFactoryContainer *container = getBVFContext ()->getBeanFactoryContainer ();
                editor = ocast <Editor::IEditor *> (container->getSingleton (customEditorName.c_str ()));
                beanFactory->setEditor (editor, false);
        }
        else {
                editor = currentMapEditor = createMappedEditor (meta->getScope () == MetaObject::SINGLETON);
                beanFactory->setEditor (editor, true);
        }

        if (!editor) {
                throw BeanNotFullyInitializedException ("Can't create editor for BeanFactory. Bean id : (" + std::string (meta->getId ()) + "), editor name : (" + std::string (meta->getEditor ()) + ").");
        }

        return true;
}

/****************************************************************************/

bool EditorService::onIndexedMetaBegin (MetaObject const *meta)
{
        currentMapEditor = NULL;

        // Tu powinien być beanFactory odpowiadający podanemu meta w parametrze.
        BeanFactory *beanFactory = getBVFContext ()->getCurrentBF ();

        if (!beanFactory) {
                // Gdy abstract
                return false;
        }

        currentFieldIdx = -1;

        std::string customEditorName = toStr (meta->getEditor ());
        std::string id = toStr (meta->getId ());

        Editor::IEditor *editor = NULL;

        if (!customEditorName.empty ()) {
                BeanFactoryContainer *container = getBVFContext ()->getBeanFactoryContainer ();
                editor = ocast <Editor::IEditor *> (container->getSingleton (customEditorName.c_str ()));
                beanFactory->setEditor (editor, false);
        }
        else if (meta->getFields ().empty ()) {
                editor = noopNoCopyEditor;
                currentIndexedEditor = NULL;
                beanFactory->setEditor (editor, false);
        }
        else {
                editor = currentIndexedEditor = createIndexedEditor (meta->getScope () == MetaObject::SINGLETON);
                beanFactory->setEditor (editor, true);
        }

        if (!editor) {
                throw BeanNotFullyInitializedException ("Can't create editor for BeanFactory. Bean id : (" +
                                std::string (id) + "), editor name : (" + customEditorName + ").");
        }

        return true;
}

/**
 * Z tego co pamiętam, to jest jakiś chack, ktory czyści zmienne stanowe.
 */
void EditorService::onConstructorArgsBegin (MetaObject const *data)
{
        currentMapEditor = NULL;

        if (!data || data->getConstructorArgs ().empty ()) {
                return;
        }

        BeanFactory *beanFactory = getBVFContext ()->getCurrentBF ();

        if (!beanFactory) {
                // Gdy abstract
                return;
        }

        currentFieldIdx = -1;

        BFIndexedEditor *editor = new BFIndexedEditor ();
        editor->setBeanWrapper (cArgsBeanWrapper);

        currentIndexedEditor = editor;
        beanFactory->setCArgsEditor (currentIndexedEditor);
}

/**
 * Z tego co pamiętam, to jest jakiś chack, ktory czyści zmienne stanowe.
 */
void EditorService::onConstructorArgsEnd (MetaObject const *)
{
        currentMapEditor = NULL;
        currentIndexedEditor = NULL;
        currentFieldIdx = -1;
}

/**
 * Tu jest obsługiwana sytuacja, kiedy ktoś poda typ wartości (<value type="xyz">), który
 * jest inny niż standardowy zbiór skalarów (int, unsigned int, char, double, bool, string, text).
 * W takim wypadku odszukiwany jest bean o nazwie z atrybutu i wykorzystywany jako edytor.
 * Czyli <b>musi sie dać skastować</b> do Editor::IEditor.
 */
void EditorService::onValueData (DataKey const *dk, ValueData const *data)
{
        // Brak edytora, kiedy podano custom-editor, lub kiedy jest bark pól do edycji
        if (!currentMapEditor && !currentIndexedEditor) {
                return;
        }

        std::string type = toStr (data->getType ());
        BeanFactory *current = getBVFContext ()->getCurrentBF ();

        if (!current) {
                // Gdy abstract
                return;
        }

        Element element;
        element.add = (dk) ? (dk->add) : (false);

        if (type == "" || Factory::ScalarFactory::isTypeSupported (type.c_str ())) {
                if (currentIndexedEditor) {
                        ++currentFieldIdx;
                        return;
                }
        }
        else {
                BeanFactoryContainer *container = getBVFContext ()->getBeanFactoryContainer ();

                element.editor = ocast <Editor::IEditor *> (container->getSingleton (type.c_str ()));
                element.type = Element::EDITOR_FROM_BF;
        }

        if (currentIndexedEditor) {
                currentIndexedEditor->setElement (++currentFieldIdx, element);
        }
        else if (currentMapEditor) {
                currentMapEditor->addElement (/*toStr (dk->key), */element);
        }
}

/**
 * Posługując się analogią z XML, to odpowiada <ref bean="jakiesId">. Pobierany jest
 * BeanFactory i tym ID (szukany w obrębie mojegio kontener i zlinkowanych). Następnie
 * ubierane jest w FactoryEditor (bo potrzebny jest edytor, a nie fabryka) i następnie
 * ustawiany do głownego edytora (SimpleMapEditora w tym przypadku).
 */
void EditorService::onRefData (DataKey const *dk, RefData const *data)
{
        // Brak edytora, kiedy podano custom-editor, lub kiedy jest brak pól do edycji
        if (!currentMapEditor && !currentIndexedEditor) {
                return;
        }

        BeanFactory *current = getBVFContext ()->getCurrentBF ();

        // Gdy abstract
        if (!current) {
                return;
        }

        BeanFactoryContainer *container = getBVFContext ()->getBeanFactoryContainer ();
        std::string referenceName = toStr (data->getData ());

        Element element;
        element.add = (dk) ? (dk->add) : (false);

        // Specjalne referencje (referencja do kontenera).
        if (referenceName == REFERENCE_TO_CONTAINER_ITSELF) {
                element.singleton = Core::Variant (container);
                element.type = Element::EXTERNAL_SINGLETON;
        }
        else {
                Factory::IFactory *factory = container->getBeanFactory (referenceName, current);

                // Zwykłe beany zdefiniowane w XML
                if (factory) {
                        element.factory = factory;
                        element.type = Element::BEAN_FACTORY;
                }
                // Szukaj singletonu zewnętrznego w mapie siongletons
                else {
                        SparseVariantMap *singletons = container->getSingletons ();
                        SparseVariantMap::const_iterator i = singletons->find (referenceName.c_str ());

                        if (i != singletons->end ()) {
                                element.singleton = i->second;
                                element.type = Element::EXTERNAL_SINGLETON;
                        }

                }
        }

        if (element.type == Element::EMPTY) {
                throw BeanNotFullyInitializedException ("Can't resolve reference (" + toStr (data->getData ()) + ").");
        }

        if (currentIndexedEditor) {
                currentIndexedEditor->setElement (++currentFieldIdx, element);
        }
        else if (currentMapEditor) {
                currentMapEditor->addElement (/*toStr (dk->key),*/ element);
        }
}

/****************************************************************************/

void EditorService::onNullData (DataKey const *dk, NullData const *data)
{
        if (currentMapEditor) {
                Element element;
                element.add = (dk) ? (dk->add) : (false);
                currentMapEditor->addElement (element);
        }
}

/**
 * Pomocnicza wykorzystywana w  EditorService::onMappedMetaBegin. Tworzy instancję
 * Editor::SimpleMapEditor, która jest potem przypisywana na pole BeanFactory::setEditor.
 * Taki edytor ustawia potem pola nowoutworzonego beana.
 */
BFMapEditor *EditorService::createMappedEditor (bool isSingleton)
{
        BFMapEditor *editor = new BFMapEditor ();

        if (isSingleton) {
                editor->setBeanWrapper (beanWrapperConversionForSingletons);
        }
        else {
                editor->setBeanWrapper (beanWrapperConversionForPrototypes);
        }

        return editor;
}

/****************************************************************************/

BFIndexedEditor *EditorService::createIndexedEditor (bool isSingleton)
{
        BFIndexedEditor *editor = new BFIndexedEditor ();

        if (isSingleton) {
                editor->setBeanWrapper (beanWrapperConversionForSingletons);
        }
        else {
                editor->setBeanWrapper (beanWrapperConversionForPrototypes);
        }

        return editor;
}

}

