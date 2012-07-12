/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/make_shared.hpp>
#include "MappedEditorService.h"
#include "metaStructure/model/MetaStructure.h"
#include "common/Exceptions.h"
#include "Defs.h"
#include "../../../core/variant/Variant.h"
#include "../../../core/Typedefs.h"
#include "../../../core/variant/Cast.h"
#include "../../../beanWrapper/beanWrapper/BeanWrapper.h"
#include "../../../factory/ScalarFactory.h"
#include "../../../editor/LazyEditor.h"

namespace Container {
using namespace Core;

/**
 * Keszuja sobie w zmiennych pomocniczych singletony, które są na mapie podaje jako argumet
 * wejściowy. Dzięki temu nie musi ich za kazdym razem szukać. Te singletony służą do
 * konstruowania edytora, który potem ustawia pola nowoutworzonego beana.
 */
void MappedEditorService::init (Core::VariantMap *singletons)
{
        Variant v = (*singletons)[BEAN_WRAPPER_W_CONVERSION];
        defaultBeanWrapper = ocast <Wrapper::BeanWrapper *> (v);
}

/**
 * Początek procesowania MappedMeta (odpowiada tagom <map> oraz <bean>). Tu wpadają
 * obiekty MappedMeta będące w obrębie jednego kontenera (te ze zlinkowanych nie
 * wpadają). Tworzony jest Editor::SimpleMapEditor lub jeśli user sobie zażyczył,
 * ustawiany jest jakiś inny customowy (atrybut editor). Edytor jest ustawiany do
 * odpowiedniego BeanFactory.
 */
bool MappedEditorService::onMappedMetaBegin (MappedMeta *meta)
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
                BeanFactoryContainer *container = getBVFContext ()->getBeanFactoryContainer ();
                Ptr <BeanFactory> fact = container->getBeanFactory (customEditorName, beanFactory);
                editor = new Editor::LazyEditor (fact.get ());
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
BFMapEditor *MappedEditorService::createMappedEditor ()
{
        BFMapEditor *editor = new BFMapEditor ();
        editor->setBeanWrapper (defaultBeanWrapper);
        return editor;
}

/**
 * Z tego co pamiętam, to jest jakiś chack, ktory czyści zmienne stanowe.
 */
void MappedEditorService::onConstructorArgsBegin (IMeta *data)
{
        currentEditor = NULL;
}

/**
 * Z tego co pamiętam, to jest jakiś chack, ktory czyści zmienne stanowe.
 */
void MappedEditorService::onConstructorArgsEnd (IMeta *data)
{
        currentEditor = NULL;
}

/**
 * Tu jest obsługiwana sytuacja, kiedy ktoś poda typ wartości (<value type="xyz">), który
 * jest inny niż standardowy zbiór skalarów (int, unsigned int, char, double, bool, string, text).
 * W takim wypadku odszukiwany jest bean o nazwie z atrybutu i wykorzystywany jako edytor.
 * Czyli <b>musi sie dać skastować</b> do Editor::IEditor.
 */
void MappedEditorService::onValueData (std::string const &key, ValueData *data)
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
        currentEditor->setElement (key, element);
}

/**
 * Posługując się analogią z XML, to odpowiada <ref bean="jakiesId">. Pobierany jest
 * BeanFactory i tym ID (szukany w obrębie mojegio kontener i zlinkowanych). Następnie
 * ubierane jest w FactoryEditor (bo potrzebny jest edytor, a nie fabryka) i następnie
 * ustawiany do głownego edytora (SimpleMapEditora w tym przypadku).
 */
void MappedEditorService::onRefData (std::string const &key, RefData *data)
{
        // Brak edytora, kiedy podano custom-editor, lub kiedy jest brak pól do edycji
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

        currentEditor->setElement (key, element);
}

}
