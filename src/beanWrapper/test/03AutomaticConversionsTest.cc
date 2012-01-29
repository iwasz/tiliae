/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../beanWrapper/BeanWrapper.h"
#include "../../core/Pointer.h"
#include "../../testHelpers/Country.h"
#include "../../testHelpers/City.h"
#include "../../testHelpers/Address.h"
#include "../../core/variant/Variant.h"
#include "../plugins/PropertyRWBeanWrapperPlugin.h"
#include "../../core/DebugContext.h"
#include "../../editor/LexicalEditor.h"
#include "../../editor/TypeEditor.h"
#include "../../editor/NoopEditor.h"
#include "../../testHelpers/Foo.h"
#include "../../editor/ChainEditor.h"
#include "../../editor/StringConstructorEditor.h"

using Editor::ChainEditor;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (BWTest03);
using namespace Wrapper;
using namespace Core;
using namespace Common;
using namespace Editor;

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testSimple)
{
        Ptr <BeanWrapper> bw = BeanWrapper::create ();
        Ptr <IEditor> ed = boost::make_shared <LexicalEditor <int, Core::String> > ();
        bw->setEditor (ed);

        Country country;

        bw->setWrappedObject (Variant (&country));

//        bw->set ("name", Variant (Core::String ("Warszawa")));
        bw->set ("name", Variant (int (123)));

        BOOST_REQUIRE_EQUAL (country.getName (), "123");
}

/**
 * Setter + bardziej zaawansowany edytor.
 */
BOOST_AUTO_TEST_CASE (testComplex_Object)
{
        Ptr <BeanWrapper> bw = BeanWrapper::create ();

        /*--------------------------------------------------------------------------*/

        Ptr <Editor::TypeEditor> editor = boost::make_shared <Editor::TypeEditor> ();
        Ptr <Editor::IEditor> noop = Editor::NoopEditor::create ();
        editor->setEqType (noop);
        editor->setNullType (noop);

        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (int), boost::make_shared <Editor::LexicalEditor <std::string, int> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (double), boost::make_shared <Editor::LexicalEditor <std::string, double> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (char), boost::make_shared <Editor::LexicalEditor <std::string, char> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (bool), boost::make_shared <Editor::LexicalEditor <std::string, bool> > ()));

        // Core::String <-> std::string
        editor->addType (Editor::TypeEditor::Type (typeid (Core::String), typeid (std::string), boost::make_shared <Editor::LexicalEditor <Core::String, std::string> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (Core::String), boost::make_shared <Editor::LexicalEditor <std::string, Core::String> > ()));

        // StringCon.
        Ptr <StringConstructorEditor> strCon = boost::make_shared <StringConstructorEditor> ();

        Ptr <ChainEditor> chain = boost::make_shared <ChainEditor> ();
        chain->addEditor (editor);
        chain->addEditor (strCon);

        /*--------------------------------------------------------------------------*/

        bw->setEditor (chain);

        Foo foo;
        bw->setWrappedObject (Variant (&foo));

        bw->set ("field0", Variant ("test1"));
        bw->set ("field1", Variant ("test2"));
        bw->set ("field2", Variant ("123"));
        bw->set ("field3", Variant ("12.34"));
        bw->set ("field4", Variant ("a"));
        bw->set ("field5", Variant ("yes"));
        bw->set ("city", Variant ("Warszawa"));

        BOOST_REQUIRE_EQUAL (foo.getField0 (), "test1");
        BOOST_REQUIRE_EQUAL (foo.getField1 (), "test2");
        BOOST_REQUIRE_EQUAL (foo.getField2 (), 123);
        BOOST_REQUIRE_EQUAL (foo.getField3 (), 12.34);
        BOOST_REQUIRE_EQUAL (foo.getField4 (), 'a');
        BOOST_REQUIRE_EQUAL (foo.getField5 (), true);
        BOOST_REQUIRE (foo.getCity ());
        BOOST_REQUIRE_EQUAL (foo.getCity ()->getName (), "Warszawa");
}

/**
 * Zawansowane edytowaine mapy.
 */
BOOST_AUTO_TEST_CASE (testComplex_Map)
{
        Ptr <BeanWrapper> bw = BeanWrapper::create ();

        /*--------------------------------------------------------------------------*/

        Ptr <Editor::TypeEditor> editor = boost::make_shared <Editor::TypeEditor> ();
        Ptr <Editor::IEditor> noop = Editor::NoopEditor::create ();
        editor->setEqType (noop);
        editor->setNullType (noop);

        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (int), boost::make_shared <Editor::LexicalEditor <std::string, int> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (double), boost::make_shared <Editor::LexicalEditor <std::string, double> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (char), boost::make_shared <Editor::LexicalEditor <std::string, char> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (bool), boost::make_shared <Editor::LexicalEditor <std::string, bool> > ()));

        // Core::String <-> std::string
        editor->addType (Editor::TypeEditor::Type (typeid (Core::String), typeid (std::string), boost::make_shared <Editor::LexicalEditor <Core::String, std::string> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (Core::String), boost::make_shared <Editor::LexicalEditor <std::string, Core::String> > ()));

        // StringCon.
        Ptr <StringConstructorEditor> strCon = boost::make_shared <StringConstructorEditor> ();

        Ptr <ChainEditor> chain = boost::make_shared <ChainEditor> ();
        chain->addEditor (editor);
        chain->addEditor (strCon);

        /*--------------------------------------------------------------------------*/

        bw->setEditor (chain);

        CityMap cityMap;
        bw->setWrappedObject (Variant (&cityMap));

        bw->set ("city01", Variant ("Warszawa"));
        bw->set ("city02", Variant ("Kraków"));
        bw->set ("city03", Variant ("Poznań"));

        BOOST_REQUIRE_EQUAL (cityMap.size (), 3);
        BOOST_REQUIRE_EQUAL (cityMap["city01"]->getName (), "Warszawa");
        BOOST_REQUIRE_EQUAL (cityMap["city02"]->getName (), "Kraków");
        BOOST_REQUIRE_EQUAL (cityMap["city03"]->getName (), "Poznań");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testListWithBeanWrapper)
{
        Ptr <IBeanWrapper> bw = BeanWrapper::create ();
        StringVector vector;

        Variant v (&vector);
        bw->add (&v, "", Variant ("iwasz"));
        bw->add (&v, "", Variant ("asia"));
        bw->add (&v, "", Variant ("gadzio"));
        bw->add (&v, "", Variant ("tmarc"));

        BOOST_REQUIRE_EQUAL (vector.size (), 4);
        BOOST_REQUIRE_EQUAL (vector[0], "iwasz");
        BOOST_REQUIRE_EQUAL (vector[1], "asia");
        BOOST_REQUIRE_EQUAL (vector[2], "gadzio");
        BOOST_REQUIRE_EQUAL (vector[3], "tmarc");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testComplex_Vector)
{
        Ptr <BeanWrapper> bw = BeanWrapper::create ();

        /*--------------------------------------------------------------------------*/

        Ptr <Editor::TypeEditor> editor = boost::make_shared <Editor::TypeEditor> ();
        Ptr <Editor::IEditor> noop = Editor::NoopEditor::create ();
        editor->setEqType (noop);
        editor->setNullType (noop);

        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (int), boost::make_shared <Editor::LexicalEditor <std::string, int> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (double), boost::make_shared <Editor::LexicalEditor <std::string, double> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (char), boost::make_shared <Editor::LexicalEditor <std::string, char> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (bool), boost::make_shared <Editor::LexicalEditor <std::string, bool> > ()));

        // Core::String <-> std::string
        editor->addType (Editor::TypeEditor::Type (typeid (Core::String), typeid (std::string), boost::make_shared <Editor::LexicalEditor <Core::String, std::string> > ()));
        editor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (Core::String), boost::make_shared <Editor::LexicalEditor <std::string, Core::String> > ()));

        // StringCon.
        Ptr <StringConstructorEditor> strCon = boost::make_shared <StringConstructorEditor> ();

        Ptr <ChainEditor> chain = boost::make_shared <ChainEditor> ();
        chain->addEditor (editor);
        chain->addEditor (strCon);

        /*--------------------------------------------------------------------------*/

        bw->setEditor (chain);

        CityVector cityVector;
        bw->setWrappedObject (Variant (&cityVector));

        bw->add ("", Variant ("Warszawa"));
        bw->add ("", Variant ("Kraków"));
        bw->add ("", Variant ("Poznań"));

        BOOST_REQUIRE_EQUAL (cityVector.size (), 3);
        BOOST_REQUIRE_EQUAL (cityVector[0]->getName (), "Warszawa");
        BOOST_REQUIRE_EQUAL (cityVector[1]->getName (), "Kraków");
        BOOST_REQUIRE_EQUAL (cityVector[2]->getName (), "Poznań");
}

BOOST_AUTO_TEST_SUITE_END ();
