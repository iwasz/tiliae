/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>

#include <iostream>
#include "core/Pointer.h"
#include "testHelpers/TestHelpers.h"

#include "container/ContainerFactory.h"
#include "container/metaStructure/model/MetaStructure.h"
#include "container/common/testHelpers/ContainerTestFactory.h"
#include <boost/make_shared.hpp>
#include "editor/testHelpers/DummyIEditor.h"
#include "beanWrapper/misc/IndexedEditor.h"
#include "container/metaStructure/model/MetaFactory.h"

/****************************************************************************/

using namespace Container;
using namespace Core;
using namespace Editor;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerTest05);

/**
 *
 */
BOOST_AUTO_TEST_CASE (testCreateCountryListWithReferenceDoubleIter)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure19 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        BOOST_CHECK_EQUAL (cont->getBeanFactoryMap ().size (), 3U);

/****************************************************************************/

        Variant v = cont->getBean ("mojaLista");
        BOOST_CHECK (!v.isNone ());

        CountryVector *list = vcast <CountryVector *> (v);

        BOOST_CHECK (list->size () == 3);

        Ptr <Country> c = list->operator[] (0);
        BOOST_CHECK (c->getName () == "Polska");

        c = list->operator[] (1);
        BOOST_CHECK (c->getName () == "Jamajka");

        c = list->operator[] (2);
        BOOST_CHECK (c->getName () == "Wolny Tybet");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testCreateOneSimpleWithCArgsAndRefWithReferenceDoubleIter)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure20 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        BOOST_CHECK_EQUAL (cont->getBeanFactoryMap ().size (), 2U);

/****************************************************************************/

        BeanFactory *bf = cont->getBeanFactory ("mojBean");
        BOOST_CHECK (bf);

        Core::VariantList const *vl = bf->getCArgs ();

        BOOST_CHECK (!vl->empty ());
        BOOST_CHECK (vl->size () == 3);
        Core::VariantList::const_iterator i = vl->begin ();

        BOOST_CHECK (vcast <String> (*i++) == "value2");
        BOOST_CHECK (vcast <std::string> (*i++) == "value3");
//        BOOST_CHECK (vcast <int> (vl->get (2)) == 6667);

/****************************************************************************/

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Bar *> (v));

        Ptr <Bar> foo = vcast <Ptr <Bar> > (v);

        BOOST_CHECK (foo->getField0 () == "value2");
        BOOST_CHECK (foo->getField1 () == "value3");

        BOOST_CHECK (foo->getCity ());
        BOOST_CHECK (foo->getCity ()->getName () == "Warszawa");
}

/**
 * Testuje tworzenie wartości <value> z typami użytkownika. Jako type="editorId" podajemy
 * ID edytora, który ma być użyty do konwersji ze stringa. W tym przypadku użyty zostanie
 * edytor DymmyJEditor, który dodaje nawiasy kwadratowe.
 */
BOOST_AUTO_TEST_CASE (testValueWithCustomEditor)
{
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();
        MetaFactory factory (metaCont->getMemoryAllocator ());

        MetaObject *child = factory.newMetaObject ();

        child->addMapField (factory.newDataKeyNewString ("field0", factory.newValueDataNewString ("value0", "bracketType")));
        child->addMapField (factory.newDataKeyNewString ("field1", factory.newValueDataNewString ("value1", "bracketType")));
        child->addMapField (factory.newDataKeyNewString ("field2", factory.newValueDataNewString ("6667", "int")));
        child->addMapField (factory.newDataKeyNewString ("field3", factory.newValueDataNewString ("123.45", "double")));
        child->addMapField (factory.newDataKeyNewString ("field4", factory.newValueDataNewString ("f", "char")));
        child->addMapField (factory.newDataKeyNewString ("field5", factory.newValueDataNewString ("true", "bool")));
        child->addMapField (factory.newDataKeyNewString ("field6", factory.newNullData ()));

        child->setId ("mojBean");
        child->setClass ("Foo");

        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        child = factory.newMetaObject ();
        //child->addField (DataKey ("name", factory.newValueDataNewString ("Warszawa", "String")));
        child->setId ("bracketType");
        child->setClass ("DummyIEditor");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Foo *> (v));

        Foo *foo = vcast <Foo *> (v);

//        std::cerr << foo->getField0 () << std::endl;
//        std::cerr << foo->getField1 () << std::endl;

        BOOST_CHECK (foo->getField0 () == "(value0)");
        BOOST_CHECK (foo->getField1 () == "(value1)");
        BOOST_CHECK (foo->getField2 () == 6667);
        BOOST_CHECK (foo->getField3 () == 123.45);
        BOOST_CHECK (foo->getField4 () == 'f');
        BOOST_CHECK (foo->getField5 () == true);
        BOOST_CHECK (!foo->getField6 ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testBeanWithCustomEditor)
{
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value0", "string")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value1", "string")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value2", "string")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value3", "string")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value4", "string")));
        child->setId ("mojBean");
        child->setClass ("string");
        child->setEditor ("editor");

        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *child2 = factory.newMetaObject ();
        child2->setId ("editor");
        child2->setClass ("ListToStringEditor");

        metaCont->add (child2);

/*--------------------------------------------------------------------------*/

        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <std::string *> (v));

        std::string *str = vcast <std::string*> (v);
        BOOST_CHECK (str);

        BOOST_CHECK_EQUAL (*str, "\"value0\",\"value1\",\"value2\",\"value3\",\"value4\"");
}

BOOST_AUTO_TEST_SUITE_END ();
