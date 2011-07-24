/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <Pointer.h>
#include <TestHelpers.h>
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
#include "inputFormat/xml/XmlMetaService.h"
#include "inputFormat/xml/XmlMetaServiceFactory.h"
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
#include "../common/Context.h"
#include "beanFactory/BeanFactoryContext.h"

//#define CONTAINER_PRINT_META 1

namespace Container {
using namespace Wrapper;

ContainerFactory::ContainerFactory ()
{
        try {

/*------1st-iteration-------------------------------------------------------*/

                iteration1 = MetaVisitor::create ();
                iteration1->setContext (&context);

                Ptr <IMetaService> service = ParentService::create ();
                service->setContext (&context);
                iteration1->addService (service);

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

        Ptr <Editor::IEditor> noop = Editor::NoopEditor::create ();
        Ptr <Editor::IEditor> noopNoCopy = Editor::NoopEditor::create (false);

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

        Ptr <IBeanWrapperPlugin> plugin = boost::make_shared <PropertyRWBeanWrapperPlugin> ();
        pluginList->push_back (plugin);

        plugin = boost::make_shared <GetPutMethodRWBeanWrapperPlugin> ();
        pluginList->push_back (plugin);

        plugin = boost::make_shared <MethodPlugin> (MethodPlugin::IMMEDIATE_CALL);
        pluginList->push_back (plugin);

        beanWrapper->setPluginList (pluginList);

/*--------------------------------------------------------------------------*/

        Ptr <Editor::TypeEditor> editor = boost::make_shared <Editor::TypeEditor> ();
        Ptr <Editor::IEditor> noop = Editor::NoopEditor::create ();
        editor->setEqType (noop);
        editor->setNullType (noop);

        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (int), boost::make_shared <Editor::LexicalEditor <std::string, int> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (double), boost::make_shared <Editor::LexicalEditor <std::string, double> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (char), boost::make_shared <Editor::LexicalEditor <std::string, char> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (bool), boost::make_shared <Editor::LexicalEditor <std::string, bool> > ()));

//        Te konwersje działają, ale są niezbyt praktyczne.
//        editor->addType (Editor::TypeEditor::Type (typeid (double), typeid (std::string), boost::make_shared <Editor::LexicalEditor <double, std::string> > ()));

        // Core::String <-> std::string
        editor->addType (Editor::TypeEditor::Type (typeid (Core::String), typeid (std::string), boost::make_shared <Editor::LexicalEditor <Core::String, std::string> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (Core::String), boost::make_shared <Editor::LexicalEditor <std::string, Core::String> > ()));

        // StringCon.
        Ptr <Editor::StringConstructorEditor> strCon = boost::make_shared <Editor::StringConstructorEditor> ();

        Ptr <Editor::ChainEditor> chain = boost::make_shared <Editor::ChainEditor> ();
        chain->addEditor (editor);
        chain->addEditor (strCon);
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
        Ptr <BeanFactoryMap> map (new BeanFactoryMap);
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

                metaCont->accept (iteration1.get ());
                metaCont->accept (iteration2.get ());

/*------2.5-iteration-*global*-singletons-----------------------------------*/

                // Tworzymy singletony (ale tylko te globalne). Czyli nie iterujemy przez wszystko, a
                Ptr <BeanFactoryMap> beanFactoryMap = context.getBeanFactoryMap ();
                for (BeanFactoryMap::iterator i = beanFactoryMap->begin (); i != beanFactoryMap->end (); ++i) {
                        Ptr <BeanFactory> factory = i->second;
                        bool isSingleton = (static_cast <IMeta::Scope> (factory->getAttributes ().getInt (SCOPE_ARGUMENT)) == IMeta::SINGLETON);
                        bool isLazyInit = factory->getAttributes ().getBool (LAZYINIT_ARGUMENT);

                        if (isSingleton && !isLazyInit) {
                                (void)factory->create (Core::VariantMap (), &ctx);

                                if (ctx.isError ()) {
                                        throw ContainerException ("ContainerFactory::fill : error creating singleton [" + i->first + "]. Message : \n" + ctx.getMessage ());
                                }
                        }
                }
        }
        catch (NoSuchBeanException &e) {
                e.addMessage ("Error @ ContainerFactory::createContainer : [" + bfCont->toString () + "]. Message : " + ctx.getMessage ());
                throw;
        }
        catch (Core::Exception &e) {
                e.addMessage ("Error @ ContainerFactory::createContainer : [" + bfCont->toString () + "]. Message : " + ctx.getMessage ());
                throw;
        }
}

/****************************************************************************/

Ptr <BeanFactoryContainer> ContainerFactory::createContainer (Ptr <MetaContainer> metaCont)
{
        ContainerFactory cf;
        Ptr <BeanFactoryContainer> container = cf.create ();
        cf.fill (container, metaCont);
        return container;
}

/*##########################################################################*/

XmlContainerFactory::XmlContainerFactory () : ContainerFactory ()
{
        metaService = XmlMetaServiceFactory::createXmlMetaServiceFactory ();
}

/****************************************************************************/

Ptr <MetaContainer> XmlContainerFactory::parseXml (const std::string &xmlFilePath)
{
        Ptr <MetaContainer> metaCont = MetaContainer::create ();
        assert (metaService);
        metaService->reset ();
        metaService->setMetaContainer (metaCont);
        metaService->populate (xmlFilePath);
        return metaCont;
}

/****************************************************************************/

void XmlContainerFactory::fill (Ptr <BeanFactoryContainer> bfCont, const std::string &xmlFilePath)
{
        Ptr <MetaContainer> metaCont = parseXml (xmlFilePath);
        ContainerFactory::fill (bfCont, metaCont);
}

/****************************************************************************/

Ptr <BeanFactoryContainer> XmlContainerFactory::createContainer (const std::string &xmlFilePath,
                                                                 bool storeMetaContainer,
                                                                 Ptr <BeanFactoryContainer> linkedParent)
{
        XmlContainerFactory cf;
        Ptr <BeanFactoryContainer> container = cf.create ();

        if (linkedParent) {
                container->setLinked (linkedParent);
        }

        Ptr <MetaContainer> metaCont = cf.parseXml (xmlFilePath);

        if (linkedParent) {
                metaCont->setLinked (linkedParent->getMetaContainer ());
        }

        if (storeMetaContainer) {
                container->setMetaContainer (metaCont);
        }

        cf.ContainerFactory::fill (container, metaCont);
        return container;
}

}
