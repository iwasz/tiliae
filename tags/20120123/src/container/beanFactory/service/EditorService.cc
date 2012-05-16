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
#include "../../../editor/LazyEditor.h"
#include "../../../editor/FactoryEditor.h"
#include "../../../beanWrapper/beanWrapper/BeanWrapper.h"
#include "../../../beanWrapper/misc/SimpleMapEditor.h"

namespace Container {
using namespace Core;

/**
 * Keszuja sobie w zmiennych pomocniczych singletony, które są na mapie podaje jako argumet
 * wejściowy. Dzięki temu nie musi ich za kazdym razem szukać. Te singletony służą do
 * konstruowania edytora, który potem ustawia pola nowoutworzonego beana.
 */
void EditorService::init (Core::VariantMap *singletons)
{
        Core::Variant v = (*singletons)[DEFAULT_MAPPED_EDITOR_NAME];
        defaultMappedEditor = vcast <Ptr <Editor::IEditor> > (v);

        v = (*singletons)[NOOP_EDITOR_NAME];
        noopEditor = vcast <Ptr <Editor::IEditor> > (v);

        v = (*singletons)[NOOP_NO_COPY_EDITOR_NAME];
        noopNoCopyEditor = vcast <Ptr <Editor::IEditor> > (v);

        v = (*singletons)[BEAN_WRAPPER_W_CONVERSION];
        defaultBeanWrapper = vcast <Ptr <Wrapper::BeanWrapper> > (v);
}

/**
 * Początek procesowania MappedMeta (odpowiada tagom <map> oraz <bean>). Tu wpadają
 * obiekty MappedMeta będące w obrębie jednego kontenera (te ze zlinkowanych nie
 * wpadają). Tworzony jest Editor::SimpleMapEditor lub jeśli user sobie zażyczył,
 * ustawiany jest jakiś inny customowy (atrybut editor). Edytor jest ustawiany do
 * odpowiedniego BeanFactory.
 */
bool EditorService::onMappedMetaBegin (MappedMeta *meta)
{
        // Tu powinien być beanFactory odpowiadający podanemu meta w parametrze.
        Ptr <BeanFactory> beanFactory = getBVFContext ()->getCurrentBF ();
        assert (beanFactory);
        currentFieldName.clear ();

        std::string customEditorName = meta->getEditor ();
        Ptr <Editor::IEditor> editor;

        if (!customEditorName.empty ()) {
                Ptr <BeanFactoryContainer> container = getBVFContext ()->getBeanFactoryContainer ();
                Ptr <BeanFactory> fact = container->getBeanFactory (customEditorName, beanFactory);
                editor = boost::make_shared <Editor::LazyEditor> (fact);
        }
        else {
                editor = currentEditor = createMappedEditor ();
        }

        if (!editor) {
                throw BeanNotFullyInitializedException ("Can't create editor for BeanFactory. Bean id : (" + meta->getId () + "), editor name : (" + meta->getEditor () + ").");
        }

        beanFactory->setEditor (editor);
        return true;
}

/**
 * Pomocnicza wykorzystywana w  EditorService::onMappedMetaBegin. Tworzy instancję
 * Editor::SimpleMapEditor, która jest potem przypisywana na pole BeanFactory::setEditor.
 * Taki edytor ustawia potem pola nowoutworzonego beana.
 */
Ptr <Editor::SimpleMapEditor> EditorService::createMappedEditor ()
{
        Ptr <Editor::SimpleMapEditor> editor = boost::make_shared <Editor::SimpleMapEditor> ();
        editor->setDefaultEditor (noopEditor);
        editor->setBeanWrapper (defaultBeanWrapper);
        return editor;
}

/**
 * Z tego co pamiętam, to jest jakiś chack, ktory czyści zmienne stanowe.
 */
void EditorService::onConstructorArgsBegin (IMeta *data)
{
        currentEditor.reset ();
        currentFieldName.clear ();
}

/**
 * Z tego co pamiętam, to jest jakiś chack, ktory czyści zmienne stanowe.
 */
void EditorService::onConstructorArgsEnd (IMeta *data)
{
        currentEditor.reset ();
        currentFieldName.clear ();
}

/**
 * Z wejściowego obiektu typu MapElem pobierany jest tylko klucz, czyli nazwa
 * pola pod jakim wartość tego elementu ma być ustawiona. Czyli przekładając to na
 * XML, zapamiętywany jest <property name="key" ... /> do późniejszego użycia.
 */
void EditorService::onMapElem (MapElem *data)
{
        currentFieldName = data->getKey ();
}

/**
 * Tu jest obsługiwana sytuacja, kiedy ktoś poda typ wartości (<value type="xxx">), który
 * jest inny niż standardowy zbiór skalarów (int, unsigned int, char, double, bool, string, text).
 * W takim wypadku odszukiwany jest bean o nazwie z atrybutu i wykorzystywany jako edytor.
 * Czyli <b>musi sie dać skastować</b> do Editor::IEditor.
 * TODO Zdublowany kod (chyba chodzi o IndexedEditorService).
 */
void EditorService::onValueData (ValueData *data)
{
        // Brak edytora, kiedy podano custom-editor, lub kiedy jest bark pól do edycji
        if (!currentEditor) {
                return;
        }

        std::string type = data->getType ();
        Ptr <BeanFactory> current = getBVFContext ()->getCurrentBF ();

        // TODO Z tym stringami to trzeba jakoś sprytniej wymyślić.
        if (type == "" ||
                type == "int" ||
                type == "unsigned int" ||
                type == "char" ||
                type == "double" ||
                type == "bool" ||
                type == "string" ||
                type == "String" ||
                type == "text") {
                return;
        }

        Ptr <BeanFactoryContainer> container = getBVFContext ()->getBeanFactoryContainer ();
        Ptr <BeanFactory> beanFactory = container->getBeanFactory (type, current);

        if (!beanFactory) {
                throw BeanNotFullyInitializedException ("Can't resolve editor for type [" + type + "].");
        }

        Ptr <Editor::IEditor> tmpEditor = boost::make_shared <Editor::LazyEditor> (beanFactory);
        currentEditor->setEditor (currentFieldName, tmpEditor);
        currentFieldName.clear ();
}

/**
 * Posługując się analogią z XML, to odpowiada <ref bean="jakiesId">. Pobierany jest
 * BeanFactory i tym ID (szukany w obrębie mojegio kontener i zlinkowanych). Następnie
 * ubierane jest w FactoryEditor (bo potrzebny jest edytor, a nie fabryka) i następnie
 * ustawiany do głownego edytora (SimpleMapEditora w tym przypadku).
 * TODO zdublowany kod!
 */
void EditorService::onRefData (RefData *data)
{
        // Brak edytora, kiedy podano custom-editor, lub kiedy jest brak pól do edycji
        if (!currentEditor) {
                return;
        }

        Ptr <BeanFactory> current = getBVFContext ()->getCurrentBF ();
        Ptr <BeanFactoryContainer> container = getBVFContext ()->getBeanFactoryContainer ();
        Ptr <BeanFactory> beanFactory = container->getBeanFactory (data->getData (), current);

        if (!beanFactory) {
                throw BeanNotFullyInitializedException ("Can't resolve reference (" + data->getData () + ").");
        }

        Ptr <Editor::IEditor> tmpEditor = boost::make_shared <Editor::FactoryEditor> (noopNoCopyEditor, beanFactory);
//        assert (currentEditor, "!currentEditor in EditorService::onValueData. This should be set in EditorService::onMappedMetaBegin.");
        currentEditor->setEditor (currentFieldName, tmpEditor);
        currentFieldName.clear ();
}

}