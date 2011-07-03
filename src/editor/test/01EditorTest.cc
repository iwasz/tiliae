/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#define BOOST_TEST_MODULE EditorTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/make_shared.hpp>
#include <list>
#include <iostream>
#include <algorithm>
#include "../../testHelpers/City.h"
#include "../../core/variant/Variant.h"
#include "../../core/string/String.h"
#include "../IEditor.h"
#include "../testHelpers/DummyJEditor.h"
#include "../testHelpers/DummyIEditor.h"
#include "../../core/variant/Cast.h"
#include "../../factory/testHelpers/MegaTon.h"
#include "../testHelpers/StringToMegaTonEditor.h"
#include "../../core/Pointer.h"
#include "../../factory/testHelpers/MegaTonFactory.h"
#include "../../factory/SingletonFactory.h"
#include "../FactoryEditor.h"
#include "../../core/Typedefs.h"
#include "../../testHelpers/Address.h"
#include "../../testHelpers/City.h"
#include "../../testHelpers/Country.h"
#include "../NoopEditor.h"
#include "../LexicalEditor.h"

using Core::Variant;
using Core::String;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (EditorTest01);
using namespace Core;
//using namespace Wrapper;
using namespace Factory;
using namespace Editor;

/****************************************************************************/

City *fire ()
{
        return NULL;
}

/**
 * To sa takie notatki - co i jak dziala i dla czego wolno tak,
 * a nie wolno inaczej. To nie jest test, który ma się wykonać,
 * a tylko demonstracja API.
 */
#if 0
BOOST_AUTO_TEST_CASE (testDemonstrateEditors)
{
//        Core::Variant (fire ());

        /*
         * Wariant wejsciowy jest dowolny. Moze byc uchwytem, moze
         * byc wartością. Jedyne wymaganie, to !isNone (). isNull ()
         * tez moze byc, jezeli ma to sens (mozna sobie wyobrazic
         * edytor, ktory gdy input.isNull () == true, to podejmuje
         * jakas akcje.
         */
        Variant in = Core::Variant (String ("kupa"));

        // Załóżmy, ze coś tutaj jest w tym edytorze.
        IEditor *e = NULL;


        /*
         * Pusty obiekt wyjściowy. Edytor musi stworzyć nowy obiekt
         * i przypisać go wariantowi out1.
         */
        Variant out1;
        e->convert (in, &out1);
//        {
//                String newString = "test";
//                *out = Core::Variant (newString);
//        }

        /*
         * Obiekt wyjściowy jako wariant-wartość.
         */
        Variant out2 = Core::Variant (String ());
        e->convert (in, &out1);
//        {
//                String *extString = vcast <String *> (*out1);
//                *extString = "test";
//        }

        /*
         * Obiekt wyjściowy jako handle.
         */
        String extStr; // Ulegnie zmianie
        Variant out3 = Core::Variant (&extStr);
        e->convert (in, &out1);
//        {
//                String *extString = vcast <String *> (*out1);
//                *extString = "test";
//        }
}
#endif

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testJEditor)
{
        String in = "moja żona";
        String out;
        Variant vOut = Core::Variant (&out);

        DummyJEditor editor;
        editor.edit (Core::Variant (in), &vOut);

//        std::cerr << vOut << ", --->" << out << std::endl;

        BOOST_REQUIRE_EQUAL (out, "[moja żona]");
}

/****************************************************************************/

/**
 *
 */
BOOST_AUTO_TEST_CASE (testIEditor)
{
        std::string in = "janek, ala i zenek";
        Variant out;

        DummyIEditor editor;
        editor.convert (Core::Variant (in), &out);

        BOOST_REQUIRE (vcast <std::string> (out) == "(janek, ala i zenek)");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testMegaTonEditor)
{
        String in = "alibaba, baba ali";
        MegaTon out;
        Variant vOut = Core::Variant (&out);

        StringToMegatonEditor editor;
        editor.edit (Core::Variant (in), &vOut);

        BOOST_REQUIRE (out.getHeavyProperty () == "alibaba, baba ali");
}

/**
 * testuje FactoryEditor.
 */
BOOST_AUTO_TEST_CASE (testMegaTonFactoryEditor)
{
        String in = "man with a movie camera";
        Variant out;
        BOOST_REQUIRE (!ccast <MegaTon *> (out));

        Ptr <StringToMegatonEditor> strToMega (new StringToMegatonEditor);
        Ptr <MegaTonFactory> megaFact (new MegaTonFactory);

        FactoryEditor editor;
        editor.setEditor (strToMega);
        editor.setFactory (megaFact);

        editor.convert (Core::Variant (in), &out);

        BOOST_REQUIRE (ccast <MegaTon *> (out));
        BOOST_REQUIRE (vcast <MegaTon *> (out)->getHeavyProperty () == "man with a movie camera");
}

/**
 * SingletonFactoryEditor.
 */
BOOST_AUTO_TEST_CASE (testMegaTonSingletonFactoryEditor)
{
        String in = "fantomas";
        Variant out;
        BOOST_REQUIRE (!ccast <MegaTon *> (out));

        Ptr <StringToMegatonEditor> strToMega (new StringToMegatonEditor);
        Ptr <MegaTonFactory> megaFact (new MegaTonFactory);
        Ptr <SingletonFactory> sfct (new SingletonFactory);
        sfct->setFactory (megaFact);

        FactoryEditor editor;
        editor.setEditor (strToMega);
        editor.setFactory (sfct);

        editor.convert (Core::Variant (in), &out);

        BOOST_REQUIRE (ccast <MegaTon *> (out));
        BOOST_REQUIRE (vcast <MegaTon *> (out)->getHeavyProperty () == "fantomas");

        Variant out2;
        BOOST_REQUIRE (!ccast <MegaTon *> (out2));

        editor.convert (Core::Variant (String ("ttteeest")), &out2);

        BOOST_REQUIRE (ccast <MegaTon *> (out2));
        BOOST_REQUIRE (vcast <MegaTon *> (out)->getHeavyProperty () == "ttteeest");
        BOOST_REQUIRE (vcast <MegaTon *> (out2)->getHeavyProperty () == "ttteeest");
        BOOST_REQUIRE (vcast <MegaTon *> (out) == vcast <MegaTon *> (out2));
}

#if 0
/**
 *
 */
BOOST_AUTO_TEST_CASE (testMappingEditorBasic)
{

/*------Edytor miasta-------------------------------------------------------*/

        City c1;
        c1.setName ("Warszawa");
        City c2;

        // Zamienia napis na [napis]
        DummyJEditor braces1;

        Mapping mp1;

        SimpleRule sr1 ("name", "name", &braces1);
        RuleList ruleList;
        ruleList.push_back (&sr1);
        mp1.setRuleList (&ruleList);

        Ptr <MappedEditor> me1 (new MappedEditor);
        me1->setMapping (&mp1);

        BeanWrapper beanWrapper1a;
        BeanWrapperPluginList pluginList1;
        PropertyRWBeanWrapperPlugin getterSetterPlugin1;
        pluginList1.push_back (&getterSetterPlugin1);
        beanWrapper1a.setPluginList (&pluginList1);

        BeanWrapper beanWrapper1b;
        beanWrapper1b.setPluginList (&pluginList1);

        me1->setIn (&beanWrapper1a);
        me1->setOut (&beanWrapper1b);

        Variant out1 = Core::Variant (&c2);
        me1->edit (Core::Variant (c1), &out1);

        BOOST_REQUIRE (c2.getName () == "[Warszawa]");

        // A teraz wrapujemy me1 do FactoryEditor. Jesli miasto nie istnieje, to sie utworzy.
        Ptr <CityFactory> cityFactory (new CityFactory);

        FactoryEditor cityFactoryEditor;
        cityFactoryEditor.setEditor (me1);
        cityFactoryEditor.setFactory (cityFactory);

        Variant out2;
        cityFactoryEditor.convert (Core::Variant (c1), &out2);
        City *ret = vcast <City *> (out2);
        BOOST_REQUIRE (ret->getName () == "[Warszawa]");

// SillyFactory nie zadziala, bo potrzebny jest wskaznik do obiektu, a Silly zwraca tylko wartosci! Program bedzie sie wywalal.
//        SillyFactory cityFactory2;
//        cityFactory2.setOriginal (Core::Variant (City ()));
//        cityFactoryEditor.setEditor (&me1);
//        cityFactoryEditor.setFactory (&cityFactory2);
//
//        Variant out3;
//        cityFactoryEditor.convert (Core::Variant (c1), &out3);
//        ret = vcast <City *> (out3);
//
//        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : >" << ret->getName () << "<" << std::endl;
//        BOOST_REQUIRE (ret->getName () == "[Warszawa]");

/*------Edytor adresu-------------------------------------------------------*/
#if 1
        // Obiekt we.
        Address a1;
        a1.setPostalCode ("02-763");
        a1.setStreet ("Sesame");
        a1.setCity (&c1);

        // Obiekt wy.
        Address a2;
//        City c3;
//        a2.setCity (&c3);

        // Zamienia napis na [napis]
        DummyJEditor braces;

        Mapping mp;

        SimpleRule sr2 ("postalCode", "postalCode", &braces);
        SimpleRule sr3 ("street", "street", &braces);
        SimpleRule sr4 ("city", "city", &cityFactoryEditor);

        RuleList ruleList2;
        ruleList2.push_back (&sr2);
        ruleList2.push_back (&sr3);
        ruleList2.push_back (&sr4);
        mp.setRuleList (&ruleList2);

        MappedEditor me;
        me.setMapping (&mp);

        BeanWrapper beanWrapper;
        BeanWrapperPluginList pluginList;
        PropertyRWBeanWrapperPlugin getterSetterPlugin;
        pluginList.push_back (&getterSetterPlugin);
        beanWrapper.setPluginList (&pluginList);

        BeanWrapper beanWrapper2;
        beanWrapper2.setPluginList (&pluginList);

        me.setIn (&beanWrapper);
        me.setOut (&beanWrapper2);

/*--------------------------------------------------------------------------*/

        Variant out = Core::Variant (&a2);
        me.edit (Core::Variant (a1), &out);

        BOOST_REQUIRE (a2.getStreet () == "[Sesame]");
        BOOST_REQUIRE (a2.getPostalCode () == "[02-763]");
        BOOST_REQUIRE (a2.getCity ());

        //std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << a2.getCity ()->getName () << std::endl;

        BOOST_REQUIRE (a2.getCity ()->getName () == "[Warszawa]");
#endif
}
#endif

#if 0
/**
 * To jest test majacy pokazac jak skonwertowac obiekt
 * o jednej strukturze (Mapa) do obiektu o innej strukturze
 * (lista). Przy okazji odpowiadajace sobie elementy z
 * Mapy i listy maja inne typy. Na wynikoweuj liscie
 * Wszystko ma typ String.
 */
BOOST_AUTO_TEST_CASE (testConvertMapToList)
{
        // Obiekt wejsciowy
        VariantMap input;
        input.set ("street", Core::Variant (String ("Katalońska")));
        input.set ("houseNo", Core::Variant (String ("5")));
        input.set ("flatNo", Core::Variant (String ("30")));
        input.set ("postalCode", Core::Variant (String ("02-763")));
        input.set ("city", Core::Variant (String ("Warszawa")));

        // Obiekt wyjściowy
        StringList outputStr;

        /*
         * Nie mam fabryki, wiec podobnie jak w przypadku
         * adresu z pustym miastem, musze umiescic puste
         * elementy listy. Edytor tylko je wyedytuje.
         */
//        output.push_back ("");
//        output.push_back ("");
//        output.push_back ("");
//        output.push_back ("");
//        output.push_back ("");

        ListInserter output;
        SillyFactory sillyFactory;
        sillyFactory.setOriginal (Core::Variant (String ()));
        output.setElementFactory (&sillyFactory);
        output.setList (&outputStr);

/*--------------------------------------------------------------------------*/

        // Tym bedziemy edytowac pola skalarne
        NoopEditor noop;

        // Mapowanie
        Mapping mp1;

//        StringList inputPaths1;
//        inputPaths1.push_back ("street");
//        inputPaths1.push_back ("houseNo");
//        inputPaths1.push_back ("flatNo");
//        inputPaths1.push_back ("postalCode");
//        inputPaths1.push_back ("city");
//
//        StringList outputPaths1;
//        outputPaths1.push_back ("0");
//        outputPaths1.push_back ("1");
//        outputPaths1.push_back ("2");
//        outputPaths1.push_back ("3");
//        outputPaths1.push_back ("4");
//
//        List <IEditor *> editors1;
//        editors1.push_back (&noop);
//        editors1.push_back (&noop);
//        editors1.push_back (&noop);
//        editors1.push_back (&noop);
//        editors1.push_back (&noop);
//
//        mp1.setEditors (&editors1);
//        mp1.setInputPaths (&inputPaths1);
//        mp1.setOutputPaths (&outputPaths1);
//        mp1.init ();

        SimpleRule sr2 ("street", "0", &noop);
        SimpleRule sr3 ("houseNo", "1", &noop);
        SimpleRule sr4 ("flatNo", "2", &noop);
        SimpleRule sr5 ("postalCode", "3", &noop);
        SimpleRule sr6 ("city", "4", &noop);

        RuleList ruleList2;
        ruleList2.push_back (&sr2);
        ruleList2.push_back (&sr3);
        ruleList2.push_back (&sr4);
        ruleList2.push_back (&sr5);
        ruleList2.push_back (&sr6);
        mp1.setRuleList (&ruleList2);

/*--------------------------------------------------------------------------*/

        // A to jest głowny edytor mapy na liste (mapujący).
        MappedEditor me1;
        me1.setMapping (&mp1);

        // Mapujacy edytor potrzebuje beanWrapperow - w XMLu to bedzie jedna linijka.
        BeanWrapper beanWrapper1a;
        BeanWrapperPluginList pluginList1;
        ListPlugin listPlugin;
        PropertyRWBeanWrapperPlugin getterSetterPlugin1;
        GetPutMethodRWBeanWrapperPlugin getputPlugin;
        pluginList1.push_back (&listPlugin);
        pluginList1.push_back (&getputPlugin);
        //pluginList1.push_back (&getterSetterPlugin1);
        beanWrapper1a.setPluginList (&pluginList1);

        BeanWrapper beanWrapper1b;
        beanWrapper1b.setPluginList (&pluginList1);

        me1.setIn (&beanWrapper1a);
        me1.setOut (&beanWrapper1b);

        Variant out1 = Core::Variant (&output);
        me1.edit (Core::Variant (&input), &out1);

/*--------------------------------------------------------------------------*/

        /*
         *  Teraz wlasciwe byloby wyciagniecie wskaznika z out (mimo, ze
         *  tak naprawde, to oryginalny obiekt output ulegl zmianie). Jenak
         *  uniwersalny kod powinien wyciagnac wskaznik (lub wartosc).
         */

        BOOST_REQUIRE (output.size () == 5);
        BOOST_REQUIRE (vcast <String> (output.get (0)) == "Katalońska");
        BOOST_REQUIRE (vcast <String> (output.get (1)) == "5");
        BOOST_REQUIRE (vcast <String> (output.get (2)) == "30");
        BOOST_REQUIRE (vcast <String> (output.get (3)) == "02-763");
        BOOST_REQUIRE (vcast <String> (output.get (4)) == "Warszawa");

/*--------------------------------------------------------------------------*/

        ListToStringEditor listEd;
        listEd.setDelimiter (",");
        listEd.setQuotation ("\"");
        String output3;
        Variant out3 = Core::Variant (&output3);

        listEd.edit (Core::Variant (&output), &out3);

//        std::cerr << output3 << std::endl;
        BOOST_REQUIRE (output3 == "\"Katalońska\",\"5\",\"30\",\"02-763\",\"Warszawa\"");
}
#endif

/****************************************************************************/

Core::String listOfListsToString (const std::list <StringList *> &list)
{
        String ret;

        typedef std::list <StringList *>::const_iterator BigIter;
        typedef StringList::const_iterator SmallIter;

        BigIter big;
        SmallIter small;

        for (big = list.begin (); big != list.end (); big++) {

                StringList *inner = *big;
                small = inner->begin ();

                while (true) {
                        ret += *small;

                        if (++small != inner->end ()) {
                                ret += ", ";
                        }
                        else {
                                break;
                        }
                }

                ret += "\n";
        }

        return ret;
}

/**
 *
 */
void printListOfLists (const std::list <StringList *> &list)
{
        std::cerr << listOfListsToString (list) << std::endl;
}

#if 0
/**
 * Test polaczonego edytora mapped i indexed.
 */
BOOST_AUTO_TEST_CASE (testComplicatedEditors)
{
         Address a1;
         a1.setPostalCode ("02-763");
         a1.setStreet ("Sesame");

         City c1;
         c1.setName ("Warszawa");

         a1.setCity (&c1);

         // Obiekt wyjściowy
         StringList outputStr;

/*--------------------------------------------------------------------------*/

         // Tym bedziemy edytowac pola skalarne
         NoopEditor noop;

/*------Mapowanie-----------------------------------------------------------*/

         Mapping mp1;

//         StringList inputPaths1;
//         inputPaths1.push_back ("street");
//         inputPaths1.push_back ("postalCode");
//         inputPaths1.push_back ("city.name");
//
//         StringList outputPaths1;
//         outputPaths1.push_back ("0");
//         outputPaths1.push_back ("2");
//         outputPaths1.push_back ("1");
//
//         List <IEditor *> editors1;
//         editors1.push_back (&noop);
//         editors1.push_back (&noop);
//         editors1.push_back (&noop);
//
//         mp1.setEditors (&editors1);
//         mp1.setInputPaths (&inputPaths1);
//         mp1.setOutputPaths (&outputPaths1);
//         mp1.init ();

         SimpleRule sr2 ("street", "0", &noop);
         SimpleRule sr3 ("postalCode", "2", &noop);
         SimpleRule sr4 ("city.name", "1", &noop);

         RuleList ruleList1;
         ruleList1.push_back (&sr2);
         ruleList1.push_back (&sr3);
         ruleList1.push_back (&sr4);
         mp1.setRuleList (&ruleList1);

 /*--------------------------------------------------------------------------*/

         // A to jest głowny edytor obiektu na liste (mapujący).
         Ptr <MappedEditor> me1 (new MappedEditor);
         me1->setMapping (&mp1);

         // Mapujacy edytor potrzebuje beanWrapperow - w XMLu to bedzie jedna linijka.
         BeanWrapper beanWrapper1a;
         BeanWrapperPluginList pluginList1;
         ListPlugin listPlugin;
         PropertyRWBeanWrapperPlugin getterSetterPlugin1;
         GetPutMethodRWBeanWrapperPlugin getputPlugin;
         pluginList1.push_back (&listPlugin);
         pluginList1.push_back (&getputPlugin);
         pluginList1.push_back (&getterSetterPlugin1);
         beanWrapper1a.setPluginList (&pluginList1);

         BeanWrapper beanWrapper1b;
         beanWrapper1b.setPluginList (&pluginList1);

         me1->setIn (&beanWrapper1a);
         me1->setOut (&beanWrapper1b);

/*-------No i uruchamiamy dla testu:----------------------------------------*/

         Variant out1 = Core::Variant (&output);
         me1->edit (Core::Variant (&a1), &out1);

/*--------------------------------------------------------------------------*/

         /*
          *  Teraz wlasciwe byloby wyciagniecie wskaznika z out (mimo, ze
          *  tak naprawde, to oryginalny obiekt output ulegl zmianie). Jenak
          *  uniwersalny kod powinien wyciagnac wskaznik (lub wartosc).
          */

         BOOST_REQUIRE (output.size () == 3);
         BOOST_REQUIRE (vcast <String> (output.get (0)) == "Sesame");
         BOOST_REQUIRE (vcast <String> (output.get (1)) == "Warszawa");
         BOOST_REQUIRE (vcast <String> (output.get (2)) == "02-763");

/*--------------------------------------------------------------------------*/

         Ptr <StringListFactoryTmpClass> stringListFactory (new StringListFactoryTmpClass);

         FactoryEditor addressToStringListEditor;
         addressToStringListEditor.setEditor (me1);
         addressToStringListEditor.setFactory (stringListFactory);

         Variant out2;
//         TODO Zakomentowane z powodu zaprzesnia obsługi podwójnych wariantów i proxy.
//         addressToStringListEditor.convert (Core::Variant (&a1), &out2);
//         IList *output2 = vcast <IList *> (out2);
//
//         BOOST_REQUIRE (output2->size () == 3);
//         BOOST_REQUIRE (vcast <String> (output2->get (0)) == "Sesame");
//         BOOST_REQUIRE (vcast <String> (output2->get (1)) == "Warszawa");
//         BOOST_REQUIRE (vcast <String> (output2->get (2)) == "02-763");

/*-------Lista adresow------------------------------------------------------*/

         Address a2;
         a2.setPostalCode ("12-345");
         a2.setStreet ("Katalońska");
         City c2;
         c2.setName ("Kraków");
         a2.setCity (&c2);

         Address a3;
         a3.setPostalCode ("54-321");
         a3.setStreet ("Belwederska");
         City c3;
         c3.setName ("Poznań");
         a3.setCity (&c3);

         List <Address *> adresy;
         adresy.push_back (&a1);
         adresy.push_back (&a2);
         adresy.push_back (&a3);

/*--------------------------------------------------------------------------*/

         IndexedEditor indexed;
         indexed.setDefaultEditor (me1);

         // Bez fabryki.
         List <StringList *> outputList;
         ListInserter output3;
         output3.setList (&outputList);
         output3.setElementFactory (stringListFactory.get ());

         Variant out3 = Core::Variant (&output3);

//         TODO Nie działają wrappery.
//         indexed.edit (Core::Variant (&adresy), &out3);
//
///*--------------------------------------------------------------------------*/
//
//         BOOST_REQUIRE (outputList.size () == 3);
//
//         BOOST_REQUIRE (outputList.getAt (0)->getAt (0) == "Sesame");
//         BOOST_REQUIRE (outputList.getAt (0)->getAt (1) == "Warszawa");
//         BOOST_REQUIRE (outputList.getAt (0)->getAt (2) == "02-763");
//
//         BOOST_REQUIRE (outputList.getAt (1)->getAt (0) == "Katalońska");
//         BOOST_REQUIRE (outputList.getAt (1)->getAt (1) == "Kraków");
//         BOOST_REQUIRE (outputList.getAt (1)->getAt (2) == "12-345");
//
//         BOOST_REQUIRE (outputList.getAt (2)->getAt (0) == "Belwederska");
//         BOOST_REQUIRE (outputList.getAt (2)->getAt (1) == "Poznań");
//         BOOST_REQUIRE (outputList.getAt (2)->getAt (2) == "54-321");

//         printListOfLists (outputList);

/*--------------------------------------------------------------------------*/

         /*
          * A teraz jeszcze podpinam ten indexedEditor pod mapped editor.
          * W ten sposob dla sciezki "" uruchomi sie indexed Editor.
          */

         Mapping mp2;

//         StringList inputPaths2;
//         inputPaths2.push_back ("");
//
//         StringList outputPaths2;
//         outputPaths2.push_back ("");
//
//         List <IEditor *> editors2;
//         editors2.push_back (&indexed);
//
//         mp2.setEditors (&editors2);
//         mp2.setInputPaths (&inputPaths2);
//         mp2.setOutputPaths (&outputPaths2);
//         mp2.init ();

         SimpleRule sr5 ("", "", &indexed);
         IndexRule ir1 (me1.get ());
         RuleList ruleList2;
         ruleList2.push_back (&sr5);
         ruleList2.push_back (&ir1);
         mp2.setRuleList (&ruleList2);

         MappedEditor me2;
         me2.setMapping (&mp2);

         // Uwaga! Musza byc osobne beanWrappery per MappedEditor.
         BeanWrapper beanWrapper2a;
         beanWrapper2a.setPluginList (&pluginList1);
         BeanWrapper beanWrapper2b;
         beanWrapper2b.setPluginList (&pluginList1);

         me2.setIn (&beanWrapper2a);
         me2.setOut (&beanWrapper2b);

         output3.clear ();

 //         TODO Nie działają wrappery.
//         me2.edit (Core::Variant (&adresy), &out3);
//
///*--------------------------------------------------------------------------*/
//
//         BOOST_REQUIRE (outputList.size () == 3);
//
//         BOOST_REQUIRE (outputList.getAt (0)->getAt (0) == "Sesame");
//         BOOST_REQUIRE (outputList.getAt (0)->getAt (1) == "Warszawa");
//         BOOST_REQUIRE (outputList.getAt (0)->getAt (2) == "02-763");
//
//         BOOST_REQUIRE (outputList.getAt (1)->getAt (0) == "Katalońska");
//         BOOST_REQUIRE (outputList.getAt (1)->getAt (1) == "Kraków");
//         BOOST_REQUIRE (outputList.getAt (1)->getAt (2) == "12-345");
//
//         BOOST_REQUIRE (outputList.getAt (2)->getAt (0) == "Belwederska");
//         BOOST_REQUIRE (outputList.getAt (2)->getAt (1) == "Poznań");
//         BOOST_REQUIRE (outputList.getAt (2)->getAt (2) == "54-321");

//         printListOfLists (outputList);

/*--------------------------------------------------------------------------*/

         a2.setPostalCode ("99-999");
         a2.setStreet ("Barcelońska");
         a2.setCity (&c3);

         out3 = Core::Variant (&outputList);
//         TODO
//         me2.convert (Core::Variant (&adresy), "1", &out3, "1");
//
///*--------------------------------------------------------------------------*/
//
//         BOOST_REQUIRE (outputList.size () == 3);
//
//         BOOST_REQUIRE (outputList.getAt (0)->getAt (0) == "Sesame");
//         BOOST_REQUIRE (outputList.getAt (0)->getAt (1) == "Warszawa");
//         BOOST_REQUIRE (outputList.getAt (0)->getAt (2) == "02-763");
//
//         BOOST_REQUIRE (outputList.getAt (1)->getAt (0) == "Barcelońska");
//         BOOST_REQUIRE (outputList.getAt (1)->getAt (1) == "Poznań");
//         BOOST_REQUIRE (outputList.getAt (1)->getAt (2) == "99-999");
//
//         BOOST_REQUIRE (outputList.getAt (2)->getAt (0) == "Belwederska");
//         BOOST_REQUIRE (outputList.getAt (2)->getAt (1) == "Poznań");
//         BOOST_REQUIRE (outputList.getAt (2)->getAt (2) == "54-321");
}
#endif

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testNoopEditor)
{
        NoopEditor noop;

        Variant in = Core::Variant (String ("kupa"));
        Variant out;

        noop.convert (in, &out);

        BOOST_REQUIRE (vcast <String> (out) == "kupa");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testStringToIntEditor)
{
        LexicalEditor <Core::String, int> editor;

        Variant in = Core::Variant (String ("12345"));
        Variant out;

        editor.convert (in, &out);

        BOOST_REQUIRE (vcast <int> (out) == 12345);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testStringToDoubleEditor)
{
        LexicalEditor <Core::String, double> editor;

        Variant in = Core::Variant (String ("12.5"));
        Variant out;

        editor.convert (in, &out);

        // == powinno zadzialac mimo niedokladnosci.
        BOOST_REQUIRE (vcast <double> (out) == 12.5);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testStringToCharEditor)
{
        LexicalEditor <Core::String, char> editor;

        Variant in = Core::Variant (String ("a"));
        Variant out;

        editor.convert (in, &out);

        BOOST_REQUIRE (vcast <char> (out) == 'a');
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testStringToBoolEditor)
{
        LexicalEditor <Core::String, bool> editor;

        Variant in = Core::Variant (String ("true"));
        Variant out;

        editor.convert (in, &out);
        BOOST_REQUIRE (vcast <bool> (out));

        in = Core::Variant (String ("false"));
        editor.convert (in, &out);
        BOOST_REQUIRE (!vcast <bool> (out));
}

#if 0
/**
 *
 */
BOOST_AUTO_TEST_CASE (testSimpleMapEditor)
{
        Ptr <Factory::IFactory> sillyFactory (new SillyFactory (Core::Variant (String ())));

        SimpleMapEditor simple;

        Ptr <EditorMap> mapEd (new EditorMap);
        mapEd->operator[] ("key1") = boost::make_shared <FactoryEditor> (boost::make_shared <DummyJEditor> ("[", "]"), sillyFactory);
        mapEd->operator[] ("key2") = boost::make_shared <FactoryEditor> (boost::make_shared <DummyJEditor> ("]", "["), sillyFactory);
        mapEd->operator[] ("key3") = boost::make_shared <FactoryEditor> (boost::make_shared <DummyJEditor> ("{", "}"), sillyFactory);
        mapEd->operator[] ("key4") = boost::make_shared <FactoryEditor> (boost::make_shared <DummyJEditor> ("(", ")"), sillyFactory);
        mapEd->operator[] ("key5") = boost::make_shared <FactoryEditor> (boost::make_shared <DummyJEditor> ("<", ">"), sillyFactory);
        mapEd->operator[] ("key6") = boost::make_shared <FactoryEditor> (boost::make_shared <DummyJEditor> ("A", "B"), sillyFactory);
        mapEd->operator[] ("key7") = boost::make_shared <FactoryEditor> (boost::make_shared <DummyJEditor> ("a", "b"), sillyFactory);

        simple.setEditors (mapEd);
        simple.setDefaultEditor (boost::make_shared <FactoryEditor> (boost::make_shared <DummyJEditor> ("&", "&"), sillyFactory));

/*--------------------------------------------------------------------------*/

        StringMap input;

        input["key1"] = "Ala";
        input["key1.5"] = "połowiczna";
        input["key2"] = "ma";
        input["key3"] = "kota";
        input["key4"] = "janek";
        input["key5"] = "ma";
        input["key5.5"] = "znów połówka";
        input["key6"] = "ochote";
        input["key7"] = "na ale";
        input["key7.5"] = "K202 odra";

        StringMap outMap;

/*--------------------------------------------------------------------------*/

        Variant out = Core::Variant (&outMap);
        simple.edit (Core::Variant (&input), &out);

        BOOST_REQUIRE_EQUAL (outMap["key1"], "[Ala]");
        BOOST_REQUIRE_EQUAL (outMap["key2"], "]ma[");
        BOOST_REQUIRE_EQUAL (outMap["key3"], "{kota}");
        BOOST_REQUIRE_EQUAL (outMap["key4"], "(janek)");
        BOOST_REQUIRE_EQUAL (outMap["key5"], "<ma>");
        BOOST_REQUIRE_EQUAL (outMap["key6"], "AochoteB");
        BOOST_REQUIRE_EQUAL (outMap["key7"], "ana aleb");

        // Te sie skonwertowały za pomocą defaultEditor.
        BOOST_REQUIRE_EQUAL (outMap["key1.5"], "&połowiczna&");
        BOOST_REQUIRE_EQUAL (outMap["key5.5"], "&znów połówka&");
        BOOST_REQUIRE_EQUAL (outMap["key7.5"], "&K202 odra&");
}
#endif

#if 0
/**
 * Testuje ProxyEditor, czyli edytor, któremu można nie podawać inputum bo
 * ma go w środku.
 */
BOOST_AUTO_TEST_CASE (testProxyEditor)
{
        Variant input = Core::Variant (String ("iwasz"));
        Variant output = Core::Variant (String (""));

        Ptr <IEditor> bracket (new DummyJEditor ("[", "]"));
        Ptr <IEditor> proxy = boost::make_shared <ProxyEditor> (bracket, input);

        proxy->convert (Variant (), &output);
        BOOST_REQUIRE (vcast <Core::String> (output) == "[iwasz]");

        proxy->convert (Core::Variant (String ("asia")), &output);
        BOOST_REQUIRE (vcast <Core::String> (output) == "[asia]");
}
#endif

BOOST_AUTO_TEST_SUITE_END ();
