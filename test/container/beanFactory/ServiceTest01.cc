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
//
//#include <iostream>
//#include "core/Pointer.h"
//#include "testHelpers/TestHelpers.h"
//#include <BeanWrapper.h>
//
//#include "container/metaStructure/model/MetaStructure.h"
//#include "container/testHelpers/ContainerTestFactory.h"
//#include "container/beanFactory/service/BeanFactoryService.h"
//#include "container/metaStructure/service/PrintService.h"
//#include "container/metaStructure/service/MetaVisitor.h"
//#include "container/metaStructure/service/ParentService.h"
//#include "container/beanFactory/factory/ServiceFactory.h"
//#include "container/beanFactory/service/ValueServiceHelper.h"
//#include "common/OrderedVariantMap.h"
//#include "container/beanFactory/service/BeanFactoryInitService.h"
//#include "container/beanFactory/service/MappedValueService.h"
//#include "container/beanFactory/service/IndexedValueService.h"
//
///****************************************************************************/
//
//using namespace Container;
//using namespace Core;
//
///****************************************************************************/
//
//BOOST_AUTO_TEST_SUITE (ServiceTest01);
//
///**
// *
// */
//BOOST_AUTO_TEST_CASE (testBeanFactoryService)
//{
//        BeanFactoryVisitorContext context;
//        Ptr <MetaVisitor> visitor = MetaVisitor::create ();
//        visitor->setContext (&context);
//
//        Ptr <IMetaService> service = ParentService::create ();
//        service->setContext (&context);
//        visitor->addService (service);
//
//        Ptr <BeanFactoryInitService> bfService = BeanFactoryInitService::create ();
//        bfService->setContext (&context);
//        bfService->setDefaultBeanWrapper (Wrapper::BeanWrapper::create ());
//        visitor->addService (bfService);
//        Ptr <BeanFactoryMap> map (new BeanFactoryMap);
//        context.setBeanFactoryMap (map);
//
////                service = PrintMetaService::create ();
////                service->setContext (&context);
////                visitor->addService (service);
//
//
//        /*--------------------------------------------------------------------------*/
//
//        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure01 ();
//        metaCont->accept (visitor.get ());
//        //std::cerr << ToStringHelper::toString (*map) << std::endl;
//
//        map->clear ();
//        metaCont = ContainerTestFactory::createMetaStructure24 ();
//        metaCont->accept (visitor.get ());
//        //std::cerr << ToStringHelper::toString (*map) << std::endl;
//}
//
///**
// *
// */
//BOOST_AUTO_TEST_CASE (testValueServiceMapped)
//{
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
//        bfService->setDefaultBeanWrapper (Wrapper::BeanWrapper::create ());
//        visitor->addService (bfService);
//
//        Ptr <MappedValueService> valMapService = MappedValueService::create ();
//        valMapService->setContext (&context);
//        Ptr <ValueServiceHelper> helper = ValueServiceHelper::create ();
//        helper->setSingletonMap (ServiceFactory::createSingletons ());
//        valMapService->setValueServiceHelper (helper);
//        visitor->addService (valMapService);
//
///*--------------------------------------------------------------------------*/
//
//        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure03 ();
//        metaCont->accept (visitor.get ());
//        //std::cerr << ToStringHelper::toString (*map) << std::endl;
//
///*--------------------------------------------------------------------------*/
//
//        BOOST_CHECK (map->size () == 1);
//        BOOST_CHECK (map->find ("syn") != map->end ());
//
//        Ptr <BeanFactory> bf = map->operator[] ("syn");
//        BOOST_CHECK (bf);
//
//        Variant input = bf->getInput();
//        BOOST_CHECK (ccast <Ptr <OrderedVariantMap> > (input));
//        Ptr <OrderedVariantMap> inMap = vcast <Ptr <OrderedVariantMap> > (input);
//
//        BOOST_CHECK (inMap);
//        BOOST_CHECK (inMap->size () == 7);
//
//        BOOST_CHECK (inMap->containsKey ("field0"));
//        BOOST_CHECK (vcast <Core::String> (inMap->get ("field0")) == "value0");
//
//        BOOST_CHECK (inMap->containsKey ("field1"));
//        BOOST_CHECK (vcast <Core::String> (inMap->get ("field1")) == "value1");
//
//        BOOST_CHECK (inMap->containsKey ("field2"));
//        BOOST_CHECK (vcast <int> (inMap->get ("field2")) == 6667);
//
//        BOOST_CHECK (inMap->containsKey ("field3"));
//        BOOST_CHECK (vcast <double> (inMap->get ("field3")) == 123.45);
//
//        BOOST_CHECK (inMap->containsKey ("field4"));
//        BOOST_CHECK (vcast <char> (inMap->get ("field4")) == 'f');
//
//        BOOST_CHECK (inMap->containsKey ("field5"));
//        BOOST_CHECK (vcast <bool> (inMap->get ("field5")) == true);
//
//        BOOST_CHECK (inMap->containsKey ("field6"));
//        BOOST_CHECK (vcast <char> (inMap->get ("field6")) == 0);
//}
//
///**
// *
// */
//BOOST_AUTO_TEST_CASE (testValueServiceIndexed)
//{
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
//        bfService->setDefaultBeanWrapper (Wrapper::BeanWrapper::create ());
//        visitor->addService (bfService);
//
//        Ptr <IndexedValueService> valIndexService = IndexedValueService::create ();
//        valIndexService->setContext (&context);
//        Ptr <ValueServiceHelper> helper = ValueServiceHelper::create ();
//        helper->setSingletonMap (ServiceFactory::createSingletons ());
//        valIndexService->setValueServiceHelper (helper);
//        visitor->addService (valIndexService);
//
///*--------------------------------------------------------------------------*/
//
//        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure04 ();
//        metaCont->accept (visitor.get ());
//        //std::cerr << ToStringHelper::toString (*map) << std::endl;
//
///*--------------------------------------------------------------------------*/
//
//        BOOST_CHECK (map->size () == 1);
//        BOOST_CHECK (map->find ("syn") != map->end ());
//
//        Ptr <BeanFactory> bf = map->operator[] ("syn");
//        BOOST_CHECK (bf);
//
//        Variant input = bf->getInput();
//        BOOST_CHECK (ccast <Ptr <VariantVector> > (input));
//        Ptr <VariantVector> inList = vcast <Ptr <VariantVector> > (input);
//
//        BOOST_CHECK (inList);
//        BOOST_CHECK (inList->size () == 7);
//
//        BOOST_CHECK (vcast <Core::String> (inList->operator[] (0)) == "value0");
//        BOOST_CHECK (vcast <Core::String> (inList->operator[] (1)) == "value1");
//        BOOST_CHECK (vcast <int> (inList->operator[] (2)) == 6667);
//        BOOST_CHECK (vcast <double> (inList->operator[] (3)) == 123.45);
//        BOOST_CHECK (vcast <char> (inList->operator[] (4)) == 'f');
//        BOOST_CHECK (vcast <bool> (inList->operator[] (5)) == true);
//        BOOST_CHECK (vcast <char *> (inList->operator[] (6)) == NULL);
//
///*--------------------------------------------------------------------------*/
//
//        map->clear ();
//        metaCont = ContainerTestFactory::createMetaStructure15 ();
//        metaCont->accept (visitor.get ());
//
//        BOOST_CHECK (map->size () == 1);
//        BOOST_CHECK (map->find ("mojBean") != map->end ());
//
//        bf = map->operator[] ("mojBean");
//        BOOST_CHECK (bf);
//
//        input = bf->getCArgs();
//        BOOST_CHECK (ccast <Ptr <VariantVector> > (input));
//        inList = vcast <Ptr <VariantVector> > (input);
//
//        BOOST_CHECK (inList);
//        BOOST_CHECK (inList->size () == 7);
//
//        BOOST_CHECK (vcast <Core::String> (inList->operator[] (0)) == "value2");
//        BOOST_CHECK (vcast <Core::String> (inList->operator[] (1)) == "value3");
//        BOOST_CHECK (vcast <int> (inList->operator[] (2)) == 6667);
//        BOOST_CHECK (vcast <double> (inList->operator[] (3)) == 123.45);
//        BOOST_CHECK (vcast <char> (inList->operator[] (4)) == 'f');
//        BOOST_CHECK (vcast <bool> (inList->operator[] (5)) == true);
//        BOOST_CHECK (vcast <char *> (inList->operator[] (6)) == NULL);
//}
//
//BOOST_AUTO_TEST_SUITE_END ();

