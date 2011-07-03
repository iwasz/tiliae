/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>

#include "../../core/Pointer.h"
#include "../wrapper/ICallableWrapper.h"
#include "../wrapper/MethodWrapper.h"
#include "../reflectAnnotations/CollectionAnnotation.h"
#include "../../core/Typedefs.h"

/*##########################################################################*/

BOOST_AUTO_TEST_SUITE (CollectionTest11);

using namespace boost;
using namespace Core;
using namespace Reflection;

/**
 *
 */
BOOST_AUTO_TEST_CASE (testAnnotationVector)
{
        CollectionAnnotation <StringVector>::run ("StringVector2");

        Ptr <Class> cls = Manager::classForName ("StringVector2");
        BOOST_REQUIRE (cls);

        Ptr <Constructor> constr = cls->getConstructor ();
        BOOST_REQUIRE (constr);

        Variant obj = constr->newInstance ();

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <StringVector *> (obj));

        Ptr<Method> set = cls->getMethod ("set", 2);
        BOOST_REQUIRE (set);

        Ptr<Method> get = cls->getMethod ("get", 1);
        BOOST_REQUIRE (get);

        Ptr<Method> add = cls->getMethod ("add", 1);
        BOOST_REQUIRE (add);



        StringVector *newV = vcast <StringVector *> (obj);
        BOOST_REQUIRE (newV);

        add->invoke (obj, Variant ("hfksfdkjsfd"));
        BOOST_REQUIRE_EQUAL (newV->size (), 1);
        BOOST_REQUIRE_EQUAL (newV->front(), "hfksfdkjsfd");

        Variant ret = get->invoke (obj, Variant (0U));

        BOOST_REQUIRE (!ret.isNone ());
        BOOST_REQUIRE (ccast <std::string> (ret));
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret), "hfksfdkjsfd");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testAnnotationList)
{
        Ptr <Class> cls = Manager::classForName ("StringList");
        BOOST_REQUIRE (cls);

        Ptr <Constructor> constr = cls->getConstructor ();
        BOOST_REQUIRE (constr);

        Variant obj = constr->newInstance ();

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <StringList *> (obj));

        Ptr<Method> set = cls->getMethod ("set", 2);
        BOOST_REQUIRE (set);

        Ptr<Method> get = cls->getMethod ("get", 1);
        BOOST_REQUIRE (get);

        Ptr<Method> add = cls->getMethod ("add", 1);
        BOOST_REQUIRE (add);



        StringList *newV = vcast <StringList *> (obj);
        BOOST_REQUIRE (newV);

        add->invoke (obj, Variant ("hfksfdkjsfd"));
        BOOST_REQUIRE_EQUAL (newV->size (), 1);
        BOOST_REQUIRE_EQUAL (newV->front(), "hfksfdkjsfd");

        // A tutaj podajemy indeks jako string - on sie sam skonwertuje do u-int.
        Variant ret = get->invoke (obj, Variant ("0"));

        BOOST_REQUIRE (!ret.isNone ());
        BOOST_REQUIRE (ccast <std::string> (ret));
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret), "hfksfdkjsfd");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testAnnotationSet)
{
        Ptr <Class> cls = Manager::classForName ("StringSet");
        BOOST_REQUIRE (cls);

        Ptr <Constructor> constr = cls->getConstructor ();
        BOOST_REQUIRE (constr);

        Variant obj = constr->newInstance ();

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <StringSet *> (obj));

        Ptr<Method> get = cls->getMethod ("get", 1);
        BOOST_REQUIRE (get);

        Ptr<Method> add = cls->getMethod ("add", 1);
        BOOST_REQUIRE (add);

        StringSet *newV = vcast <StringSet *> (obj);
        BOOST_REQUIRE (newV);

        add->invoke (obj, Variant ("hfksfdkjsfd"));
        BOOST_REQUIRE_EQUAL (newV->size (), 1);
        BOOST_REQUIRE (newV->find("hfksfdkjsfd") != newV->end ());

        Variant ret = get->invoke (obj, Variant ("hfksfdkjsfd"));

        BOOST_REQUIRE (!ret.isNone ());
        BOOST_REQUIRE (ccast <std::string> (ret));
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret), "hfksfdkjsfd");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testAnnotationMap)
{
        Ptr <Class> cls = Manager::classForName ("StringMap");
        BOOST_REQUIRE (cls);

        Ptr <Constructor> constr = cls->getConstructor ();
        BOOST_REQUIRE (constr);

        Variant obj = constr->newInstance ();

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <StringMap *> (obj));

        Ptr<Method> get = cls->getMethod ("get", 1);
        BOOST_REQUIRE (get);

        Ptr<Method> set = cls->getMethod ("set", 2);
        BOOST_REQUIRE (set);

        StringMap *newV = vcast <StringMap *> (obj);
        BOOST_REQUIRE (newV);

        VariantVector args;
        args.push_back (Variant ("ala"));
        args.push_back (Variant ("makota"));
        set->invoke (obj, &args);

        BOOST_REQUIRE_EQUAL (newV->size (), 1);
        BOOST_REQUIRE_EQUAL (newV->operator [] ("ala"), std::string ("makota"));

        Variant ret = get->invoke (obj, Variant ("ala"));

        BOOST_REQUIRE (!ret.isNone ());
        BOOST_REQUIRE (ccast <std::string> (ret));
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret), "makota");
}

/**
 * Testy customowych kolekcji.
 */
BOOST_AUTO_TEST_CASE (testCustomCollections)
{
    Ptr <Class> cls = Manager::classForName ("AddressList");
    BOOST_REQUIRE (cls);

    Ptr <Constructor> constr = cls->getConstructor ();
    BOOST_REQUIRE (constr);

    Variant obj = constr->newInstance ();
    BOOST_REQUIRE (!obj.isNone ());

    Ptr<Method> get = cls->getMethod ("get", 1);
    BOOST_REQUIRE (get);

    Ptr<Method> set = cls->getMethod ("set", 2);
    BOOST_REQUIRE (set);

    cls = Manager::classForName ("BarList");
    BOOST_REQUIRE (cls);

    cls = Manager::classForName ("BarMap");
    BOOST_REQUIRE (cls);

    cls = Manager::classForName ("CityList");
    BOOST_REQUIRE (cls);

    cls = Manager::classForName ("CityMap");
    BOOST_REQUIRE (cls);
}

BOOST_AUTO_TEST_SUITE_END ();
