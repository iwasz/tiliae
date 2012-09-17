// TODO zrobić coś z tym testem

///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#include <boost/test/unit_test.hpp>
//#include <boost/mpl/list.hpp>
//#include <boost/test/test_case_template.hpp>
//#include "common/OrderedVariantMap.h"
//#include "core/Typedefs.h"
//#include "core/variant/Cast.h"
//#include "core/variant/Variant.h"
//
///****************************************************************************/
//
//using namespace Core;
//using namespace Container;
//
///****************************************************************************/
//
//BOOST_AUTO_TEST_SUITE (OrderedVariantMapTest);
//
//typedef boost::mpl::list <OrderedVariantMap, Core::VariantMap> TestTypes;
//
///**
// * Ma się nie wywalić
// */
//BOOST_AUTO_TEST_CASE_TEMPLATE (testInstantiation, Map, TestTypes)
//{
//        Map map;
//}
//
///**
// * Czy to co się ustawia da się potem wyjąć.
// */
//BOOST_AUTO_TEST_CASE_TEMPLATE (testSetGet, Map, TestTypes)
//{
//        Map map;
//
//        map.insert (std::make_pair ("k6", 667));
//        map.insert (std::make_pair ("k5", 668));
//        map.insert (std::make_pair ("k4", 669));
//        map.insert (std::make_pair ("k3", 670));
//        map.insert (std::make_pair ("k2", 671));
//        map.insert (std::make_pair ("k1", 672));
//
//        Variant ret = map.get (Core::Variant (String ("k6")));
//        BOOST_CHECK (vcast <int> (ret) == 667);
//
//        ret = map.get (Core::Variant (String ("k5")));
//        BOOST_CHECK (vcast <int> (ret) == 668);
//
//        ret = map.get (Core::Variant (String ("k4")));
//        BOOST_CHECK (vcast <int> (ret) == 669);
//
//        ret = map.get (Core::Variant (String ("k3")));
//        BOOST_CHECK (vcast <int> (ret) == 670);
//
//        ret = map.get (Core::Variant (String ("k2")));
//        BOOST_CHECK (vcast <int> (ret) == 671);
//
//        ret = map.get (Core::Variant (String ("k1")));
//        BOOST_CHECK (vcast <int> (ret) == 672);
//}
//
///**
// * containsKey
// */
//BOOST_AUTO_TEST_CASE_TEMPLATE (testContainsKey, Map, TestTypes)
//{
//        Map map;
//
//        map["k6"] = Core::Variant (667);
//        map["k5"] = Core::Variant (668);
//        map["k4"] = Core::Variant (669);
//        map["k3"] = Core::Variant (670);
//        map["k2"] = Core::Variant (671);
//        map["k1"] = Core::Variant (672);
//
//        BOOST_CHECK (map.containsKey (Core::Variant (String ("k6"))));
//        BOOST_CHECK (map.containsKey (Core::Variant (String ("k5"))));
//        BOOST_CHECK (map.containsKey (Core::Variant (String ("k4"))));
//        BOOST_CHECK (map.containsKey (Core::Variant (String ("k3"))));
//        BOOST_CHECK (map.containsKey (Core::Variant (String ("k2"))));
//        BOOST_CHECK (map.containsKey (Core::Variant (String ("k1"))));
//
//        BOOST_CHECK (!map.containsKey (Core::Variant (String ("k0"))));
//        BOOST_CHECK (!map.containsKey (Core::Variant (String ())));
//}
//
///**
// * Clear, size, empty
// */
//BOOST_AUTO_TEST_CASE_TEMPLATE (testClearAndSizeAndEmpty, Map, TestTypes)
//{
//        Map map;
//
//        map.set (Core::Variant (667));
//        map.set (Core::Variant (668));
//        map.set (Core::Variant (669));
//        map.set (Core::Variant (670));
//        map.set (Core::Variant (671));
//        map.set (Core::Variant (672));
//
//        BOOST_CHECK (map.size () == 6);
//        BOOST_CHECK (!map.isEmpty ());
//
//        map.clear ();
//
//        BOOST_CHECK (map.size () == 0);
//        BOOST_CHECK (map.isEmpty ());
//
//        Map map2;
//
//        BOOST_CHECK (map2.size () == 0);
//        BOOST_CHECK (map2.isEmpty ());
//}
//
///**
// * Iteratory
// */
//BOOST_AUTO_TEST_CASE (testIteratorsOrder)
//{
//        OrderedVariantMap map;
//
//        map.set (Core::Variant (667));
//        map.set (Core::Variant (668));
//        map.set (Core::Variant (669));
//        map.set (Core::Variant (670));
//        map.set (Core::Variant (671));
//        map.set (Core::Variant (672));
//
//        Iterator i = map.getBegin ();
//
//        BOOST_CHECK (ccast <Pair> (i.get ()));
//
//        Pair p = vcast <Pair> (i.get ());
//
//        BOOST_CHECK (ccast <String> (p.first));
//        BOOST_CHECK (ccast <int> (p.second));
//
//        String key = vcast <String> (p.first);
//        int val = vcast <int> (p.second);
//
//        BOOST_CHECK (key == "k6");
//        BOOST_CHECK (val == 667);
//
//        p = vcast <Pair> ((++i).get ());
//        BOOST_CHECK (vcast <String> (p.first) == "k5");
//        BOOST_CHECK (vcast <int> (p.second) == 668);
//
//        p = vcast <Pair> ((++i).get ());
//        BOOST_CHECK (vcast <String> (p.first) == "k4");
//        BOOST_CHECK (vcast <int> (p.second) == 669);
//
//        p = vcast <Pair> ((++i).get ());
//        BOOST_CHECK (vcast <String> (p.first) == "k3");
//        BOOST_CHECK (vcast <int> (p.second) == 670);
//
//        p = vcast <Pair> ((++i).get ());
//        BOOST_CHECK (vcast <String> (p.first) == "k2");
//        BOOST_CHECK (vcast <int> (p.second) == 671);
//
//        p = vcast <Pair> ((++i).get ());
//        BOOST_CHECK (vcast <String> (p.first) == "k1");
//        BOOST_CHECK (vcast <int> (p.second) == 672);
//
//        i++;
//        BOOST_CHECK (i == map.getEnd ());
//}
//
///**
// * Iteratory
// */
//BOOST_AUTO_TEST_CASE (testIteratorsOrder2)
//{
//        OrderedVariantMap map;
//
//        map.set (Core::Variant (672));
//        map.set (Core::Variant (671));
//        map.set (Core::Variant (670));
//        map.set (Core::Variant (669));
//        map.set (Core::Variant (668));
//        map.set (Core::Variant (667));
//
//        Iterator i = map.getBegin ();
//
//        BOOST_CHECK (ccast <Pair> (i.get ()));
//
//        Pair p = vcast <Pair> (i.get ());
//
//        BOOST_CHECK (ccast <String> (p.first));
//        BOOST_CHECK (ccast <int> (p.second));
//
//        String key = vcast <String> (p.first);
//        int val = vcast <int> (p.second);
//
//        BOOST_CHECK (key == "k1");
//        BOOST_CHECK (val == 672);
//
//        p = vcast <Pair> ((++i).get ());
//        BOOST_CHECK (vcast <String> (p.first) == "k2");
//        BOOST_CHECK (vcast <int> (p.second) == 671);
//
//        p = vcast <Pair> ((++i).get ());
//        BOOST_CHECK (vcast <String> (p.first) == "k3");
//        BOOST_CHECK (vcast <int> (p.second) == 670);
//
//        p = vcast <Pair> ((++i).get ());
//        BOOST_CHECK (vcast <String> (p.first) == "k4");
//        BOOST_CHECK (vcast <int> (p.second) == 669);
//
//        p = vcast <Pair> ((++i).get ());
//        BOOST_CHECK (vcast <String> (p.first) == "k5");
//        BOOST_CHECK (vcast <int> (p.second) == 668);
//
//        p = vcast <Pair> ((++i).get ());
//        BOOST_CHECK (vcast <String> (p.first) == "k6");
//        BOOST_CHECK (vcast <int> (p.second) == 667);
//
//        i++;
//        BOOST_CHECK (i == map.getEnd ());
//}
//
//BOOST_AUTO_TEST_SUITE_END ();
