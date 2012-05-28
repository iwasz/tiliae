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
#include "../../../factory/testHelpers/SillyFactory.h"

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
        defaultMappedEditor = ocast <Ptr <Editor::IEditor> > (v);

        v = (*singletons)[NOOP_EDITOR_NAME];
        noopEditor = ocast <Ptr <Editor::IEditor> > (v);

        v = (*singletons)[NOOP_NO_COPY_EDITOR_NAME];
        noopNoCopyEditor = ocast <Ptr <Editor::IEditor> > (v);

        v = (*singletons)[BEAN_WRAPPER_W_CONVERSION];
        defaultBeanWrapper = ocast <Ptr <Wrapper::BeanWrapper> > (v);
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

        if (!beanFactory) {
                // Gdy abstract
                return false;
        }

        std::string customEditorName = meta->getEditor ();
        Editor::IEditor *editor = NULL;

        if (!customEditorName.empty ()) {
                Ptr <BeanFactoryContainer> container = getBVFContext ()->getBeanFactoryContainer ();
                Ptr <BeanFactory> fact = container->getBeanFactory (customEditorName, beanFactory);
                editor = new Editor::LazyEditor (fact);
        }
        else {
                editor = currentEditor = createMappedEditor ();
        }

        if (!editor) {
                throw BeanNotFullyInitializedException ("Can't create editor for BeanFactory. Bean id : (" + meta->getId () + "), editor name : (" + meta->getEditor () + ").");
        }

        beanFactory->setEditor (editor, true);
        return true;
}

/**
 * Pomocnicza wykorzystywana w  EditorService::onMappedMetaBegin. Tworzy instancję
 * Editor::SimpleMapEditor, która jest potem przypisywana na pole BeanFactory::setEditor.
 * Taki edytor ustawia potem pola nowoutworzonego beana.
 */
Editor::SimpleMapEditor *EditorService::createMappedEditor ()
{
        Editor::SimpleMapEditor *editor = new Editor::SimpleMapEditor ();
        editor->setDefaultEditor (noopEditor);
        editor->setBeanWrapper (defaultBeanWrapper);
        return editor;
}

/**
 * Z tego co pamiętam, to jest jakiś chack, ktory czyści zmienne stanowe.
 */
void EditorService::onConstructorArgsBegin (IMeta *data)
{
        currentEditor = NULL;
}

/**
 * Z tego co pamiętam, to jest jakiś chack, ktory czyści zmienne stanowe.
 */
void EditorService::onConstructorArgsEnd (IMeta *data)
{
        currentEditor = NULL;
}

/**
 * Tu jest obsługiwana sytuacja, kiedy ktoś poda typ wartości (<value type="xxx">), który
 * jest inny niż standardowy zbiór skalarów (int, unsigned int, char, double, bool, string, text).
 * W takim wypadku odszukiwany jest bean o nazwie z atrybutu i wykorzystywany jako edytor.
 * Czyli <b>musi sie dać skastować</b> do Editor::IEditor.
 * TODO Zdublowany kod (chyba chodzi o IndexedEditorService).
 */
void EditorService::onValueData (std::string const &key, ValueData *data)
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
        currentEditor->setEditor (key, tmpEditor);
//        currentFieldName.clear ();
}

/**
 * Posługując się analogią z XML, to odpowiada <ref bean="jakiesId">. Pobierany jest
 * BeanFactory i tym ID (szukany w obrębie mojegio kontener i zlinkowanych). Następnie
 * ubierane jest w FactoryEditor (bo potrzebny jest edytor, a nie fabryka) i następnie
 * ustawiany do głownego edytora (SimpleMapEditora w tym przypadku).
 * TODO zdublowany kod!
 */
void EditorService::onRefData (std::string const &key, RefData *data)
{
        // Brak edytora, kiedy podano custom-editor, lub kiedy jest brak pól do edycji
        if (!currentEditor) {
                return;
        }

        Ptr <BeanFactory> current = getBVFContext ()->getCurrentBF ();

        if (!current) {
                return;
        }

        Ptr <BeanFactoryContainer> container = getBVFContext ()->getBeanFactoryContainer ();

        std::string referenceName = data->getData ();
        Ptr <Factory::IFactory> factory;

        // Specjalne referencje
        if (referenceName == REFERENCE_TO_CONTAINER_ITSELF) {
                factory = boost::make_shared <Factory::SillyFactory> (Core::Variant (container));
        }

        // Zwykłe beany zdefiniowane w XML
        else {
                factory = container->getBeanFactory (referenceName, current);
        }

        // Singletony w mapie singletons.
        if (!factory) {
                Ptr <Core::VariantMap> singletons = container->getSingletons ();
                Core::VariantMap::const_iterator i = singletons->find (referenceName);

                if (i != singletons->end ()) {
                        factory = boost::make_shared <Factory::SillyFactory> (i->second);
                }
        }

        if (!factory) {
                throw BeanNotFullyInitializedException ("Can't resolve reference (" + data->getData () + ").");
        }

        Ptr <Editor::IEditor> tmpEditor = boost::make_shared <Editor::FactoryEditor> (noopNoCopyEditor, factory);
        currentEditor->setEditor (key, tmpEditor);

}

}
