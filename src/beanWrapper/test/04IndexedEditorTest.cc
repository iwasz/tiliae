/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
#include "editor/LexicalEditor.h"
#include "beanWrapper/misc/IndexedEditor.h"
#include "core/Typedefs.h"
#include "beanWrapper/BeanWrapper.h"
#include <vector>
#include "reflection/Reflection.h"

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (BWTest04);
using namespace Wrapper;
using namespace Core;
using namespace Common;
using namespace Editor;

/****************************************************************************/

typedef std::vector <int> IntVector;
REFLECTION_COLLECTION (IntVector);

/**
 * Testuje IndexedEditor z ustawionym tylko jednym edytorem.
 * To było domyślne zachowanie zanim pozwoliłem dodawać więcej
 * niż jeden edytor wewnętrzny do indexedEditor.
 */
BOOST_AUTO_TEST_CASE (testIndexedEditor)
{
        Ptr <LexicalEditor <std::string, int> > stringEditor = boost::make_shared <LexicalEditor <std::string, int> > ();
        IndexedEditor indexed;
        indexed.setDefaultEditor (stringEditor.get ());
        indexed.setBeanWrapper (Wrapper::BeanWrapper::create ());

/*--------------------------------------------------------------------------*/

        VariantList input;

        input.push_back (Variant ("12"));
        input.push_back (Variant ("34"));
        input.push_back (Variant ("56"));
        input.push_back (Variant ("78"));
        input.push_back (Variant ("90"));
        input.push_back (Variant ("12"));
        input.push_back (Variant ("34"));

        IntVector out;
        Variant ov (&out);
        indexed.edit (Variant (&input), &ov);

        BOOST_REQUIRE_EQUAL (out[0], 12);
        BOOST_REQUIRE_EQUAL (out[1], 34);
        BOOST_REQUIRE_EQUAL (out[2], 56);
        BOOST_REQUIRE_EQUAL (out[3], 78);
        BOOST_REQUIRE_EQUAL (out[4], 90);
        BOOST_REQUIRE_EQUAL (out[5], 12);
        BOOST_REQUIRE_EQUAL (out[6], 34);

/*--------------------------------------------------------------------------*/

//        outputStr.clear ();
//        out = Core::Variant (&outputStr);
//        indexed.edit (Core::Variant (&input), &out);
//
////        for (StringList::const_iterator i = outputStr.begin (); i != outputStr.end (); i++) {
////                std::cerr << *i << "\n";
////        }
//
//        BOOST_REQUIRE_EQUAL (outputStr[0], "[Ala]");
//        BOOST_REQUIRE_EQUAL (outputStr[1], "[ma]");
//        BOOST_REQUIRE_EQUAL (outputStr[2], "[kota]");
//        BOOST_REQUIRE_EQUAL (outputStr[3], "[janek]");
//        BOOST_REQUIRE_EQUAL (outputStr[4], "[ma]");
//        BOOST_REQUIRE_EQUAL (outputStr[5], "[ochote]");
//        BOOST_REQUIRE_EQUAL (outputStr[6], "[na ale]");
}
#if 0
/**
 * Testuje IndexedEditor, ale z wieloma edytorami + do tego z domyślnym
 */
BOOST_AUTO_TEST_CASE (testIdexedEditorMulti)
{
        IndexedEditor indexed;

        Ptr <EditorVector> vectEd (new EditorVector);
        vectEd->push_back (Ptr <IEditor> (new DummyJEditor ("[", "]"))); //0
        vectEd->push_back (Ptr <IEditor> (new DummyJEditor ("]", "["))); //1
        vectEd->push_back (Ptr <IEditor> (new DummyJEditor ("{", "}"))); //2
        vectEd->push_back (Ptr <IEditor> (new DummyJEditor ("(", ")"))); //3
        vectEd->push_back (Ptr <IEditor> (new DummyJEditor ("<", ">"))); //4
        vectEd->push_back (Ptr <IEditor> (new DummyJEditor ("A", "B"))); //5
        vectEd->push_back (Ptr <IEditor> (new DummyJEditor ("a", "b"))); //6

        indexed.setEditors (vectEd);
        indexed.setBeanWrapper (Wrapper::BeanWrapper::create ());
        indexed.setDefaultEditor (Ptr <IEditor> (new DummyJEditor ("*", "*")));
        indexed.setEditor (8, Ptr <IEditor> (new DummyJEditor ("+", "+")));

/*--------------------------------------------------------------------------*/

        StringList input;

        input.push_back ("Ala");
        input.push_back ("ma");
        input.push_back ("kota");
        input.push_back ("janek");
        input.push_back ("ma");
        input.push_back ("ochote");
        input.push_back ("na ale");

        input.push_back ("1");
        input.push_back ("2");
        input.push_back ("3");

        StringVector outputStr (10);

/*--------------------------------------------------------------------------*/

        Variant out = Core::Variant (&outputStr);
        indexed.edit (Core::Variant (&input), &out);

#if 0
        for (StringList::const_iterator i = outputStr.begin (); i != outputStr.end (); i++) {
                std::cerr << *i << "\n";
        }
#endif

        BOOST_REQUIRE_EQUAL (outputStr[0], "[Ala]");
        BOOST_REQUIRE_EQUAL (outputStr[1], "]ma[");
        BOOST_REQUIRE_EQUAL (outputStr[2], "{kota}");
        BOOST_REQUIRE_EQUAL (outputStr[3], "(janek)");
        BOOST_REQUIRE_EQUAL (outputStr[4], "<ma>");
        BOOST_REQUIRE_EQUAL (outputStr[5], "AochoteB");
        BOOST_REQUIRE_EQUAL (outputStr[6], "ana aleb");
        BOOST_REQUIRE_EQUAL (outputStr[7], "*1*");
        BOOST_REQUIRE_EQUAL (outputStr[8], "+2+");
        BOOST_REQUIRE_EQUAL (outputStr[9], "*3*");

/*--------------------------------------------------------------------------*/

        out = Core::Variant (&outputStr);
        indexed.edit (Core::Variant (&input), &out);

        BOOST_REQUIRE_EQUAL (outputStr[0], "[Ala]");
        BOOST_REQUIRE_EQUAL (outputStr[1], "]ma[");
        BOOST_REQUIRE_EQUAL (outputStr[2], "{kota}");
        BOOST_REQUIRE_EQUAL (outputStr[3], "(janek)");
        BOOST_REQUIRE_EQUAL (outputStr[4], "<ma>");
        BOOST_REQUIRE_EQUAL (outputStr[5], "AochoteB");
        BOOST_REQUIRE_EQUAL (outputStr[6], "ana aleb");
        BOOST_REQUIRE_EQUAL (outputStr[7], "*1*");
        BOOST_REQUIRE_EQUAL (outputStr[8], "+2+");
        BOOST_REQUIRE_EQUAL (outputStr[9], "*3*");
}
#endif

BOOST_AUTO_TEST_SUITE_END ();
