/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#define BOOST_TEST_MODULE BeanWrapperTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <iostream>

#include "variant/Cast.h"
#include "../../beanWrapper/IBeanWrapper.h"
#include "../beanWrapper/BeanWrapper.h"
#include "../../reflection/annotations/AnnotationManager.h"
#include "../../reflection/Manager.h"
#include "../../testHelpers/Address.h"
#include "../../testHelpers/City.h"
#include "../../testHelpers/Country.h"
#include <typeinfo>
#include "../plugins/PropertyRWBeanWrapperPlugin.h"
#include "../plugins/GetPutMethodRWBeanWrapperPlugin.h"
#include <boost/make_shared.hpp>
#include "../plugins/MethodPlugin.h"
#include "../../testHelpers/Bar.h"
#include "../../testHelpers/Foo.h"
#include "../../core/DebugContext.h"

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (BWTest01);
using namespace Wrapper;
using namespace Core;
using namespace Common;

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testGeneral)
{
        IBeanWrapper *beanWrapper = new BeanWrapper ();
        delete beanWrapper;
}

/****************************************************************************/

/**
 *  Testuje single plugin - wklada i wyjmuje do niego jeden integer.
 */
BOOST_AUTO_TEST_CASE (testSinglePlugin)
{
        BeanWrapper *beanWrapper = new BeanWrapper ();

        Variant i = Core::Variant (666);
        // To jest to samo co beanWrapper->setWrappedObject
        beanWrapper->set ("this", i);
        // To jest to samo co beanWrapper->getWrappedObject
        Variant j = beanWrapper->get ("this");
        int ii = vcast <int> (j);
        BOOST_REQUIRE_EQUAL (ii, 666);

        // A teraz zmieniamy obiekt warpowany!
        Variant s = Core::Variant (String ("ala ma kota"));
        beanWrapper->set ("this", s);
        Variant t = beanWrapper->get ("this");
        String S = vcast <String> (t);
        BOOST_REQUIRE_EQUAL (S, "ala ma kota");

        delete beanWrapper;
}

/****************************************************************************/

/**
 *  Testowaine plugina od setterow i getterow,
 */
BOOST_AUTO_TEST_CASE (testSetterGetterPlugin)
{
        int noOfAnnotations = Annotations::AnnotationManager::instance ().getAnnotationList ().size ();
        BOOST_CHECK (noOfAnnotations > 0);

//        std::cerr << Annotations::AnnotationManager::instance ().toString() << std::endl;
//        std::cerr << Reflection::Manager::instance ().toString() << std::endl;

        // Po pierwsze powtórz test z ReflectionTest.
        Reflection::Class *cls = Reflection::Manager::classForName ("Address");
        BOOST_REQUIRE (cls);

        cls = Reflection::Manager::classForType (typeid (Address));
        BOOST_REQUIRE (cls);

        // OK...

        Ptr <BeanWrapper> beanWrapper = boost::make_shared <BeanWrapper> ();
        beanWrapper->addPlugin (new PropertyRWBeanWrapperPlugin);

        Country country;
        country.setName ("Polska");

        City city;
        city.setName ("Warszawa");

        Address address;
        address.setStreet ("katalonska");
        address.setPostalCode ("02-673");
        address.setCity (&city);
        address.setCountry (&country);

        beanWrapper->setWrappedObject (Core::Variant (&address));
        Variant vv = beanWrapper->getWrappedObject ();
        BOOST_REQUIRE (vv.isHandle ());
        Address *pa = vcast <Address *> (vv);
        BOOST_REQUIRE_EQUAL (pa, &address);

//        BOOST_REQUIRE (!beanWrapper->get ("").isNone ());
        BOOST_REQUIRE (!beanWrapper->get ("postalCode").isNone ());
        BOOST_REQUIRE (vcast <String> (beanWrapper->get ("postalCode")) == "02-673");
        BOOST_REQUIRE (vcast <String> (beanWrapper->get ("street")) == "katalonska");
        BOOST_REQUIRE (vcast <std::string> (beanWrapper->get ("city.name")) == "Warszawa");
        BOOST_REQUIRE (vcast <Core::String> (beanWrapper->get ("country.name")) == "Polska");

        beanWrapper->set ("postalCode", Core::Variant (String ("ala")));
        beanWrapper->set ("street", Core::Variant (String ("ma")));
        beanWrapper->set ("city.name", Core::Variant ("kota"));
        beanWrapper->set ("country.name", Core::Variant (String ("psa")));

        BOOST_REQUIRE (address.getPostalCode () == "ala");
        BOOST_REQUIRE (address.getStreet () == "ma");
        BOOST_REQUIRE (address.getCity ()->getName () == "kota");
        BOOST_REQUIRE (address.getCountry ()->getName () == "psa");

        // Czy zrzuci wyjątek kiedy pobieramy coś czego nie ma?
        bool err;
        beanWrapper->get ("adrea", &err);
        BOOST_REQUIRE_EQUAL(err, true);
        beanWrapper->get ("adres.asg", &err);
        BOOST_REQUIRE_EQUAL(err, true);
        beanWrapper->get ("adres.city.nam", &err);
        BOOST_REQUIRE_EQUAL(err, true);
        beanWrapper->get ("adres.city.namea", &err);
        BOOST_REQUIRE_EQUAL(err, true);
        beanWrapper->get ("adres.city.name.a", &err);
        BOOST_REQUIRE_EQUAL(err, true);

        // Na tych 3ech sie wywalaja asercje w srodu i niech sobie robia co chca.
//        BOOST_REQUIRE (beanWrapper->get ("...aslkaslij..").getType () == Core::NONE);
//        BOOST_REQUIRE (beanWrapper->get (".").getType () == Core::NONE);

        /*
         * Set może zrzucić i getException i setException!
         */
        bool ret;
        ret = beanWrapper->set ("adres.postalCode", Core::Variant (String ("ala")));
        BOOST_REQUIRE_EQUAL(ret, false);
        ret = beanWrapper->set ("adres.street", Core::Variant (String ("ma")));
        BOOST_REQUIRE_EQUAL(ret, false);
        ret = beanWrapper->set ("adres.city.name", Core::Variant (String ("kota")));
        BOOST_REQUIRE_EQUAL(ret, false);
        ret = beanWrapper->set ("adres.country.name", Core::Variant (String ("psa")));
        BOOST_REQUIRE_EQUAL(ret, false);
        ret = beanWrapper->set ("adres.country.aname", Core::Variant (String ("psa")));
        BOOST_REQUIRE_EQUAL(ret, false);

/*--------------------------------------------------------------------------*/

        // A tu podejscie 2. Robimy to samo co wyzej, ale wariant jest inicjowany nie wskaźnikiem, a const &
        Variant vv2 = Core::Variant (address);  // Kopia adresu tu się robi!
        beanWrapper->setWrappedObject (vv2);
        BOOST_REQUIRE (vv2.isHandle());
        Address const *pa2 = vcast <Address const *> (vv2);

        // To jest kopia, więc będą się różnić
        BOOST_REQUIRE_NE (pa2, &address);

        BOOST_REQUIRE (pa2->getPostalCode () == "ala");
        BOOST_REQUIRE (pa2->getStreet () == "ma");
        BOOST_REQUIRE (pa2->getCity ()->getName () == "kota");
        BOOST_REQUIRE (pa2->getCountry ()->getName () == "psa");

        Address *a = vcast <Address *> (vv2);
        a->setPostalCode ("asia");
        a->setStreet ("krzyczy");
        a->getCity ()->setName ("kiedy idzie");
        a->getCountry()->setName ("do sklepu");

        /*
         * Nie da się pobrac wskaznika do wrapowanego obiektu!
         * Nie da się, bo getWrappedObject zawsze zwraca kopie
         * warianta, a poniewaz wariant jest value, to obiekt
         * wrapowany sie tez skopiuje.
         */
        BOOST_REQUIRE (vcast <String> (beanWrapper->get ("postalCode")) == "asia");
        BOOST_REQUIRE (vcast <String> (beanWrapper->get ("street")) == "krzyczy");
        BOOST_REQUIRE (vcast <std::string> (beanWrapper->get ("city.name")) == "kiedy idzie");
        BOOST_REQUIRE (vcast <String> (beanWrapper->get ("country.name")) == "do sklepu");

        // Mozna uzywac obiektu tylko, gdy wyciagniemy go spowrotem w ten sposob:
        Address fromWrapper = vcast <Address> (beanWrapper->getWrappedObject ());

        BOOST_REQUIRE (fromWrapper.getPostalCode () == "asia");
        BOOST_REQUIRE (fromWrapper.getStreet () == "krzyczy");
        BOOST_REQUIRE (fromWrapper.getCity ()->getName () == "kiedy idzie");
        BOOST_REQUIRE (fromWrapper.getCountry ()->getName () == "do sklepu");

        // Lub jako wskaznik, ale do oibektu, ktory nie jest tymczasowy:
        Variant tmp = beanWrapper->getWrappedObject ();
        // tmp musi caly czas istniec, kiedy uzywamy ps2.
        pa2 = vcast <Address const *> (tmp);

        BOOST_REQUIRE (pa2->getPostalCode () == "asia");
        BOOST_REQUIRE (pa2->getStreet () == "krzyczy");
        BOOST_REQUIRE (pa2->getCity ()->getName () == "kiedy idzie");
        BOOST_REQUIRE (pa2->getCountry ()->getName () == "do sklepu");
}

/**
 * To jest test pluginu get put, czyli takiego, ktory
 * obsluguje metody get i set (lub put) w obiekcie.
 *
 * To ma dzialac dla map/
 */
BOOST_AUTO_TEST_CASE (testGetPutPlugin)
{
        Ptr <BeanWrapper> beanWrapper = boost::make_shared <BeanWrapper> ();
        beanWrapper->addPlugin (new GetPutMethodRWBeanWrapperPlugin);

/*##########################################################################*/

        StringMap stringMap;
        stringMap["key1"] = "value1";
        stringMap["key2"] = "value2";

        // To samo co setWrappedObject
        // beanWrapper->set ("", Core::Variant (stringMap));
        beanWrapper->setWrappedObject (Core::Variant (stringMap));

        BOOST_REQUIRE_EQUAL (vcast <std::string> (beanWrapper->get ("key1")), "value1");
        BOOST_REQUIRE_EQUAL (vcast <std::string> (beanWrapper->get ("key2")), "value2");

        VariantMap vMap;
        vMap["strMap"] = Core::Variant (stringMap);
        vMap["a"] = Core::Variant (String ("aa"));

        beanWrapper->setWrappedObject (Core::Variant (vMap));

        BOOST_REQUIRE (vcast <String> (beanWrapper->get ("a")) == "aa");
        BOOST_REQUIRE (vcast <std::string> (beanWrapper->get ("strMap.key1")) == "value1");
        BOOST_REQUIRE (vcast <std::string> (beanWrapper->get ("strMap.key2")) == "value2");

        bool err;
        beanWrapper->get ("adrea", &err);
        BOOST_REQUIRE_EQUAL (err, true);
        beanWrapper->get ("adres.asg", &err).getTypeInfo ();
        BOOST_REQUIRE_EQUAL (err, true);
        beanWrapper->get ("adres.city.nam", &err).getTypeInfo ();
        BOOST_REQUIRE_EQUAL (err, true);
        beanWrapper->get ("adres.city.namea", &err).getTypeInfo ();
        BOOST_REQUIRE_EQUAL (err, true);
        beanWrapper->get ("adres.city.name.a", &err).getTypeInfo ();
        BOOST_REQUIRE_EQUAL (err, true);
}

/**
 * A to jest test tez tego plugina, co obsluguje metody get i set, ale
 * teraz probujemy go na mapie.
 */
BOOST_AUTO_TEST_CASE (testGetPutPlugin2)
{
        Ptr <BeanWrapper> beanWrapper = boost::make_shared <BeanWrapper> ();
        beanWrapper->addPlugin (new GetPutMethodRWBeanWrapperPlugin);

/*##########################################################################*/

        StringMap stringMap;
        stringMap["key1"] = "value1";
        stringMap["key2"] = "value2";

        VariantMap vMap;
        vMap["sMap"] = Core::Variant (&stringMap);

        beanWrapper->setWrappedObject (Core::Variant (&vMap));

        BOOST_REQUIRE (vcast <std::string> (beanWrapper->get ("sMap.key1")) == "value1");
        BOOST_REQUIRE (vcast <std::string> (beanWrapper->get ("sMap.key2")) == "value2");

/*##########################################################################*/


        beanWrapper->set ("sMap.key1", Core::Variant ("kupa"));
        //std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << stringMap.get ("key1") << std::endl;
        BOOST_REQUIRE (stringMap["key1"] == "kupa");

        beanWrapper->set ("sMap.key2", Core::Variant ("miekkaKupa"));
        //std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << stringMap.get ("key1") << std::endl;
        BOOST_REQUIRE (stringMap["key2"] == "miekkaKupa");

/*##########################################################################*/

        // Troche zagniezdzania...
        VariantMap vMap1;
        vMap1["vMap"] = Core::Variant (&vMap);

        VariantMap vMap2;
        vMap2["vMap1"] = Core::Variant (&vMap1);

        beanWrapper->setWrappedObject (Core::Variant (&vMap2));

        BOOST_REQUIRE (vcast <std::string> (beanWrapper->get ("vMap1.vMap.sMap.key1")) == "kupa");
        BOOST_REQUIRE (vcast <std::string> (beanWrapper->get ("vMap1.vMap.sMap.key2")) == "miekkaKupa");
}


/**
 *  Testuje SimpleBeanWrapper.
 */
BOOST_AUTO_TEST_CASE (testSimpleBeanWrapper)
{
        StringMap stringMap;
        stringMap["key1"] = "value1";
        stringMap["key2"] = "value2";

        VariantMap vMap;
        vMap["sMap"] = Core::Variant (&stringMap);

        //beanWrapper->set ("vMap", Core::Variant (&vMap));
        //beanWrapper->set ("sMap", Core::Variant (&stringMap));

        BeanWrapper *beanWrapper = BeanWrapper::create (Core::Variant (vMap));

        BOOST_REQUIRE (vcast <std::string> (beanWrapper->get ("sMap.key1")) == "value1");
        BOOST_REQUIRE (vcast <std::string> (beanWrapper->get ("sMap.key2")) == "value2");

        delete beanWrapper;
}

#if 0
/**
 *  Testuje zagniezdzone simplebeanWrappery, ale tylko pobieranie
 *  z nich wartosci, czyli niec nie jest ustawiane metoda set, ale
 *  tylko pobierane metoda get.
 */
void BeanWrapperTest::testNestedSimpleBeanWrappersGet ()
{
        StringMap stringMap;
        stringMap["key1", "value1");
        stringMap["key2", "value2");

        VariantMap vMap;
        vMap["sMap", Core::Variant (&stringMap));

        Ptr <BeanWrapper> beanWrapper = BeanWrapper::create (Core::Variant (vMap));

        BOOST_REQUIRE (vcast <String> (beanWrapper->get ("sMap.key1")) == "value1");
        BOOST_REQUIRE (vcast <String> (beanWrapper->get ("sMap.key2")) == "value2");

        shared_ptr <IBeanWrapper> beanWrapper2 = SimpleBeanWrapper::create (Core::Variant (beanWrapper));

        BOOST_REQUIRE (vcast <String> (beanWrapper2->get ("sMap.key1")) == "value1");
        BOOST_REQUIRE (vcast <String> (beanWrapper2->get ("sMap.key2")) == "value2");
}

/**
 *  Testuje zagniezdzone simplebeanWrappery i to za rowno
 *  pobieranie jak i ustawianie propertisow wrapowanych obiektow.
 */
void BeanWrapperTest::testNestedSimpleBeanWrappersSet ()
{
        StringMap stringMap;
        stringMap.put ("key1", "value1");
        stringMap.put ("key2", "value2");

        VariantMap vMap;
        vMap.put ("sMap", Core::Variant (&stringMap));

        IBeanWrapper *beanWrapper = SimpleBeanWrapper::create (Core::Variant (vMap));
        IBeanWrapper *beanWrapper2 = SimpleBeanWrapper::create (Core::Variant (beanWrapper));

        beanWrapper->set ("sMap.key1", Core::Variant (String ("suzuki")));
        beanWrapper->set ("sMap.key2", Core::Variant (String ("honda")));

        BOOST_REQUIRE (vcast <String> (beanWrapper->get ("sMap.key1")) == "suzuki");
        BOOST_REQUIRE (vcast <String> (beanWrapper->get ("sMap.key2")) == "honda");

        beanWrapper2->set ("sMap.key1", Core::Variant (String ("yamaha")));
        beanWrapper2->set ("sMap.key2", Core::Variant (String ("kawasaki")));

        BOOST_REQUIRE (vcast <String> (beanWrapper2->get ("sMap.key1")) == "yamaha");
        BOOST_REQUIRE (vcast <String> (beanWrapper2->get ("sMap.key2")) == "kawasaki");
}

/**
 *  Testuje zagniezdzone beanWrappery!
 */
void BeanWrapperTest::testNestedBeanWrappers ()
{
        /*
        BeanWrapper *beanWrapper = new BeanWrapper ();

        IContainingBeanWrapperPlugin *containingPlugin = new MapBeanWrapperPlugin (); //(sic!)SingleVariantBeanWrapperPlugin ();
        beanWrapper->setBeanContainingPlugin (containingPlugin);

        BeanWrapperPluginList *pluginList = new BeanWrapperPluginList ();

        IBeanWrapperPlugin *plugin = new PropertyRWBeanWrapperPlugin ();
        pluginList->push_back (plugin);

        plugin = new GetPutMethodRWBeanWrapperPlugin ();
        pluginList->push_back (plugin);

        plugin = new ChildBeanWrapperPlugin ();
        pluginList->push_back (plugin);

        beanWrapper->setPluginList (pluginList);
        */
/*--------------------------------------------------------------------------*/
        /*
        BeanWrapper *beanWrapper2 = new BeanWrapper ();

        IContainingBeanWrapperPlugin *containingPlugin2 = new MapBeanWrapperPlugin (); //(sic!)SingleVariantBeanWrapperPlugin ();
        beanWrapper2->setBeanContainingPlugin (containingPlugin2);

        BeanWrapperPluginList *pluginList2 = new BeanWrapperPluginList ();

        plugin = new PropertyRWBeanWrapperPlugin ();
        pluginList2->push_back (plugin);

        plugin = new GetPutMethodRWBeanWrapperPlugin ();
        pluginList2->push_back (plugin);

        plugin = new ChildBeanWrapperPlugin ();
        pluginList2->push_back (plugin);

        beanWrapper2->setPluginList (pluginList2);
        */
/*##########################################################################*/

        StringMap stringMap;
        stringMap.put ("key1", "value1");
        stringMap.put ("key2", "value2");

        VariantMap vMap;
        vMap.put ("sMap", Core::Variant (&stringMap));

        //beanWrapper2->set ("vMap", Core::Variant (&vMap));
        //beanWrapper2->set ("sMap", Core::Variant (&stringMap));

        //beanWrapper->set ("wrapper", Core::Variant (beanWrapper2));

        IBeanWrapper *beanWrapper = SimpleBeanWrapper::create (Core::Variant (vMap));

        BOOST_REQUIRE (vcast <String> (beanWrapper->get ("sMap.key1")) == "value1");
        BOOST_REQUIRE (vcast <String> (beanWrapper->get ("sMap.key2")) == "value2");

        IBeanWrapper *beanWrapper2 = SimpleBeanWrapper::create (Core::Variant (beanWrapper));

        BOOST_REQUIRE (vcast <String> (beanWrapper2->get ("sMap.key1")) == "value1");
        BOOST_REQUIRE (vcast <String> (beanWrapper2->get ("sMap.key2")) == "value2");


        /**
         *  Tu sprawdzamy zwykly get, czy dziala od poczatku (nic nie ustawialem
         *  za pomocaIBeanWrapper::set
         */
        //BOOST_REQUIRE (vcast <String> (beanWrapper->get ("wrapper.sMap.key1")) == "value1");
        //BOOST_REQUIRE (vcast <String> (beanWrapper->get ("wrapper.sMap.key2")) == "value2");

        //BOOST_REQUIRE (vcast <String> (beanWrapper->get ("wrapper.vMap.sMap.key1")) == "value1");
        //BOOST_REQUIRE (vcast <String> (beanWrapper->get ("wrapper.vMap.sMap.key2")) == "value2");

/*##########################################################################*/

        /**
         *  A tu sprawdzam, czy na tak zagniezdzonych BeanWrapperach dziala takze set.
         *  Najpierw ustawiam property za pomoca IBeanWrapper::set, a potem pobieram
         *  getem.
         */
        //beanWrapper->set ("wrapper.sMap.key1", Core::Variant (String ("kupa")));
        //std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << stringMap.get ("key1") << std::endl;
        //BOOST_REQUIRE (stringMap.get ("key1") == "kupa");

        //beanWrapper->set ("wrapper.vMap.sMap.key1", Core::Variant (String ("miekkaKupa")));
        //std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << stringMap.get ("key1") << std::endl;
        //BOOST_REQUIRE (stringMap.get ("key1") == "miekkaKupa");

        //delete getterSetterPlugin;
        //delete pluginList;
        //delete containingPlugin;
        //delete beanWrapper;
}

#endif

BOOST_AUTO_TEST_CASE (testListPlugin)
{
        BeanWrapper beanWrapper;
        beanWrapper.addPlugin (new PropertyRWBeanWrapperPlugin);
        beanWrapper.addPlugin (new GetPutMethodRWBeanWrapperPlugin);
        beanWrapper.addPlugin (new MethodPlugin (MethodPlugin::METHOD));

/*##########################################################################*/

        StringList stringList;
        stringList.push_back ("value0");
        stringList.push_back ("value1");
        stringList.push_back ("value2");
        stringList.push_back ("value3");

        // Musi byc wariant handle, bo tylko takie da sie polimorficznie rzutować (na IList *).
        beanWrapper.setWrappedObject (Core::Variant (&stringList));

        Variant v1 = beanWrapper.get ("0");

#       if 0
        Core::Type t = v1.getType ();
        Core::Containing c = v1.getContaining ();
        const std::type_info *ti = v1.getTypeInfo ();
        bool b1 = can_cast <String> (v1);
        bool b2 = can_cast <String &> (v1);
        bool b3 = can_cast <const String &> (v1);
        bool b4 = can_cast <String *> (v1);
        bool b5 = can_cast <const String *> (v1);
#endif

        String s = vcast <std::string> (v1);
        BOOST_REQUIRE (s == "value0");
        BOOST_REQUIRE (vcast <std::string> (beanWrapper.get ("1")) == "value1");
        BOOST_REQUIRE (vcast <std::string> (beanWrapper.get ("2")) == "value2");
        BOOST_REQUIRE (vcast <std::string> (beanWrapper.get ("3")) == "value3");

        VariantList vList1;
        vList1.push_back (Core::Variant (&stringList));
        vList1.push_back (Core::Variant (&stringList));
        vList1.push_back (Core::Variant (&stringList));

        VariantList vList2;
        vList2.push_back (Core::Variant (&vList1));
        vList2.push_back (Core::Variant (&vList1));
        vList2.push_back (Core::Variant (&vList1));

        VariantList vList3;
        vList3.push_back (Core::Variant (&vList2));
        vList3.push_back (Core::Variant (&vList2));
        vList3.push_back (Core::Variant (&vList2));
        vList3.push_back (Core::Variant (&vList2));

        // To samo co setWrappedObject
        beanWrapper.setWrappedObject (Core::Variant (&vList3));

        BOOST_REQUIRE_EQUAL (vcast <std::string> (beanWrapper.get ("3.2.1.0")), "value0");

        beanWrapper.set ("0.0.0.2", Core::Variant ("kupa"));
        StringList::iterator i = stringList.begin ();
        ++i; ++i;
        BOOST_REQUIRE_EQUAL (*i, "kupa");

        StringList stringList2;
        stringList2.push_back ("poznoJuzKu.wa");
        VariantList vList4;
        vList4.push_back (Core::Variant (&stringList2));
        beanWrapper.set ("0.0.1", Core::Variant (&vList4));

        BOOST_REQUIRE_EQUAL (vcast <std::string> (beanWrapper.get ("0.0.1.0.0")), "poznoJuzKu.wa");
}

/****************************************************************************/
#if 0
BOOST_AUTO_TEST_CASE (testMapPlugin)
{
        // TODO To sie nie skasuje
        BeanWrapperPluginList *pluginList = new BeanWrapperPluginList ();
        IBeanWrapperPlugin *plugin;

//        IBeanWrapperPlugin *plugin = new PropertyRWBeanWrapperPlugin ();
//        pluginList->push_back (plugin);

        plugin = new MapPlugin;
        pluginList->push_back (plugin);

//        plugin = new GetPutMethodRWBeanWrapperPlugin ();
//        pluginList->push_back (plugin);
//
//        plugin = new MethodPlugin (MethodPlugin::METHOD);
//        pluginList->push_back (plugin);

        BeanWrapper beanWrapper;
        beanWrapper.setPluginList (pluginList);

/*##########################################################################*/

        StringMap stringMap;
        stringMap["key0", "value0");
        stringMap["key1", "value1");
        stringMap["key2", "value2");
        stringMap["key3", "value3");

        // Musi byc wariant handle, bo tylko takie da sie polimorficznie rzutować (na IList *).
        beanWrapper.setWrappedObject (Core::Variant (&stringMap));

        BOOST_REQUIRE (vcast <String> (beanWrapper.get ("key1")) == "value1");
        BOOST_REQUIRE (vcast <String> (beanWrapper.get ("key2")) == "value2");

        beanWrapper.set ("key4", vcast <Variant> (String ("value4")));
        BOOST_REQUIRE (vcast <String> (beanWrapper.get ("key4")) == "value4");

/*--------------------------------------------------------------------------*/

        VariantMap vMap;

//        Variant vvv = vcast <Variant> (vMap);
//        BOOST_REQUIRE (can_cast <VariantMap *> (vvv));
//        BOOST_REQUIRE (can_cast <IMap *> (vvv));
//        BOOST_REQUIRE (can_cast <const IMap *> (vvv));

        vMap["strMap", Core::Variant (stringMap));
        vMap["a", Core::Variant (String ("aa")));
        Variant obj = vcast<Variant> (&vMap);
        BOOST_REQUIRE (vcast <String> (beanWrapper.get (&obj, "a")) == "aa");

        // To samo co setWrappedObject
        beanWrapper.set ("", Core::Variant (&vMap));

        BOOST_REQUIRE (vcast <String> (beanWrapper.get ("a")) == "aa");
//        BOOST_REQUIRE (vcast <String> (beanWrapper.get ("strMap.key1")) == "value1");
//        BOOST_REQUIRE (vcast <String> (beanWrapper.get ("strMap.key2")) == "value2");
}
#endif
/**
 *
 */
BOOST_AUTO_TEST_CASE (testMethodPlugin)
{
        BeanWrapper beanWrapper;
        beanWrapper.addPlugin (new MethodPlugin);
        beanWrapper.addPlugin (new PropertyRWBeanWrapperPlugin);

/*##########################################################################*/

        Country country;
        country.setName ("Polska");

        City city;
        city.setName ("Warszawa");

        Address address;
        address.setStreet ("katalonska");
        address.setPostalCode ("02-673");
        address.setCity (&city);
        address.setCountry (&country);

        beanWrapper.setWrappedObject (Core::Variant (&address));
        Variant vv = beanWrapper.getWrappedObject ();
        BOOST_REQUIRE (vv.isHandle ());
        Address *pa = vcast <Address *> (vv);
        BOOST_REQUIRE (pa == &address);

//        BOOST_REQUIRE (!beanWrapper.get ("").isNone ());
//        BOOST_REQUIRE (beanWrapper->get ("postalCode").getType () != Core::NONE);
        BOOST_REQUIRE (vcast <String> (beanWrapper.get ("getPostalCode")) == "02-673");
        BOOST_REQUIRE (vcast <String> (beanWrapper.get ("getStreet")) == "katalonska");
        BOOST_REQUIRE (vcast <std::string> (beanWrapper.get ("city.getName")) == "Warszawa");
        BOOST_REQUIRE (vcast <String> (beanWrapper.get ("country.getName")) == "Polska");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testMethodPluginMethodMode)
{
        BeanWrapper beanWrapper;
        beanWrapper.addPlugin (new MethodPlugin (MethodPlugin::METHOD));
        beanWrapper.addPlugin (new PropertyRWBeanWrapperPlugin);

/*##########################################################################*/

        Country country;
        country.setName ("Polska");

        City city;
        city.setName ("Warszawa");

        Address address;
        address.setStreet ("katalonska");
        address.setPostalCode ("02-673");
        address.setCity (&city);
        address.setCountry (&country);

        beanWrapper.setWrappedObject (Core::Variant (&address));
        Variant vv = beanWrapper.getWrappedObject ();
        BOOST_REQUIRE (vv.isHandle());
        Address *pa = vcast <Address *> (vv);
        BOOST_REQUIRE (pa == &address);

//        BOOST_REQUIRE (!beanWrapper.get ("").isNone ());
        Variant ret = beanWrapper.get ("getPostalCode");
        Ptr <Handler> handler = vcast <Ptr <Handler> > (ret);
        BOOST_REQUIRE (vcast <String> (handler->invoke ()) == "02-673");

        handler = vcast <Ptr <Handler> > (beanWrapper.get ("getStreet"));
        BOOST_REQUIRE (vcast <String> (handler->invoke ()) == "katalonska");

        handler = vcast <Ptr <Handler> > (beanWrapper.get ("city.getName"));
        BOOST_REQUIRE (vcast <std::string> (handler->invoke ()) == "Warszawa");

        handler = vcast <Ptr <Handler> > (beanWrapper.get ("country.getName"));
        BOOST_REQUIRE (vcast <String> (handler->invoke ()) == "Polska");
}

/**
 * Test konkretengo przypadku, przy którym leciał segf. Zależało
 * to od kombinacji pluginów i danych wejściowych.
 */
BOOST_AUTO_TEST_CASE (testMethodPluginMethodSegF)
{
        BeanWrapper beanWrapper;
        beanWrapper.addPlugin (new PropertyRWBeanWrapperPlugin);
        beanWrapper.addPlugin (new GetPutMethodRWBeanWrapperPlugin);
        beanWrapper.addPlugin (new MethodPlugin (MethodPlugin::METHOD));

/****************************************************************************/

        VariantMap argsMap;
        Bar bar = Bar (Variant ());
        argsMap["bar"] = Core::Variant (&bar);
        Variant domain = Core::Variant (&argsMap);

        DebugContext ctx;
        bool err;
        Variant ret = beanWrapper.get (&domain, "bar.funcA", &err, &ctx);
        BOOST_REQUIRE (!err);

        // No i na tym był SegF! Podana zła nazwa funkcji.
        ret = beanWrapper.get (&domain, "funcA", &err, &ctx);
        BOOST_REQUIRE (err);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testAbstractObjects)
{
        Foo foo;
        foo.addr.setStreet ("testowy01");

        BeanWrapper *beanWrapper = BeanWrapper::create (Core::Variant (&foo));

        /*
         * Z poniższym wywołaniem był problem, ponieważ warian zawierający wskaźnik do
         * Place dawał type_info dotyczące typu Place * (typ wskaźnika), a nie typu
         * Address * (faktyczny typ obiektu wskazywanego).
         */
        BOOST_REQUIRE_EQUAL (vcast <String> (beanWrapper->get ("place.street")), "testowy01");

        // Place2 jest typu Ptr <Place> a wskazuje na obiekt typu Address.
        BOOST_REQUIRE_EQUAL (vcast <String> (beanWrapper->get ("place2.street")), "test02-66");
        delete beanWrapper;
}

/**
 * Testuje zachowanie kiedy podajemy pustą ścieżkę. Zmieniłem zachowanie się BW w takim przypadku,
 * bo okazało się, że przecież zdarza się, że chcemy ustawić mapie obiekt z pustym kluczem!
 */
BOOST_AUTO_TEST_CASE (testEmptyPath)
{
        BeanWrapper *beanWrapper = BeanWrapper::create ();

        StringMap map;
        beanWrapper->setWrappedObject (Variant (&map));
        beanWrapper->set ("", Variant ("Franusiek"));
        BOOST_REQUIRE_EQUAL (vcast <std::string> (beanWrapper->get ("")), "Franusiek");

        StringVector vec;
        beanWrapper->setWrappedObject (Variant (&vec));
        Variant wo = beanWrapper->getWrappedObject ();
        BOOST_REQUIRE_EQUAL (&vec, vcast <StringVector *> (wo));

        beanWrapper->add ("", Variant ("Franek"));
        BOOST_REQUIRE_EQUAL (vcast <std::string> (beanWrapper->get ("0")), "Franek");

        Ptr <Core::IIterator> iter = beanWrapper->iterator ("");
        std::string ret = vcast <std::string> (iter->next ());
        BOOST_REQUIRE_EQUAL (ret, "Franek");

        vec.clear ();
        beanWrapper->add ("this", Variant ("Franek i mama Asia"));

        wo = beanWrapper->getWrappedObject ();
        BOOST_REQUIRE_EQUAL (&vec, vcast <StringVector *> (wo));
        BOOST_REQUIRE_EQUAL (vec.size (), 1);
        BOOST_REQUIRE_EQUAL (vec.front (), "Franek i mama Asia");

        Ptr <Core::IIterator> iter2 = beanWrapper->iterator ("this");
        ret = vcast <std::string> (iter2->next ());
        BOOST_REQUIRE_EQUAL (ret, "Franek i mama Asia");

        delete beanWrapper;
}

BOOST_AUTO_TEST_SUITE_END ();
