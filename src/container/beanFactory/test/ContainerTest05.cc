/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <Pointer.h>
#include <TestHelpers.h>

#include "ContainerFactory.h"
#include "metaStructure/model/MetaStructure.h"
#include "common/testHelpers/ContainerTestFactory.h"
#include <boost/make_shared.hpp>
#include "../../../editor/testHelpers/DummyIEditor.h"
#include "../../../beanWrapper/misc/IndexedEditor.h"

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
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createContainer (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ());
        BOOST_CHECK (cont->getBeanFactoryMap ()->size () == 4);

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
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createContainer (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ());
        BOOST_CHECK (cont->getBeanFactoryMap ()->size () == 2);

/****************************************************************************/

        Ptr <BeanFactory> bf = cont->getBeanFactory ("mojBean");
        BOOST_CHECK (bf);

        Core::VariantList const *vl = bf->getCArgs ();

        BOOST_CHECK (!vl->empty ());
        BOOST_CHECK (vl->size () == 3);
        Core::VariantList::const_iterator i = vl->begin ();

        BOOST_CHECK (vcast <String> (*i++) == "value2");
        BOOST_CHECK (vcast <std::string> (*i++) == "value3");
//        BOOST_CHECK (vcast <int> (vl->get (2)) == 6667);

        IEditor *cargsEditor = bf->getCArgsEditor ();
        BOOST_CHECK (cargsEditor);
        Editor::IndexedEditor *idxEd = dynamic_cast <Editor::IndexedEditor *> (cargsEditor);
        BOOST_CHECK (idxEd);
        BOOST_CHECK (idxEd->getEditor (2));

/****************************************************************************/

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Bar *> (v));

        Bar *foo = vcast <Bar *> (v);

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

        MappedMeta *child = new MappedMeta ();

        child->addField (DataKey ("field0", new ValueData ("value0", "bracketType")));
        child->addField (DataKey ("field1", new ValueData ("value1", "bracketType")));
        child->addField (DataKey ("field2", new ValueData ("6667", "int")));
        child->addField (DataKey ("field3", new ValueData ("123.45", "double")));
        child->addField (DataKey ("field4", new ValueData ("f", "char")));
        child->addField (DataKey ("field5", new ValueData ("true", "bool")));
        child->addField (DataKey ("field6", new NullData ()));

        child->setId ("mojBean");
        child->setClass ("Foo");

        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        child = new MappedMeta ();
        //child->addField (DataKey ("name", new ValueData ("Warszawa", "String")));
        child->setId ("bracketType");
        child->setClass ("DummyIEditor");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        Ptr <BeanFactoryContainer> cont = ContainerFactory::createContainer (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ());
        BOOST_CHECK (cont->getBeanFactoryMap ()->size () == 2);

/*--------------------------------------------------------------------------*/

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

/*--------------------------------------------------------------------------*/

        IndexedMeta *child = new IndexedMeta ();

        child->addField (new ValueData ("value0", "string"));
        child->addField (new ValueData ("value1", "string"));
        child->addField (new ValueData ("value2", "string"));
        child->addField (new ValueData ("value3", "string"));
        child->addField (new ValueData ("value4", "string"));
        child->setId ("mojBean");
        child->setClass ("string");
        child->setEditor ("editor");

        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MappedMeta *child2 = new MappedMeta ();
        child2->setId ("editor");
        child2->setClass ("ListToStringEditor");

        metaCont->add (child2);

/*--------------------------------------------------------------------------*/

        Ptr <BeanFactoryContainer> cont = ContainerFactory::createContainer (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ());
        BOOST_CHECK (cont->getBeanFactoryMap ()->size () == 2);

/*--------------------------------------------------------------------------*/

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <std::string *> (v));

        std::string *str = vcast <std::string*> (v);
        BOOST_CHECK (str);

        BOOST_CHECK_EQUAL (*str, "\"value0\",\"value1\",\"value2\",\"value3\",\"value4\"");
}

BOOST_AUTO_TEST_SUITE_END ();
