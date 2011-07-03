// TODO - co z tym zrobić? Serwisy nie są częśćią API, więc nie można z nich korzystać na zewnątrz lib.

///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#include <boost/test/unit_test.hpp>
//#include <boost/make_shared.hpp>
//#include <iostream>
//#include <Pointer.h>
//#include <TestHelpers.h>
//#include <BeanWrapper.h>
//#include <NoopEditor.h>
//#include <SimpleMapEditor.h>
//#include <IndexedEditor.h>
//
//#include "metaStructure/model/MetaStructure.h"
//#include "common/testHelpers/ContainerTestFactory.h"
//#include "beanFactory/service/BeanFactoryService.h"
//#include "metaStructure/service/PrintService.h"
//#include "metaStructure/service/MetaVisitor.h"
//#include "metaStructure/service/ParentService.h"
//#include "beanFactory/factory/ServiceFactory.h"
//#include "beanFactory/service/ValueServiceHelper.h"
//#include "common/OrderedVariantMap.h"
//#include "beanFactory/service/EditorService.h"
//#include "Defs.h"
//#include "beanFactory/service/BeanFactoryInitService.h"
//#include "beanFactory/service/MappedValueService.h"
//#include "beanFactory/service/IndexedValueService.h"
//#include "beanFactory/service/BeanStackUpdateService.h"
//#include "beanFactory/service/ListEditorService.h"
//
///****************************************************************************/
//
//using namespace Container;
//using namespace Core;
//
///****************************************************************************/
//
//BOOST_AUTO_TEST_SUITE (ServiceTest02);
//
///**
// *
// */
//BOOST_AUTO_TEST_CASE (testEditorServiceMapped)
//{
///*------1st-iteration-------------------------------------------------------*/
//
//        BeanFactoryVisitorContext context;
//        Ptr <BeanFactoryMap> map (new BeanFactoryMap);
//        context.setBeanFactoryMap (map);
//
//        Ptr <MetaVisitor> visitor = MetaVisitor::create ();
//        visitor->setContext (&context);
//
//        Ptr <IMetaService> service = ParentService::create ();
//        service->setContext (&context);
//        visitor->addService (service);
//
//        Ptr <BeanFactoryInitService> bfService = BeanFactoryInitService::create ();
//        bfService->setContext (&context);
//        Ptr <Wrapper::BeanWrapper> beanWrapper = Wrapper::BeanWrapper::create ();
//        bfService->setDefaultBeanWrapper (beanWrapper);
//        visitor->addService (bfService);
//
//        Ptr <Core::VariantMap> singletons = ServiceFactory::createSingletons ();
//
//        Ptr <MappedValueService> valMapService = MappedValueService::create ();
//        valMapService->setContext (&context);
//        Ptr <ValueServiceHelper> helper = ValueServiceHelper::create ();
//        helper->setSingletonMap (singletons);
//        valMapService->setValueServiceHelper (helper);
//        visitor->addService (valMapService);
//
//        Ptr <IndexedValueService> valIndexService = IndexedValueService::create ();
//        valIndexService->setContext (&context);
//        helper->setSingletonMap (singletons);
//        valIndexService->setValueServiceHelper (helper);
//        visitor->addService (valIndexService);
//
//        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure25 ();
//        metaCont->accept (visitor.get ());
//
///*------2nd-iteration-------------------------------------------------------*/
//
//        visitor->reset ();
//
//        Ptr <BeanFactoryContainer> container = boost::make_shared <BeanFactoryContainer> ();
//        container->setSingletons (singletons);
//        container->addSingleton (DEFAULT_BEAN_WRAPPER, Core::Variant (beanWrapper));
//        container->setBeanFactoryMap (map);
//        context.setBeanFactoryContainer (container);
//
//        Ptr <BeanStackUpdateService> updService = BeanStackUpdateService::create ();
//        updService->setContext (&context);
//        visitor->addService (updService);
//
//        Ptr <EditorService> editorService = EditorService::create ();
//        editorService->setContext (&context);
//        editorService->init (singletons.get ());
//        visitor->addService (editorService);
//
//        metaCont->accept (visitor.get ());
//
///*--------------------------------------------------------------------------*/
//
//                //std::cerr << ToStringHelper::toString (*map) << std::endl;
//
///*--------------------------------------------------------------------------*/
//
//        BOOST_CHECK (map->size () == 3);
//        BOOST_CHECK (map->find ("syn") != map->end ());
//
//        Ptr <BeanFactory> bf = map->operator[] ("syn");
//        BOOST_CHECK (bf);
//
//        Ptr <IEditor> editor = bf->getEditor ();
//        BOOST_CHECK (editor);
//
//        Ptr <Editor::SimpleMapEditor> mapped = dynamic_pointer_cast <Editor::SimpleMapEditor> (editor);
//        BOOST_CHECK (mapped);
//
//        Ptr<EditorMap> editorMap = mapped->getEditors ();
//        BOOST_CHECK (editorMap);
//        BOOST_CHECK (!editorMap->empty ());
//
//        // 2 Ponieważ tylko 2 są inne niż te domyślne string, int etc
//        BOOST_CHECK (editorMap->size () == 2);
//}
//
///**
// *
// */
//BOOST_AUTO_TEST_CASE (testEditorServiceIndexed)
//{
///*------1st-iteration-------------------------------------------------------*/
//
//                BeanFactoryVisitorContext context;
//                Ptr <BeanFactoryMap> map (new BeanFactoryMap);
//                context.setBeanFactoryMap (map);
//
//                Ptr <MetaVisitor> visitor = MetaVisitor::create ();
//                visitor->setContext (&context);
//
//                Ptr <IMetaService> service = ParentService::create ();
//                service->setContext (&context);
//                visitor->addService (service);
//
//                Ptr <BeanFactoryInitService> bfService = BeanFactoryInitService::create ();
//                bfService->setContext (&context);
//                Ptr <Wrapper::BeanWrapper> beanWrapper = Wrapper::BeanWrapper::create ();
//                bfService->setDefaultBeanWrapper (beanWrapper);
//                visitor->addService (bfService);
//
//                Ptr <Core::VariantMap> singletons = ServiceFactory::createSingletons ();
//
//                Ptr <MappedValueService> valMapService = MappedValueService::create ();
//                valMapService->setContext (&context);
//                Ptr <ValueServiceHelper> helper = ValueServiceHelper::create ();
//                helper->setSingletonMap (singletons);
//                valMapService->setValueServiceHelper (helper);
//                visitor->addService (valMapService);
//
//                Ptr <IndexedValueService> valIndexService = IndexedValueService::create ();
//                valIndexService->setContext (&context);
//                helper->setSingletonMap (singletons);
//                valIndexService->setValueServiceHelper (helper);
//                visitor->addService (valIndexService);
//
//                Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure26 ();
//                metaCont->accept (visitor.get ());
//
///*------2nd-iteration-------------------------------------------------------*/
//
//                visitor->reset ();
//
//                Ptr <BeanFactoryContainer> container = boost::make_shared <BeanFactoryContainer> ();
//                container->setSingletons (singletons);
//                container->addSingleton (DEFAULT_BEAN_WRAPPER, Core::Variant (beanWrapper));
//                container->setBeanFactoryMap (map);
//                context.setBeanFactoryContainer (container);
//
//                Ptr <BeanStackUpdateService> updService = BeanStackUpdateService::create ();
//                updService->setContext (&context);
//                visitor->addService (updService);
//
//                Ptr <ListEditorService> listEditorService = ListEditorService::create ();
//                listEditorService->setContext (&context);
//                listEditorService->init (singletons.get ());
//                visitor->addService (listEditorService);
//
//                metaCont->accept (visitor.get ());
//
///*--------------------------------------------------------------------------*/
//
//                //std::cerr << ToStringHelper::toString (*map) << std::endl;
//
///*--------------------------------------------------------------------------*/
//
//                BOOST_CHECK (map->size () == 3);
//                BOOST_CHECK (map->find ("syn") != map->end ());
//
//                Ptr <BeanFactory> bf = map->operator []("syn");
//                BOOST_CHECK (bf);
//
//                Ptr <IEditor> editor = bf->getEditor ();
//                BOOST_CHECK (editor);
//
//                Ptr <Editor::IndexedEditor> indexed = dynamic_pointer_cast <Editor::IndexedEditor> (editor);
//                BOOST_CHECK (indexed);
//
//                Ptr<Editor::IndexedEditor::EditorMap> editorMap = indexed->getEditors ();
//                BOOST_CHECK (editorMap);
//                BOOST_CHECK (!editorMap->empty ());
//
//                // 2 Ponieważ tylko 2 są inne niż te domyślne string, int etc
//                BOOST_CHECK (editorMap->size () == 2);
//}
//
//BOOST_AUTO_TEST_SUITE_END ();

