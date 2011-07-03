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
//#include <K202.h>
//#include <Reflection.h>
//#include <Signal.h>
//
//using namespace Core;
//using namespace Signal;
//
//BOOST_AUTO_TEST_SUITE (MergeParamsTest);
//
//namespace Testowa2 {
//
//struct Receiver {
//
//        __c(void);
//
//        Receiver () : onSig3 (this, "/a/sig0", "$handler2 (%0, $test)"),
//                        onSig4 (this, "/a/sig1", "$handler2 (%0, %1)"),
//                        onSig5 (this, "/a/sig2", "$handler2 ($test, $aa)"),
//                        onSig6 (this, "/sig6", "$handler2 (1, 2)"),
//                        iValue (0)
//        {
//                vector.add (Core::Variant (45));
//                map.set ("test", Core::Variant (5));
//
//                onSig3.setParamVector (vector);
//                onSig3.setArgsMap (map);
//                onSig4.setParamVector (vector);
//                onSig4.setArgsMap (map);
//                onSig5.setParamVector (vector);
//                onSig5.setArgsMap (map);
//        }
//
//        _m (handler2) void handler2 (int i1, int i2)
//        {
//                iValue = i1 + i2;
//        }
//
//        VariantVector vector;
//        VariantMap map;
//        Listener onSig3, onSig4, onSig5, onSig6;
//        int iValue;
//
//        _e (Testowa2::Receiver);
//};
//
//}
//
///**
// * Testuje ścieżki. W kodzie jest opisane co i jak.
// */
//BOOST_AUTO_TEST_CASE (testBasic)
//{
//        try {
//                Testowa2::Receiver rec;
//
//                emit ("/a/sig0");
//                BOOST_CHECK (rec.iValue == 50);
//
//                rec.iValue = 0;
//
//                VariantVector vector;
//                VariantMap map;
//
//                int i = 1;
//                vector.add (Core::Variant (&i));
//
////                vector.add (Core::Variant (1));
//                map.set ("aa", Core::Variant (2));
//
//                emit ("/a/sig1", vector);
//
//                BOOST_CHECK (rec.iValue == 46);
//
////                rec.iValue = 0;
////
////                emit ("/a/sig2", vector, map);
////
////                BOOST_CHECK (rec.iValue == 7);
//        }
//        catch (const Core::Exception &e) {
//                std::cerr << e.getMessage() << std::endl;
//        }
//
//}
//
//namespace TT {
//
//struct Test {
//
//        Test () : list (this, "/toggled", "1") {}
//        Listener list;
//};
//
//}
//
///**
// * Segfoltowało w konkretnym wypadku.
// */
//BOOST_AUTO_TEST_CASE (testScopeReuse)
//{
//        try {
//                {
//                        Testowa2::Receiver rec;
//                        TT::Test tt;
//                        //bind ("/win", &tt);
//                }
//
//                {
//                        TT::Test t2;
//                        //bind ("/win", &t2);
//                }
//
//        }
//        catch (const Core::Exception &e) {
//                std::cerr << e.getMessage() << std::endl;
//        }
//
//}
//
//BOOST_AUTO_TEST_SUITE_END ();
