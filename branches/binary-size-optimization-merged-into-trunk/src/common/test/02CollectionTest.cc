///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#define BOOST_TEST_MODULE CommonTest
//#define BOOST_TEST_DYN_LINK
//
//#include <boost/test/unit_test.hpp>
//#include <iostream>
//
//#include "collection/ListHelper.h"
//
//BOOST_AUTO_TEST_SUITE (CollectionTest);
//
//using namespace Common;
//
//BOOST_AUTO_TEST_CASE (testListHelper)
//{
//        Core::StringList l;
//
//        l = ListHelper::createStringList ("");
//        BOOST_CHECK (!l.size ());
//
//        l = ListHelper::createStringList ("test");
//        BOOST_CHECK (l.size () == 1);
//        BOOST_CHECK (l.getAt (0) == "test");
//
//        l = ListHelper::createStringList ("test1", "test2", "test3", "test4", "test5");
//        BOOST_CHECK (l.size () == 5);
//        BOOST_CHECK (l.getAt (0) == "test1");
//        BOOST_CHECK (l.getAt (1) == "test2");
//        BOOST_CHECK (l.getAt (2) == "test3");
//        BOOST_CHECK (l.getAt (3) == "test4");
//        BOOST_CHECK (l.getAt (4) == "test5");
//}
//
//BOOST_AUTO_TEST_SUITE_END ();
