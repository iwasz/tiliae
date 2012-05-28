/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/make_shared.hpp>
#include <boost/make_shared.hpp>
#include "../TypeEditor.h"
#include "../LexicalEditor.h"
#include "../StringConstructorEditor.h"
#include "../../testHelpers/City.h"
#include "../StreamEditor.h"
#include "../StringFactoryMethodEditor.h"

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (EditorTest02);
using namespace Core;
using namespace Editor;

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testJEditor)
{
        Ptr <TypeEditor> editor = boost::make_shared <TypeEditor> ();

        editor->addType (TypeEditor::Type (typeid (std::string), typeid (int), boost::make_shared <LexicalEditor <std::string, int> > ()));
        editor->addType (TypeEditor::Type (typeid (int), typeid (std::string), boost::make_shared <LexicalEditor <int, std::string> > ()));
        editor->addType (TypeEditor::Type (typeid (Core::String), typeid (std::string), boost::make_shared <LexicalEditor <Core::String, std::string> > ()));
        editor->addType (TypeEditor::Type (typeid (std::string), typeid (Core::String), boost::make_shared <LexicalEditor <std::string, Core::String> > ()));

/*--------------------------------------------------------------------------*/

        Variant out ((int)0);
        editor->convert (Variant (std::string ("123")), &out);
        BOOST_REQUIRE_EQUAL (vcast <int> (out), 123);

        out = Variant (Core::String (""));
        editor->convert (Variant (std::string ("123")), &out);
        BOOST_REQUIRE_EQUAL (vcast <Core::String> (out), "123");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testStringConstruct)
{
        Ptr <StringConstructorEditor> editor = boost::make_shared <StringConstructorEditor> ();

///*--------------------------------------------------------------------------*/

        Ptr <City> city;
        Variant out (city);

        Core::DebugContext ctx;
        bool success = editor->convert (Variant ("Warszawa"), &out, &ctx);
        std::cerr << ctx.getMessage () << std::endl;

        city = vcast <Ptr <City> > (out);
        BOOST_REQUIRE (city);
        BOOST_REQUIRE_EQUAL (city->getName (), "Warszawa");
        BOOST_REQUIRE_EQUAL (success, true);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testStreamEditor)
{
        Ptr <StreamEditor<std::string, unsigned int> > editor = boost::make_shared <StreamEditor<std::string, unsigned int> > ();

        Variant out;
        editor->convert (Variant ("123"), &out);
        BOOST_REQUIRE_EQUAL (vcast <unsigned int> (out), 123u);

        editor->convert (Variant ("0xabc"), &out);
        BOOST_REQUIRE_EQUAL (vcast <unsigned int> (out), 2748u);

        editor->convert (Variant ("0xFF"), &out);
        BOOST_REQUIRE_EQUAL (vcast <unsigned int> (out), 255u);
}

/****************************************************************************/

static Core::Variant convertStringToInt (std::string const &input)
{
        return Core::Variant (boost::lexical_cast <int> (input));
}

struct City2 {
        City2 (std::string const &n) : name (n) {}
        std::string name;
};

static Core::Variant convertStringToCity (std::string const &input)
{
        return Core::Variant (boost::make_shared <City2> (input));
}

BOOST_AUTO_TEST_CASE (testConversionFunctionEditor)
{
        StringFactoryMethodEditor editor;
        editor.addConversion (typeid (int), convertStringToInt);
        editor.addConversion (typeid (City2), convertStringToCity);

        {
                Ptr <City2> city;
                Variant out (city);
                editor.convert (Variant ("Warszawa"), &out);
                BOOST_REQUIRE_EQUAL (vcast <City2 *> (out)->name, "Warszawa");
        }

        {
                int i;
                Variant out (i);
                editor.convert (Variant ("12345"), &out);
                BOOST_REQUIRE_EQUAL (vcast <int> (out), 12345);
        }
}

BOOST_AUTO_TEST_SUITE_END ();
