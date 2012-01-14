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
//BOOST_AUTO_TEST_SUITE (RemoveTest);
//
//int iValue = 0;
//
//struct Handler1 {
//
//        c__(void);
//
//        Handler1 () : onClickedListener (this, "clicked2", "$onClicked1()") {}
//
//        m_ (onClicked1) void onClicked1 () { iValue++; }
//
//        Listener onClickedListener;
//
//        e_ (Handler1);
//};
//
///**
// * Sprawdza,y, czy sie pousuwają listenery i scopey same, kiedy
// * zostanie usunięty obiekt nasłuchujący.
// */
//BOOST_AUTO_TEST_CASE (testRemove)
//{
//        BOOST_CHECK (!iValue);
//
//        {
//                // Nie ma scopa
//                BOOST_CHECK (!findScope ("/test"));
//                BOOST_CHECK (Signal::Manager::instance().countScopes () == 0);
//
//                Handler1 h1;
//                bind ("/test", &h1);
//
//                BOOST_CHECK (Signal::Manager::instance().countScopes () == 1);
//
//                Ptr <Scope> scp = findScope ("/test");
//
//                BOOST_CHECK (scp);
//                BOOST_CHECK (!scp->isEmpty ());
//                BOOST_CHECK (scp->countListeners () == 1);
//
//                {
//                        Handler1 h2;
//                        bind ("/test", &h2);
//                        BOOST_CHECK (Signal::Manager::instance().countScopes () == 1);
//                        BOOST_CHECK (scp->countListeners () == 2);
//
//                        BOOST_CHECK (iValue == 0);
//                        Signal::emit ("/test/clicked2");
//                        BOOST_CHECK (iValue == 2);
//                }
//
//                BOOST_CHECK (Signal::Manager::instance().countScopes () == 1);
//                BOOST_CHECK (scp->countListeners () == 1);
//                BOOST_CHECK (iValue == 2);
//
//                Signal::emit (scp, "clicked2");
//                BOOST_CHECK (iValue == 3);
//
//                Signal::emit ("/test/clicked2");
//                BOOST_CHECK (iValue == 4);
//        }
//
//        // Nie ma już żadnego scope.
//        BOOST_CHECK (Signal::Manager::instance().countScopes () == 0);
//}
//
///**
// * Jak wyżej, testujemy usuwanie się automatyczne, ale teraz
// * alokujemy obiekty za pomocą new i delete.
// */
//BOOST_AUTO_TEST_CASE (testRemoveNewAndDelete)
//{
//        BOOST_CHECK (iValue == 4);
//
//        // Nie ma scopa
//        BOOST_CHECK (!findScope ("/test"));
//        BOOST_CHECK (Signal::Manager::instance().countScopes () == 0);
//
//        Handler1 *h1 = new Handler1;
//        bind ("/test", h1);
//
//        BOOST_CHECK (Signal::Manager::instance().countScopes () == 1);
//
//        Ptr <Scope> scp = findScope ("/test");
//
//        BOOST_CHECK (scp);
//        BOOST_CHECK (!scp->isEmpty ());
//        BOOST_CHECK (scp->countListeners () == 1);
//
//        Handler1 *h2 = new Handler1;
//        bind ("/test", h2);
//        BOOST_CHECK (Signal::Manager::instance().countScopes () == 1);
//        BOOST_CHECK (scp->countListeners () == 2);
//
//        BOOST_CHECK (iValue == 4);
//        Signal::emit ("/test/clicked2");
//        BOOST_CHECK (iValue == 6);
//        delete h2;
//
//        BOOST_CHECK (Signal::Manager::instance().countScopes () == 1);
//        BOOST_CHECK (scp->countListeners () == 1);
//        BOOST_CHECK (iValue == 6);
//
//        Signal::emit (scp, "clicked2");
//        BOOST_CHECK (iValue == 7);
//
//        Signal::emit ("/test/clicked2");
//        BOOST_CHECK (iValue == 8);
//        delete h1;
//
//        // Nie ma już żadnego scope.
//        BOOST_CHECK (Signal::Manager::instance().countScopes () == 0);
//}
//
///**
// * Testuje poprawkę błedu. Otóż zapomniałem, że jeden listener może
// * być dodany do więcej niż jednego scope (jeśli ma relatywny sygnał).
// * Jednak początkowo klasa Listener miała tylko jeden wskaźnik do Scope.
// * Dlatego podczas kasowania Listenera usuwał się on z tylko jednego
// * Scope (ostatniego do którego go dodano).
// */
//BOOST_AUTO_TEST_CASE (testRemoveMultiScope)
//{
//        int scopesNum = Signal::Manager::instance().countScopes();
//
//        {
//                Handler1 h1;
//                bind ("/test66", &h1);
//
//                BOOST_CHECK (Signal::Manager::instance().countScopes () == scopesNum + 1);
//
//                bind ("/test67", &h1);
//                BOOST_CHECK (Signal::Manager::instance().countScopes () == scopesNum + 2);
//        }
//
//        BOOST_CHECK (Signal::Manager::instance().countScopes () == scopesNum);
//
//        Ptr <Scope> s = findScope ("/test67");
//        BOOST_CHECK (!s);
//
//        s = findScope ("/test66");
//        BOOST_CHECK (!s);
//}
//
//BOOST_AUTO_TEST_SUITE_END ();
