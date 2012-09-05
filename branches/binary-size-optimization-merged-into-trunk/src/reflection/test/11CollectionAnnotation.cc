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
#include "../../core/Iterator.h"

using Core::IIterator;

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

        Class *cls = Manager::classForName ("StringVector2");
        BOOST_REQUIRE (cls);

        Constructor *constr = cls->getConstructor ();
        BOOST_REQUIRE (constr);

        Variant obj = constr->newInstance ();

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <StringVector *> (obj));

        Method *set = cls->getMethod ("set", 2);
        BOOST_REQUIRE (set);

        Method *get = cls->getMethod ("get", 1);
        BOOST_REQUIRE (get);

        Method *add = cls->getMethod ("add", 1);
        BOOST_REQUIRE (add);



        StringVector *newV = vcast <StringVector *> (obj);
        BOOST_REQUIRE (newV);

        add->invoke (obj, Variant ("hfksfdkjsfd"));
        BOOST_REQUIRE_EQUAL (newV->size (), 1U);
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
        Class *cls = Manager::classForName ("StringList");
        BOOST_REQUIRE (cls);

        Constructor *constr = cls->getConstructor ();
        BOOST_REQUIRE (constr);

        Variant obj = constr->newInstance ();

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <StringList *> (obj));

        Method *set = cls->getMethod ("set", 2);
        BOOST_REQUIRE (set);

        Method *get = cls->getMethod ("get", 1);
        BOOST_REQUIRE (get);

        Method *add = cls->getMethod ("add", 1);
        BOOST_REQUIRE (add);



        StringList *newV = vcast <StringList *> (obj);
        BOOST_REQUIRE (newV);

        add->invoke (obj, Variant ("hfksfdkjsfd"));
        BOOST_REQUIRE_EQUAL (newV->size (), 1U);
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
        Class *cls = Manager::classForName ("StringSet");
        BOOST_REQUIRE (cls);

        Constructor *constr = cls->getConstructor ();
        BOOST_REQUIRE (constr);

        Variant obj = constr->newInstance ();

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <StringSet *> (obj));

        Method *get = cls->getMethod ("get", 1);
        BOOST_REQUIRE (get);

        Method *add = cls->getMethod ("add", 1);
        BOOST_REQUIRE (add);

        StringSet *newV = vcast <StringSet *> (obj);
        BOOST_REQUIRE (newV);

        add->invoke (obj, Variant ("hfksfdkjsfd"));
        BOOST_REQUIRE_EQUAL (newV->size (), 1U);
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
        Class *cls = Manager::classForName ("StringMap");
        BOOST_REQUIRE (cls);

        Constructor *constr = cls->getConstructor ();
        BOOST_REQUIRE (constr);

        Variant obj = constr->newInstance ();

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <StringMap *> (obj));

        Method *get = cls->getMethod ("get", 1);
        BOOST_REQUIRE (get);

        Method *set = cls->getMethod ("set", 2);
        BOOST_REQUIRE (set);

        StringMap *newV = vcast <StringMap *> (obj);
        BOOST_REQUIRE (newV);

        VariantVector args;
        args.push_back (Variant ("ala"));
        args.push_back (Variant ("makota"));
        set->invoke (obj, &args);

        BOOST_REQUIRE_EQUAL (newV->size (), 1U);
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
    Class *cls = Manager::classForName ("AddressList");
    BOOST_REQUIRE (cls);

    Constructor *constr = cls->getConstructor ();
    BOOST_REQUIRE (constr);

    Variant obj = constr->newInstance ();
    BOOST_REQUIRE (!obj.isNone ());

    Method *get = cls->getMethod ("get", 1);
    BOOST_REQUIRE (get);

    Method *set = cls->getMethod ("set", 2);
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

/**
 *
 */
BOOST_AUTO_TEST_CASE (testVectorIterator)
{
        Class *cls = Manager::classForName ("StringVector");
        BOOST_REQUIRE (cls);

        Constructor *constr = cls->getConstructor ();
        BOOST_REQUIRE (constr);

        Variant obj = constr->newInstance ();

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <StringVector *> (obj));

        StringVector *strV = vcast <StringVector *> (obj);
        strV->push_back ("ala");
        strV->push_back ("MA");
        strV->push_back ("KOTA");
        strV->push_back ("PSA");

        Method *iterator = cls->getMethod ("iterator");
        BOOST_REQUIRE (iterator);
        Ptr <IIterator> i = ocast <Ptr <IIterator> > (iterator->invoke (obj));

        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "ala");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "MA");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "KOTA");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "PSA");
        BOOST_REQUIRE (!i->hasNext ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testListIterator)
{
        Class *cls = Manager::classForName ("StringList");
        BOOST_REQUIRE (cls);

        Constructor *constr = cls->getConstructor ();
        BOOST_REQUIRE (constr);

        Variant obj = constr->newInstance ();

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <StringList *> (obj));

        StringList *strV = vcast <StringList *> (obj);
        strV->push_back ("ala");
        strV->push_back ("MA");
        strV->push_back ("KOTA");
        strV->push_back ("PSA");

        Method *iterator = cls->getMethod ("iterator");
        BOOST_REQUIRE (iterator);
        Ptr <IIterator> i = ocast <Ptr <IIterator> > (iterator->invoke (obj));

        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "ala");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "MA");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "KOTA");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "PSA");
        BOOST_REQUIRE (!i->hasNext ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testListSet)
{
        Class *cls = Manager::classForName ("StringSet");
        BOOST_REQUIRE (cls);

        Constructor *constr = cls->getConstructor ();
        BOOST_REQUIRE (constr);

        Variant obj = constr->newInstance ();

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <StringSet *> (obj));

        StringSet *strV = vcast <StringSet *> (obj);
        strV->insert ("ala");
        strV->insert ("MA");
        strV->insert ("KOTA");
        strV->insert ("PSA");

        Method *iterator = cls->getMethod ("iterator");
        BOOST_REQUIRE (iterator);
        Ptr <IIterator> i = ocast <Ptr <IIterator> > (iterator->invoke (obj));

        // Assume ascii
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "KOTA");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "MA");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "PSA");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "ala");
        BOOST_REQUIRE (!i->hasNext ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testListMap)
{
        Class *cls = Manager::classForName ("StringMap");
        BOOST_REQUIRE (cls);

        Constructor *constr = cls->getConstructor ();
        BOOST_REQUIRE (constr);

        Variant obj = constr->newInstance ();

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <StringMap *> (obj));

        StringMap *strV = vcast <StringMap *> (obj);
        (*strV)["a"] = "1";
        (*strV)["b"] = "2";
        (*strV)["c"] = "3";

        Method *iterator = cls->getMethod ("iterator");
        BOOST_REQUIRE (iterator);
        Ptr <IIterator> i = ocast <Ptr <IIterator> > (iterator->invoke (obj));

        BOOST_REQUIRE (i->hasNext ());
        std::pair <std::string const, std::string> p = vcast <std::pair <std::string const, std::string> > (i->next ());
        BOOST_REQUIRE_EQUAL (p.first, "a");
        BOOST_REQUIRE_EQUAL (p.second, "1");

        BOOST_REQUIRE (i->hasNext ());
        std::pair <std::string const, std::string> p2 = vcast <std::pair <std::string const, std::string> > (i->next ());
        BOOST_REQUIRE_EQUAL (p2.first, "b");
        BOOST_REQUIRE_EQUAL (p2.second, "2");

        BOOST_REQUIRE (i->hasNext ());
        std::pair <std::string const, std::string> p3 = vcast <std::pair <std::string const, std::string> > (i->next ());
        BOOST_REQUIRE_EQUAL (p3.first, "c");
        BOOST_REQUIRE_EQUAL (p3.second, "3");

        BOOST_REQUIRE (!i->hasNext ());
}

BOOST_AUTO_TEST_SUITE_END ();
