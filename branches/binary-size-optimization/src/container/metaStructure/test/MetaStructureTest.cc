/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>

#include "metaStructure/model/MetaStructure.h"
//#include "metaStructure/service/MetaVisitor.h"
#include "common/testHelpers/ContainerTestFactory.h"
#include "metaStructure/service/PrintService.h"
#include "metaStructure/service/ParentService.h"
#include "../../../core/variant/Cast.h"
#include <boost/make_shared.hpp>

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (MetaStructureTest);

/**
 * To chyba po prostu miało się nie wywalić.
 */
BOOST_AUTO_TEST_CASE (testCreateData)
{
        Ptr <ValueData> data = boost::make_shared <ValueData> ("data", "String");
        BOOST_CHECK (data->getData () == "data");
        BOOST_CHECK (data->getType () == "String");

/*--------------------------------------------------------------------------*/

        Ptr <NullData> data1 = boost::make_shared <NullData> ();
        BOOST_CHECK (data1);

/*--------------------------------------------------------------------------*/

        Ptr <RefData> data2 = boost::make_shared <RefData> ("someBean");
        BOOST_CHECK (data2->getData () == "someBean");

/*--------------------------------------------------------------------------*/

//        Ptr <IdRefData> data3 = boost::make_shared <IdRefData> ("someBean", AbstractRef::LOCAL);
//        BOOST_CHECK (data3->getData () == "someBean");
//        BOOST_CHECK (data3->getTarget () == AbstractRef::LOCAL);
}

/**
 * Testuje najprostszy serwis wypisujący strukturę na ekran.
 * TODO MetaVisito nie jest API - przetestowac inaczej
 */
//BOOST_AUTO_TEST_CASE (testMetaVisitorPrint)
//{
//        Ptr <MetaVisitor> visitor = MetaVisitor::create ();
//        Ptr <PrintMetaService> service = PrintMetaService::create ();
//        String buff;
//        service->setBuffer (&buff);
//        visitor->addService (service);
//
//        VisitorContext context;
//        visitor->setContext (&context);
//        service->setContext (&context);
//
//        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure24 ();
//        metaCont->accept (visitor.get ());
//
//        metaCont = ContainerTestFactory::createMetaStructure01 ();
//        metaCont->accept (visitor.get ());
//
//        BOOST_CHECK (!buff.empty ());
//}

///**
// * Testuje serwis uzupełniający strukturę pod kątem parent/child.
// */
//BOOST_AUTO_TEST_CASE (testMetaVisitorParent)
//{
//        VisitorContext context;
//        Ptr <MetaVisitor> visitor = MetaVisitor::create ();
//        visitor->setContext (&context);
//
//        Ptr <IMetaService> service = ParentService::create ();
//        service->setContext (&context);
//        visitor->addService (service);
//
////        service = PrintMetaService::create ();
////        service->setContext (&context);
////        visitor->addService (service);
//
//        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure01 ();
//
///*--------------------------------------------------------------------------*/
//
//        BOOST_CHECK (metaCont);
//        metaCont->accept (visitor.get ());
//
//        Ptr <IMeta> syn = metaCont->get ("syn");
//        MappedMeta *mSyn = dynamic_cast <MappedMeta *> (syn.get ());
//        BOOST_CHECK (mSyn);
//
//        // Sprawdz fieldy.
//        BOOST_CHECK (mSyn->getField ("field3"));
//        BOOST_CHECK (mSyn->getField ("field3")->getData ());
//        BOOST_CHECK (mSyn->getField ("field3")->getData ()->getData () == "value3");
//
//        BOOST_CHECK (mSyn->getField ("field4"));
//        BOOST_CHECK (mSyn->getField ("field4")->getData ());
//        BOOST_CHECK (mSyn->getField ("field4")->getData ()->getData () == "value4");
//
//        BOOST_CHECK (mSyn->getField ("field1"));
//        BOOST_CHECK (mSyn->getField ("field1")->getData ());
//        BOOST_CHECK (mSyn->getField ("field1")->getData ()->getData () == "value1");
//
//        BOOST_CHECK (mSyn->getField ("field2"));
//        BOOST_CHECK (mSyn->getField ("field2")->getData ());
//        BOOST_CHECK (mSyn->getField ("field2")->getData ()->getData () == "value2");
//
//        // Sprawdz atrybuty :
//        BOOST_CHECK (mSyn->containsAttribute (ABSTRACT_ARGUMENT));
//        BOOST_CHECK (mSyn->getAbstract () == true);
//
//        BOOST_CHECK (mSyn->containsAttribute (LAZYINIT_ARGUMENT));
//        BOOST_CHECK (mSyn->getLazyInit () == true);
//
//        // Spradz makroInfo :
////        BOOST_CHECK (ccast <Core::String> (mSyn->getMetaInfo ("test1")));
////        BOOST_CHECK (vcast <Core::String> (mSyn->getMetaInfo ("test1")) == "valTest1");
////        BOOST_CHECK (ccast <Core::String> (mSyn->getMetaInfo ("test2")));
////        BOOST_CHECK (vcast <Core::String> (mSyn->getMetaInfo ("test2")) == "valTest2");
////        BOOST_CHECK (ccast <Core::String> (mSyn->getMetaInfo ("test1")));
////        BOOST_CHECK (vcast <Core::String> (mSyn->getMetaInfo ("test3")) == "valTest3");
//
//        // Sprawdz c-Arg.
//        BOOST_CHECK (mSyn->getConstructorArgs ().size () == 2);
//}

BOOST_AUTO_TEST_SUITE_END ();
