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
#include "metaStructure/service/ParentService.h"
#include "beanFactory/service/ValueServiceHelper.h"
#include "beanFactory/service/EditorService.h"
#include "Defs.h"
#include "ContainerFactory.h"
#include "beanFactory/service/BeanFactoryService.h"
#include "beanFactory/service/BeanFactoryInitService.h"
#include "beanFactory/service/MappedValueService.h"
#include "beanFactory/service/IndexedValueService.h"
#include "beanFactory/service/FactoryService.h"
#include "beanFactory/service/BeanStackUpdateService.h"
#include "beanFactory/service/ListEditorService.h"
#include "metaStructure/model/meta/IMeta.h"
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

using Editor::StringFactoryMethodEditor;

//#define CONTAINER_PRINT_META 1

namespace Container {
using namespace Wrapper;

ContainerFactory::ContainerFactory ()
{
        try {

                iteration0 = MetaVisitor::create ();
                iteration0->setContext (&context);

                Ptr <IMetaService> service = ParentService::create ();
                service->setContext (&context);
                iteration0->addService (service);

/*------1st-iteration-------------------------------------------------------*/

                iteration1 = MetaVisitor::create ();
                iteration1->setContext (&context);

//                Ptr <IMetaService> service = ParentService::create ();
//                service->setContext (&context);
//                iteration1->addService (service);

                Ptr <Wrapper::BeanWrapper> beanWrapper = createBeanWrapper ();

                Ptr <BeanFactoryInitService> bfService = BeanFactoryInitService::create ();
                bfService->setContext (&context);
                //Ptr <Wrapper::BeanWrapper> beanWrapper = Wrapper::BeanWrapper::create ();
                bfService->setDefaultBeanWrapper (beanWrapper);
                iteration1->addService (bfService);

                singletons = createSingletons ();
                singletons->operator[] (BEAN_WRAPPER_W_CONVERSION) = Core::Variant (beanWrapper);

                Ptr <MappedValueService> valMapService = MappedValueService::create ();
                valMapService->setContext (&context);
                Ptr <ValueServiceHelper> helper = ValueServiceHelper::create ();
                helper->setSingletonMap (singletons);
                valMapService->setValueServiceHelper (helper);
                iteration1->addService (valMapService);

                Ptr <IndexedValueService> valIndexService = IndexedValueService::create ();
                valIndexService->setContext (&context);
                helper->setSingletonMap (singletons);
                valIndexService->setValueServiceHelper (helper);
                iteration1->addService (valIndexService);

/*------2nd-iteration-------------------------------------------------------*/

                iteration2 = MetaVisitor::create ();
                iteration2->setContext (&context);

                Ptr <BeanStackUpdateService> updService = BeanStackUpdateService::create ();
                updService->setContext (&context);
                iteration2->addService (updService);

                Ptr <EditorService> editorService = EditorService::create ();
                editorService->setContext (&context);
                editorService->init (singletons.get ());
                iteration2->addService (editorService);

                Ptr <ListEditorService> listEditorService = ListEditorService::create ();
                listEditorService->setContext (&context);
                listEditorService->init (singletons.get ());
                iteration2->addService (listEditorService);

                Ptr <FactoryService> factoryService = FactoryService::create ();
                factoryService->setContext (&context);
                factoryService->init (singletons.get ());
                iteration2->addService (factoryService);

#if CONTAINER_PRINT_META
                Ptr <PrintMetaService> printService = PrintMetaService::create ();
                printService->setContext (&context);
                iteration2->addService (printService);
#endif
        }
        catch (Core::Exception &e) {
                e.addMessage ("Error @ ContainerFactory::ContainerFactory.");
                throw;
        }
}

/****************************************************************************/

Ptr <Core::VariantMap> ContainerFactory::createSingletons ()
{
        Ptr <Core::VariantMap> map = boost::make_shared <Core::VariantMap> ();

        Ptr <Editor::IEditor> noop = boost::make_shared <Editor::NoopEditor> ();
        Ptr <Editor::IEditor> noopNoCopy = boost::make_shared <Editor::NoopEditor> (false);

        map->operator[] (DEFAULT_MAPPED_EDITOR_NAME) = Core::Variant (noop);
        map->operator[] (DEFAULT_INDEXED_EDITOR_NAME) = Core::Variant (noop);
        map->operator[] (NOOP_EDITOR_NAME) = Core::Variant (noop);
        map->operator[] (NOOP_NO_COPY_EDITOR_NAME) = Core::Variant (noopNoCopy);

        // Dodaj reflection factory.
        Ptr <Factory::ScalarFactory> factS = boost::make_shared <Factory::ScalarFactory> ();
        Ptr <Factory::ReflectionFactory> factR = boost::make_shared <Factory::ReflectionFactory> ();
        Ptr <Factory::ChainFactory> fact = boost::make_shared <Factory::ChainFactory> ();
        fact->addFactory (factS);
        fact->addFactory (factR);
        map->operator[] (DEFAULT_OBJECT_FACTORY_NAME) = Core::Variant (fact);
        map->operator[] (DEFAULT_VALUE_FACTORY_NAME) = Core::Variant (factS);

        map->operator[] (BEAN_WRAPPER_SIMPLE) = Core::Variant (Wrapper::BeanWrapper::create ());

        return map;
}

/****************************************************************************/

Ptr <Wrapper::BeanWrapper> ContainerFactory::createBeanWrapper ()
{
        Ptr <BeanWrapper> beanWrapper = boost::make_shared <BeanWrapper> ();
        Ptr <BeanWrapperPluginList> pluginList = boost::make_shared <BeanWrapperPluginList> ();

        beanWrapper->addPlugin (new PropertyRWBeanWrapperPlugin ());
        beanWrapper->addPlugin (new GetPutMethodRWBeanWrapperPlugin ());
        beanWrapper->addPlugin (new MethodPlugin (MethodPlugin::IMMEDIATE_CALL));

/*--------------------------------------------------------------------------*/

        Ptr <Editor::TypeEditor> editor = boost::make_shared <Editor::TypeEditor> ();
        Ptr <Editor::IEditor> noop = boost::make_shared <Editor::NoopEditor> ();
        editor->setEqType (noop);
        editor->setNullType (noop);

        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (int), boost::make_shared <Editor::StreamEditor <std::string, int> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (double), boost::make_shared <Editor::LexicalEditor <std::string, double> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (float), boost::make_shared <Editor::LexicalEditor <std::string, float> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (char), boost::make_shared <Editor::LexicalEditor <std::string, char> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (bool), boost::make_shared <Editor::LexicalEditor <std::string, bool> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (unsigned int), boost::make_shared <Editor::StreamEditor <std::string, unsigned int> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (unsigned char), boost::make_shared <Editor::StreamEditor <std::string, unsigned char> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (long), boost::make_shared <Editor::StreamEditor <std::string, long> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (unsigned long), boost::make_shared <Editor::StreamEditor <std::string, unsigned long> > ()));

        // Core::String <-> std::string
        editor->addType (Editor::TypeEditor::Type (typeid (Core::String), typeid (std::string), boost::make_shared <Editor::LexicalEditor <Core::String, std::string> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (Core::String), boost::make_shared <Editor::LexicalEditor <std::string, Core::String> > ()));

        // StringCon.
        Ptr <Editor::StringConstructorEditor> strCon = boost::make_shared <Editor::StringConstructorEditor> ();

        conversionMethodEditor = boost::make_shared <Editor::StringFactoryMethodEditor> ();

        Editor::ChainEditor *chain = new Editor::ChainEditor ();

        chain->addEditor (editor);
        chain->addEditor (strCon);
        chain->addEditor (conversionMethodEditor);
        chain->addEditor (noop);

/*--------------------------------------------------------------------------*/

        beanWrapper->setEditor (chain);
        return beanWrapper;
}

/****************************************************************************/

Ptr <BeanFactoryContainer> ContainerFactory::create ()
{
        Ptr <BeanFactoryContainer> container = boost::make_shared <BeanFactoryContainer> ();
        container->setSingletons (singletons);
        Ptr <BeanFactoryMap> map = boost::make_shared <BeanFactoryMap> ();
        container->setBeanFactoryMap (map);
        return container;
}

/****************************************************************************/

void ContainerFactory::fill (Ptr <BeanFactoryContainer> bfCont, Ptr <MetaContainer> metaCont)
{
        BeanFactoryContext ctx;

        try {
                context.reset ();
                context.setBeanFactoryContainer (bfCont);
                context.setBeanFactoryMap (bfCont->getBeanFactoryMap ());
                metaCont->accept (iteration0.get ());
                metaCont->accept (iteration1.get ());
                metaCont->accept (iteration2.get ());

/*------2.5-iteration-*global*-singletons-----------------------------------*/

                // Tworzymy singletony (ale tylko te globalne). Czyli nie iterujemy przez wszystko, a
                Ptr <BeanFactoryMap> beanFactoryMap = context.getBeanFactoryMap ();
                for (BeanFactoryMap::nth_index <1>::type::iterator i = beanFactoryMap->get<1> ().begin ();
                     i  != beanFactoryMap->get<1> (). end ();
                     ++i) {

                        Ptr <BeanFactory> factory = *i;

                        bool isSingleton = (static_cast <IMeta::Scope> (factory->getIntAttribute (Attributes::SCOPE_ARGUMENT)) == IMeta::SINGLETON);
                        bool isLazyInit = factory->getBoolAttribute (Attributes::LAZYINIT_ARGUMENT);

                        if (isSingleton && !isLazyInit) {
                                Core::Variant v = factory->create (Core::VariantMap (), &ctx);

                                if (v.isNone ()) {
                                        throw ContainerException (ctx, "ContainerFactory::fill : error creating singleton [" + (*i)->getId () + "].");
                                }
                        }
                }
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

Ptr <BeanFactoryContainer> ContainerFactory::createContainer (Ptr <MetaContainer> metaCont,
                bool storeMetaContainer,
                Ptr <BeanFactoryContainer> linkedParent)
{
        ContainerFactory cf;
        Ptr <BeanFactoryContainer> container = cf.createEmptyContainer (metaCont, storeMetaContainer, linkedParent, cf);
        cf.fill (container, metaCont);
        return container;
}

Ptr <BeanFactoryContainer> ContainerFactory::createEmptyContainer (Ptr <MetaContainer> metaCont,
                bool storeMetaContainer,
                Ptr <BeanFactoryContainer> linkedParent, ContainerFactory &cf)
{
        Ptr <BeanFactoryContainer> container = cf.create ();
        container->conversionMethodEditor = cf.conversionMethodEditor.get ();

        if (linkedParent) {
                container->setLinked (linkedParent);
                metaCont->setLinked (linkedParent->getMetaContainer ());
        }

        if (storeMetaContainer) {
                container->setMetaContainer (metaCont);
        }

        return container;
}

}
