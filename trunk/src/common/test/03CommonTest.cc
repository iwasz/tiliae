///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#include <boost/test/unit_test.hpp>
//#include <iostream>
//
//#include "handler/IHandler.h"
//#include "handler/ZeroHandler.h"
//#include "handler/SingleHandler.h"
//#include "handler/DebugHandler.h"
//
//BOOST_AUTO_TEST_SUITE (CommonTest);
//
//using namespace Common;
//using namespace Core;
//
///**
// * Sprawdza czy dziala wywolanie handlera.
// */
//BOOST_AUTO_TEST_CASE (testHandler)
//{
//        DebugHandler cdh;
//        cdh.setDebug ("cdh1");
//        VariantList params;
//        params.add (Core::Variant (String ("param1")));
//        params.add (Core::Variant (String ("param2")));
//        params.add (Core::Variant (String ("param3")));
//        Variant ret = cdh.run (params);
//
//        String strRet = vcast <String> (ret);
//        BOOST_CHECK (strRet == "cdh1 param1 param2 param3");
//}
//
///**
// * Sprawdza czy dziala wywolanie handlera.
// */
//BOOST_AUTO_TEST_CASE (testSingleHandler)
//{
//        DebugHandler cdh;
//        cdh.setDebug ("cdh1");
//
//        SingleHandler sh;
//        sh.setHandler (&cdh);
//
//        Variant param = Core::Variant (String ("single-param1"));
//
//        Variant ret = sh.run (param);
//        String strRet = vcast <String> (ret);
//        BOOST_CHECK (strRet == "cdh1 single-param1");
//}
//
///**
// * Sprawdza czy dziala wywolanie handlera.
// */
//BOOST_AUTO_TEST_CASE (testZeroHandler)
//{
//        DebugHandler *cdh = new DebugHandler;
//        cdh->setDebug ("cdh1");
//
//        ZeroHandler zh;
//        zh.setHandler (cdh);
//
//        Variant ret = zh.run ();
//        String strRet = vcast <String> (ret);
//        BOOST_CHECK (strRet == "cdh1");
//}
//
//BOOST_AUTO_TEST_SUITE_END ();
