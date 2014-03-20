/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include "core/Pointer.h"
#include "editor/NoopEditor.h"
#include "container/metaStructure/model/MetaStructure.h"
#include "container/common/testHelpers/ContainerTestFactory.h"
#include "container/metaStructure/service/PrintService.h"
#include "container/metaStructure/service/MetaVisitor.h"
#include "container/beanFactory/service/ValueServiceHelper.h"
#include "container/ContainerFactory.h"
#include "container/beanFactory/service/BeanFactoryService.h"
#include "container/beanFactory/service/BeanFactoryInitService.h"
#include "container/beanFactory/service/MappedValueService.h"
#include "container/beanFactory/service/IndexedValueService.h"
#include "container/beanFactory/service/FactoryService.h"
#include "container/metaStructure/model/MetaObject.h"
#include "beanWrapper/plugins/PropertyRWBeanWrapperPlugin.h"
#include "beanWrapper/plugins/GetPutMethodRWBeanWrapperPlugin.h"
#include "beanWrapper/plugins/MethodPlugin.h"
#include "beanWrapper/plugins/ListPlugin.h"
#include "beanWrapper/beanWrapper/BeanWrapper.h"
#include "factory/ScalarFactory.h"
#include "factory/ReflectionFactory.h"
#include "factory/ChainFactory.h"
#include "editor/TypeEditor.h"
#include "editor/LexicalEditor.h"
#include "editor/ChainEditor.h"
#include "core/DebugContext.h"
#include "container/beanFactory/BeanFactoryContext.h"
#include "editor/StreamEditor.h"
#include "editor/StringFactoryMethodEditor.h"
#include "container/beanFactory/service/EditorService.h"
#include "container/beanFactory/service/SingletonInstantiateService.h"
#include "container/beanFactory/InternalSingletons.h"
#include "container/beanFactory/service/BFStringConstructorEditor.h"

using Editor::StringFactoryMethodEditor;
using Container::BFStringConstructorEditor;

namespace Container {
using namespace Wrapper;

/****************************************************************************/

void ContainerFactory::init (BeanFactoryContainer *bfCont, MetaContainer *metaCont)
{
        MetaVisitor iteration;
        BeanFactoryVisitorContext context;
        InternalSingletons *internals = bfCont->getInternalSingletons ();
        context.setMetaContainer (metaCont);
        Core::ArrayRegionAllocator <char> *memoryAllocator = bfCont->getMemoryAllocator ();
        bfCont->setGlobalInitMethod (metaCont->getGlobalInitMethod ());
        bfCont->setGlobalIdAwareMethod (metaCont->getGlobalIdAwareMethod ());

        try {

                iteration.setContext (&context);

                BeanFactoryInitService bfService;
                bfService.setContext (&context);
//                bfService.setDefaultBeanWrapper (internals->beanWrapperConversionForSingletons);
                bfService.setDefaultBeanWrapper (internals->beanWrapperForMethods);
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
                editorService.setBeanWrapperConversionForSingletons (internals->beanWrapperConversionForSingletons);
                editorService.setBeanWrapperConversionForPrototypes (internals->beanWrapperConversionForPrototypes);
                editorService.setNoopNoCopyEditor (internals->noopNoCopy);
                editorService.setCArgsBeanWrapper (internals->beanWrapperSimple);
                iteration.addService (&editorService);

                FactoryService factoryService;
                factoryService.setContext (&context);
                factoryService.setDefaultSingletonFactory (internals->defaultSingletonFactory);
                factoryService.setDefaultPrototypeFactory (internals->defaultPrototypeFactory);
                iteration.addService (&factoryService);

                SingletonInstantiateService sIService (memoryAllocator);
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
                                                     bool storeConfigurationForLinked,
                                                     BeanFactoryContainer *linkedParent)
{
        Ptr <BeanFactoryContainer> container = std::make_shared <BeanFactoryContainer> ();

        if (!linkedParent) {
                container->setInternalSingletons (createSingletons (container->getMemoryAllocator (), container->getSingletons ()));
        }

        if (linkedParent) {
                container->setInternalSingletons (linkedParent->getInternalSingletons ());
                container->setLinked (linkedParent);
                metaCont->setLinked (linkedParent->getMetaContainer ());
        }

        if (storeConfigurationForLinked) {
                container->setMetaContainer (metaCont);
        }

        return container;
}


/****************************************************************************/

Ptr <BeanFactoryContainer> ContainerFactory::createAndInit (Ptr <MetaContainer> metaCont,
                                                            bool storeConfigurationForLinked,
                                                            BeanFactoryContainer *linkedParent)
{
        Ptr <BeanFactoryContainer> container = create (metaCont, storeConfigurationForLinked,linkedParent);
        init (container.get (), metaCont.get ());
        return container;
}

/****************************************************************************/

InternalSingletons *ContainerFactory::createSingletons (Core::IAllocator *memoryAllocator, SparseVariantMap *singletons)
{
        InternalSingletons *internals = new InternalSingletons;

        internals->noop = new Editor::NoopEditor ();
        internals->noopNoCopy = new Editor::NoopEditor (false);

        // Dodaj reflection factory.
        Factory::ScalarFactory *factS = new Factory::ScalarFactory ();
        Factory::ReflectionFactory *factR = new Factory::ReflectionFactory (memoryAllocator);
        Factory::ChainFactory *fact = new Factory::ChainFactory (true);
        fact->addFactory (factS);
        fact->addFactory (factR);

        internals->defaultSingletonFactory = fact;
        internals->defaultValueFactory = factS;

        // Dla prototpów ReflectionFactory bez alokatora (czyli alokuje na heapie).
        factS = new Factory::ScalarFactory ();
        factR = new Factory::ReflectionFactory ();
        fact = new Factory::ChainFactory (true);
        fact->addFactory (factS);
        fact->addFactory (factR);

        internals->defaultPrototypeFactory = fact;
        internals->beanWrapperSimple = Wrapper::BeanWrapper::create ();

/*--------------------------------------------------------------------------*/

        BeanWrapper *beanWrapper = new BeanWrapper (true);
        beanWrapper->addPlugin (new PropertyRWBeanWrapperPlugin ());
        beanWrapper->addPlugin (new GetPutMethodRWBeanWrapperPlugin ());
        beanWrapper->addPlugin (new MethodPlugin (MethodPlugin::IMMEDIATE_CALL));

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

#ifdef WITH_CORE_STRING
        // Core::String <-> std::string
        typeEditor->addType (Editor::TypeEditor::Type (typeid (Core::String), typeid (std::string), new Editor::LexicalEditor <Core::String, std::string> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (Core::String), new Editor::LexicalEditor <std::string, Core::String> ()));
#endif

        // StringCon.
        BFStringConstructorEditor *strCon = new BFStringConstructorEditor (singletons, memoryAllocator);
        Editor::StringFactoryMethodEditor *conversionMethodEditor = new Editor::StringFactoryMethodEditor ();
        Editor::ChainEditor *chain = new Editor::ChainEditor (true);

        chain->addEditor (typeEditor);
        chain->addEditor (strCon);
        chain->addEditor (conversionMethodEditor);
        chain->addEditor (new Editor::NoopEditor ());

        beanWrapper->setEditor (chain);
        internals->beanWrapperConversionForSingletons = beanWrapper;

/*--------------------------------------------------------------------------*/

        beanWrapper = new BeanWrapper (true);
        beanWrapper->addPlugin (new PropertyRWBeanWrapperPlugin ());
        beanWrapper->addPlugin (new GetPutMethodRWBeanWrapperPlugin ());
        beanWrapper->addPlugin (new MethodPlugin (MethodPlugin::IMMEDIATE_CALL));

        internals->strCon_BW_Proto = strCon = new BFStringConstructorEditor (singletons, memoryAllocator);
        chain = new Editor::ChainEditor (false);
        chain->addEditor (typeEditor);
        chain->addEditor (strCon);
        chain->addEditor (conversionMethodEditor);
        chain->addEditor (internals->noop);

        beanWrapper->setEditor (chain);

        internals->beanWrapperConversionForPrototypes = beanWrapper;

/*--------------------------------------------------------------------------*/

        beanWrapper = new BeanWrapper (true);
        beanWrapper->addPlugin (new MethodPlugin (MethodPlugin::METHOD));
        internals->beanWrapperForMethods = beanWrapper;

/*--------------------------------------------------------------------------*/

        internals->mainTypeEditor = typeEditor;
        internals->mainMethodConversionEditor = conversionMethodEditor;

        return internals;
}

}
