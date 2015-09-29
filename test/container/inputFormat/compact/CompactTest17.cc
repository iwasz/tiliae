/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <iostream>
#include "core/Pointer.h"
#include "testHelpers/TestHelpers.h"
#include "container/ContainerFactory.h"
#include "container/inputFormat/compact/CompactMetaService.h"
#include "Conf.h"
#include "container/metaStructure/model/MetaContainer.h"
#include "container/ContainerFactory.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (CompactXmlTest17);

Core::Variant toType (std::string const &s)
{
        Type t;

        if (s == "TYPE1") {
                t = TYPE1;
        }
        else if (s == "TYPE2") {
                t = TYPE2;
        }
        else if (s == "TYPE3") {
                t = TYPE3;
        }
        else {
                throw 1;
        }

        return Core::Variant (static_cast <unsigned int> (t));
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test081TEnum)
{
        Ptr <MetaContainer> metaContainer = CompactMetaService::parseFile (PATH + "081-enum.xml");
        Ptr <BeanFactoryContainer> container = ContainerFactory::create (metaContainer, true);
        container->addConversion (typeid (Type), toType);
        ContainerFactory::init (container.get (), metaContainer.get ());

        Dummy3 *test1 = vcast <Dummy3 *> (container->getBean ("test1"));
        BOOST_REQUIRE_EQUAL (test1->field1, TYPE1);
        BOOST_REQUIRE_EQUAL (test1->field2, TYPE2);
        BOOST_REQUIRE_EQUAL (test1->field3, TYPE3);

        Dummy3 *test2 = vcast <Dummy3 *> (container->getBean ("test2"));
        BOOST_REQUIRE_EQUAL (test2->field1, TYPE3);
        BOOST_REQUIRE_EQUAL (test2->field2, TYPE2);
        BOOST_REQUIRE_EQUAL (test2->field3, TYPE1);

        Dummy3 *test3 = vcast <Dummy3 *> (container->getBean ("test3"));
        BOOST_REQUIRE_EQUAL (test3->field1, TYPE3);
        BOOST_REQUIRE_EQUAL (test3->field2, TYPE3);
        BOOST_REQUIRE_EQUAL (test3->field3, TYPE3);
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test082ParentWithInner)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "082-parent-with-inner.xml"));
        Foo *foo1 = vcast <Foo *> (cont->getBean ("childBean1"));
        Foo *foo2 = vcast <Foo *> (cont->getBean ("childBean2"));

        BOOST_REQUIRE_NE (foo1->getCity (), foo2->getCity ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (test083PropAlias)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "083-prop-alias.xml"));
        Foo *foo1 = vcast <Foo *> (cont->getBean ("childBean1"));
        Foo *foo2 = vcast <Foo *> (cont->getBean ("childBean2"));

        BOOST_REQUIRE_EQUAL (foo1->getCity ()->getName (), "Częstochowa");
        BOOST_REQUIRE_EQUAL (foo2->getCity ()->getName (), "Szczebrzeszyn");
}

/**
 * Myślałem, że to nie będzie działać, ale jednak działa :
 *
 *  <A id="a">
 *   <A1 set-as="a1" id="a1" />
 *   <ref set-as="a2" bean="@a1" />
 *  </A>
 *
 *  <a id="nowyA"/>
 *
 * TO JEST BŁĘDNE ROZUMOWANIE:
 * Powyżej beany klasy A mają pola a1 i a2. W obydwu instancjach a1 powinno być równe a2. Jedak z powodu błędu w drugiej instancji a2 bedzie równe a1 i a2 z
 * beana a. Wynika to stąd, że te wewnętrzne dodają do additionalSingletons (vector).
 */
BOOST_AUTO_TEST_CASE (test084InerSingletonInherit)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "084-inner-singleton.xml"));

        Bar *bar1= vcast <Bar *> (cont->getBean ("mojBean"));
        BOOST_REQUIRE_EQUAL (bar1->getCity4 (), bar1->getCity5 ());
        BOOST_REQUIRE_EQUAL (bar1->getCity4 ()->getName (), "Warszawa");

        Bar *bar2= vcast <Bar *> (cont->getBean ("childBean1"));
        BOOST_REQUIRE_EQUAL (bar2->getCity4 (), bar2->getCity5 ());
        BOOST_REQUIRE_NE (bar1->getCity4 (), bar2->getCity4 ());
        BOOST_REQUIRE_EQUAL (bar2->getCity4 ()->getName (), "Kraków");

        Bar *bar3= vcast <Bar *> (cont->getBean ("childBean2"));
        BOOST_REQUIRE_EQUAL (bar3->getCity4 (), bar3->getCity5 ());
        BOOST_REQUIRE_NE (bar1->getCity4 (), bar3->getCity4 ());
        BOOST_REQUIRE_EQUAL (bar3->getCity4 ()->getName (), "Poznań");
}

/**
 * Test na błąd, który pokazał się w Bajce - kiedy miałem zlinkowane kontenery, jeden z singletonów instanconował się
 * 2 razy.
 */
BOOST_AUTO_TEST_CASE (test085LinkedContainers)
{
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "085-linked-01.xml"), true);
        Bar *bar1 = vcast <Bar *> (cont->getBean ("mojBean"));

        Ptr <BeanFactoryContainer> cont2 = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "085-linked-02.xml"), false, cont.get ());
        VariantList *list = vcast <VariantList *> (cont2->getBean ("lista"));
        Bar *bar2 = vcast <Bar *> (list->front ());

        BOOST_REQUIRE_EQUAL (bar1, bar2);
}

BOOST_AUTO_TEST_CASE (test086GlobalInitMethod)
{
/*------Kontener------------------------------------------------------------*/

        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "086-global-init-method.xml"));

/*------Testy---------------------------------------------------------------*/

        Variant v = cont->getBean ("city");
        BOOST_CHECK (!v.isNone ());

        City *c = vcast <City *> (v);
        BOOST_CHECK_EQUAL (c->getName (), "Warszawa_INIT");
}

BOOST_AUTO_TEST_CASE (test087GlobalIdMethod)
{
/*------Kontener------------------------------------------------------------*/

        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "087-global-id-method.xml"));

/*------Testy---------------------------------------------------------------*/

        Variant v = cont->getBean ("Warszawa");
        BOOST_CHECK (!v.isNone ());

        City *c = vcast <City *> (v);
        BOOST_CHECK_EQUAL (c->getName (), "Warszawa");

        v = cont->getBean ("Polska");
        BOOST_CHECK (!v.isNone ());

        Country *ct = vcast <Country *> (v);
        BOOST_CHECK_EQUAL (ct->getName (), "Polska");

}

/**
 * <beans init-method> działa na wszystkie pliki
 */
BOOST_AUTO_TEST_CASE (test088GlobalInitMethodIncluded)
{
/*------Kontener------------------------------------------------------------*/

        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "088-import-global-init-method.xml"));

/*------Testy---------------------------------------------------------------*/

        Variant v = cont->getBean ("city1");
        BOOST_CHECK (!v.isNone ());

        City *c = vcast <City *> (v);
        BOOST_CHECK_EQUAL (c->getName (), "Warszawa_INIT");

        v = cont->getBean ("city2");
        BOOST_CHECK (!v.isNone ());

        c = vcast <City *> (v);
        BOOST_CHECK_EQUAL (c->getName (), "Warszawa_INIT");
}

BOOST_AUTO_TEST_SUITE_END ();
