/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <Pointer.h>
#include <NoopEditor.h>

#include "metaStructure/model/MetaStructure.h"
#include "common/testHelpers/ContainerTestFactory.h"
#include "metaStructure/service/PrintService.h"
#include "metaStructure/service/MetaVisitor.h"
#include "beanFactory/service/ValueServiceHelper.h"
#include "ContainerFactory.h"
#include "beanFactory/service/BeanFactoryService.h"
#include "beanFactory/service/BeanFactoryInitService.h"
#include "beanFactory/service/MappedValueService.h"
#include "beanFactory/service/IndexedValueService.h"
#include "beanFactory/service/FactoryService.h"
#include "metaStructure/model/MetaObject.h"
#include "../beanWrapper/plugins/PropertyRWBeanWrapperPlugin.h"
#include "../beanWrapper/plugins/GetPutMethodRWBeanWrapperPlugin.h"
#include "../beanWrapper/plugins/MethodPlugin.h"
#include "../beanWrapper/plugins/ListPlugin.h"
#include "../beanWrapper/beanWrapper/BeanWrapper.h"
#include "../factory/ScalarFactory.h"
#include "../factory/ReflectionFactory.h"
#include "../factory/ChainFactory.h"
#include "../editor/TypeEditor.h"
#include "../editor/LexicalEditor.h"
#include "../editor/StringConstructorEditor.h"
#include "../editor/ChainEditor.h"
#include "../core/DebugContext.h"
#include "beanFactory/BeanFactoryContext.h"
#include "../editor/StreamEditor.h"
#include "../editor/StringFactoryMethodEditor.h"
#include "beanFactory/service/EditorService.h"
#include "beanFactory/service/SingletonInstantiateService.h"
#include "beanFactory/InternalSingletons.h"

using Editor::StringFactoryMethodEditor;

namespace Container {
using namespace Wrapper;

/****************************************************************************/

void ContainerFactory::init (BeanFactoryContainer *bfCont, MetaContainer *metaCont)
{
        MetaVisitor iteration;
        BeanFactoryVisitorContext context;
        InternalSingletons *internals = bfCont->getInternalSingletons ();
        context.setMetaContainer (metaCont);

        try {

                iteration.setContext (&context);

                BeanFactoryInitService bfService;
                bfService.setContext (&context);
                bfService.setDefaultBeanWrapper (internals->beanWrapperConversion);
                iteration.addService (&bfService);

                MappedValueService valMapService;
                valMapService.setContext (&context);
                ValueServiceHelper helper;
                helper.setDefaultValueFactory (internals->defaultValueFactory);
                valMapService.setValueServiceHelper (&helper);
                iteration.addService (&valMapService);

                IndexedValueService valIndexService;
                valIndexService.setContext (&context);
                valIndexService.setValueServiceHelper (&helper);
                iteration.addService (&valIndexService);

                EditorService editorService;
                editorService.setContext (&context);
                editorService.setDefaultBeanWrapper (internals->beanWrapperConversion);
                editorService.setNoopNoCopyEditor (internals->noopNoCopy);
                editorService.setCArgsBeanWrapper (internals->beanWrapperSimple);
                iteration.addService (&editorService);

                FactoryService factoryService;
                factoryService.setContext (&context);
                factoryService.setDefaultSingletonFactory (internals->defaultSingletonFactory);
                iteration.addService (&factoryService);

                SingletonInstantiateService sIService;
                sIService.setContext (&context);
                iteration.addService (&sIService);

#if CONTAINER_PRINT_META
                PrintMetaService printService;
                printService.setContext (&context);
                iteration.addService (&printService);
#endif

                context.reset ();
                context.setBeanFactoryContainer (bfCont);
                context.setBeanFactoryMap (&bfCont->getBeanFactoryMap ());

                metaCont->updateParents ();
                MetaDeque sorted = metaCont->topologicalSort ();
                iteration.visit (&sorted);
        }
        catch (NoSuchBeanException &e) {
                e.addMessage ("ContainerFactory::createContainer : [" + bfCont->toString () + "].");
                throw;
        }
        catch (Core::Exception &e) {
                e.addMessage ("ContainerFactory::createContainer : [" + bfCont->toString () + "].");
                throw;
        }
}

/****************************************************************************/

Ptr <BeanFactoryContainer> ContainerFactory::create (Ptr <MetaContainer> metaCont,
                                                     bool storeMetaContainer,
                                                     BeanFactoryContainer *linkedParent)
{
        Ptr <BeanFactoryContainer> container = boost::make_shared <BeanFactoryContainer> (new SparseVariantMap (), createSingletons ());

        if (linkedParent) {
                container->setLinked (linkedParent);
                metaCont->setLinked (linkedParent->getMetaContainer ());
        }

        if (storeMetaContainer) {
                container->setMetaContainer (metaCont);
        }

        return container;
}


/****************************************************************************/

Ptr <BeanFactoryContainer> ContainerFactory::createAndInit (Ptr <MetaContainer> metaCont,
                                                            bool storeMetaContainer,
                                                            BeanFactoryContainer *linkedParent)
{
        Ptr <BeanFactoryContainer> container = create (metaCont, storeMetaContainer,linkedParent);
        init (container.get (), metaCont.get ());
        return container;
}

/****************************************************************************/

InternalSingletons *ContainerFactory::createSingletons ()
{
        InternalSingletons *internals = new InternalSingletons;

        internals->noop = new Editor::NoopEditor ();
        internals->noopNoCopy = new Editor::NoopEditor (false);

        // Dodaj reflection factory.
        Factory::ScalarFactory *factS = new Factory::ScalarFactory ();
        Factory::ReflectionFactory *factR = new Factory::ReflectionFactory ();
        Factory::ChainFactory *fact = new Factory::ChainFactory (true);
        fact->addFactory (factS);
        fact->addFactory (factR);

        internals->defaultSingletonFactory = fact;
        internals->defaultValueFactory = factS;
        internals->beanWrapperSimple = Wrapper::BeanWrapper::create ();

        BeanWrapper *beanWrapper = new BeanWrapper (true);
        beanWrapper->addPlugin (new PropertyRWBeanWrapperPlugin ());
        beanWrapper->addPlugin (new GetPutMethodRWBeanWrapperPlugin ());
        beanWrapper->addPlugin (new MethodPlugin (MethodPlugin::IMMEDIATE_CALL));

/*--------------------------------------------------------------------------*/

        Editor::TypeEditor *typeEditor = new Editor::TypeEditor (true);
        typeEditor->setEqType (new Editor::NoopEditor ());
        typeEditor->setNullType (new Editor::NoopEditor ());

        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (int), new Editor::StreamEditor <std::string, int> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (double), new Editor::LexicalEditor <std::string, double> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (float), new Editor::LexicalEditor <std::string, float> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (char), new Editor::LexicalEditor <std::string, char> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (bool), new Editor::LexicalEditor <std::string, bool> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (unsigned int), new Editor::StreamEditor <std::string, unsigned int> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (unsigned char), new Editor::StreamEditor <std::string, unsigned char> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (long), new Editor::StreamEditor <std::string, long> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (unsigned long), new Editor::StreamEditor <std::string, unsigned long> ()));

        // Core::String <-> std::string
        typeEditor->addType (Editor::TypeEditor::Type (typeid (Core::String), typeid (std::string), new Editor::LexicalEditor <Core::String, std::string> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (Core::String), new Editor::LexicalEditor <std::string, Core::String> ()));

        // StringCon.
        Editor::StringConstructorEditor *strCon = new Editor::StringConstructorEditor ();
        Editor::StringFactoryMethodEditor *conversionMethodEditor = new Editor::StringFactoryMethodEditor ();
        Editor::ChainEditor *chain = new Editor::ChainEditor (true);

        chain->addEditor (typeEditor);
        chain->addEditor (strCon);
        chain->addEditor (conversionMethodEditor);
        chain->addEditor (new Editor::NoopEditor ());

        beanWrapper->setEditor (chain);

/*--------------------------------------------------------------------------*/

        internals->beanWrapperConversion = beanWrapper;
        internals->mainTypeEditor = typeEditor;
        internals->mainMethodConversionEditor = conversionMethodEditor;

        return internals;
}

}
