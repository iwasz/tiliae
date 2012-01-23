/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#define BOOST_TEST_MODULE LightCoreTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "XmlTextReader.h"
#include "XmlException.h"

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (Variant01);
using namespace Xml;
using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testComplex)
{
        XmlTextReader reader;
        reader.readerForFilename ("../src/xml/test/viewTest3.xml");

        try {
                std::string debug;

                while (reader.read ()) {
                        debug += std::string ("Depth=") + boost::lexical_cast <std::string> (reader.depth ()) +
                                        ", nodeType=" + boost::lexical_cast <std::string> (reader.nodeType ()) +
                                        ", nodeName=" + reader.name () + ", isEmptyElem=" + boost::lexical_cast <std::string> (reader.isEmptyElement ()) +
                                        "\n" + reader.value () + "\n\n";

                        if (reader.nodeType () == 1) {
                                while (reader.moveToNextAttribute ()) {

                                        debug += std::string ("Depth=") + boost::lexical_cast <std::string> (reader.depth ()) +
                                                        ", nodeType=" + boost::lexical_cast <std::string> (reader.nodeType ()) +
                                                        ", attribCount=" + boost::lexical_cast <std::string> (reader.attributeCount ()) +
                                                        ", hasAttrib=" + boost::lexical_cast <std::string> (reader.hasAttributes ()) +
                                                        ", name=" + reader.name () + "\n" + reader.value ();

                                }
                        }

//                        std::cerr << debug << std::endl;
                }

                // To jest bardzo podstawowy test, sprawdzamy czy jest cokolwiek :)
                BOOST_REQUIRE (debug.size () > 100);

        }
        catch (const Xml::XmlException &e) {
                std::cerr << "Error" << std::endl;
        }
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testVersion)
{
        XmlTextReader reader;
        reader.readerForDoc (
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "\n"
                "<beans>\n"
                "\n"
                "    <bean id=\"simpleTokenizer\" class=\"SimpleTokenizer\">\n"
                "        <property name=\"separator\">\n"
                "            <value>.</value>\n"
                "        </property>\n"
                "    </bean>\n");

        reader.read ();
        BOOST_REQUIRE (reader.encoding () == "UTF-8");
        BOOST_REQUIRE (reader.xmlVersion () == "1.0");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testNodes)
{
        XmlTextReader reader;
        reader.readerForDoc (
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "\n"
                "<beans>\n"
                "\n"
                "    <bean id=\"simpleTokenizer\" class=\"SimpleTokenizer\">\n"
                "        <property name=\"separator\">\n"
                "            <value>.</value>\n"
                "        </property>\n"
                "    </bean></beans>\n");

        reader.read ();

        BOOST_REQUIRE (reader.depth () == 0);
        BOOST_REQUIRE (reader.nodeType () == 1);
        BOOST_REQUIRE (reader.name () == "beans");
        BOOST_REQUIRE (reader.isEmptyElement () == false);

        reader.read ();
        reader.read ();

        // Element w elemencie ma zaglebienie 1. Atrybuty tego glownego tez maja 1.
        BOOST_REQUIRE (reader.depth () == 1);
        BOOST_REQUIRE (reader.nodeType () == 1);
        BOOST_REQUIRE (reader.name () == "bean");
        BOOST_REQUIRE (reader.isEmptyElement () == false);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testAttributes)
{
        XmlTextReader reader;
        reader.readerForDoc (
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<bean id=\"simpleTokenizer\" class=\"SimpleTokenizer\" a=\"atribA\" b=\"atribB\">\n"
                "    <property name=\"separator\">\n"
                "        <value>.</value>\n"
                "    </property>\n"
                "</bean>\n");

        reader.read ();

        BOOST_REQUIRE (reader.depth () == 0);
        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ELEMENT);
        BOOST_REQUIRE (reader.name () == "bean");
        BOOST_REQUIRE (reader.isEmptyElement () == false);

        BOOST_REQUIRE (reader.hasAttributes ());
        BOOST_REQUIRE (reader.attributeCount () == 4);

        reader.moveToNextAttribute ();

        // Reader iteruje tak samo po elementach jak i po ich atrybutach.
        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ATTRIBUTE);
        BOOST_REQUIRE (reader.depth () == 1);
        BOOST_REQUIRE (reader.name () == "id");
        BOOST_REQUIRE (reader.value () == "simpleTokenizer");

        reader.moveToNextAttribute ();

        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ATTRIBUTE);
        BOOST_REQUIRE (reader.depth () == 1);
        BOOST_REQUIRE (reader.name () == "class");
        BOOST_REQUIRE (reader.value () == "SimpleTokenizer");

        reader.moveToNextAttribute ();

        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ATTRIBUTE);
        BOOST_REQUIRE (reader.depth () == 1);
        BOOST_REQUIRE (reader.name () == "a");
        BOOST_REQUIRE (reader.value () == "atribA");

        reader.moveToNextAttribute ();

        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ATTRIBUTE);
        BOOST_REQUIRE (reader.depth () == 1);
        BOOST_REQUIRE (reader.name () == "b");
        BOOST_REQUIRE (reader.value () == "atribB");

        BOOST_REQUIRE (!reader.moveToNextAttribute ());

        // Ustawiamy sie spowrotem na pierwszy atrybut.
        reader.moveToFirstAttribute ();

        // Reader iteruje tak samo po elementach jak i po ich atrybutach.
        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ATTRIBUTE);
        BOOST_REQUIRE (reader.depth () == 1);
        BOOST_REQUIRE (reader.name () == "id");
        BOOST_REQUIRE (reader.value () == "simpleTokenizer");

        // A teraz wychodzimy z elementow i ustawiamy sie na glownym elemencie.
        reader.moveToElement ();

        // Sprawdzamy, czy jestesmy na elemencie, a nie na atrybutach.
        BOOST_REQUIRE (reader.depth () == 0);
        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ELEMENT);
        BOOST_REQUIRE (reader.name () == "bean");
        BOOST_REQUIRE (reader.isEmptyElement () == false);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testAttributes2)
{
        XmlTextReader reader;
        reader.readerForDoc (
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<bean id=\"simpleTokenizer\" class=\"SimpleTokenizer\" a=\"atribA\" b=\"atribB\">\n"
                "    <property name=\"separator\">\n"
                "        <value>.</value>\n"
                "    </property>\n"
                "</bean>\n");

        reader.read ();

        reader.moveToAttribute ("a");

         // Reader iteruje tak samo po elementach jak i po ich atrybutach.
         BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ATTRIBUTE);
         BOOST_REQUIRE (reader.depth () == 1);
         BOOST_REQUIRE (reader.name () == "a");
         BOOST_REQUIRE (reader.value () == "atribA");

         reader.moveToAttribute ("b");

          // Reader iteruje tak samo po elementach jak i po ich atrybutach.
          BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ATTRIBUTE);
          BOOST_REQUIRE (reader.depth () == 1);
          BOOST_REQUIRE (reader.name () == "b");
          BOOST_REQUIRE (reader.value () == "atribB");

        reader.moveToAttribute (0);

        // Reader iteruje tak samo po elementach jak i po ich atrybutach.
        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ATTRIBUTE);
        BOOST_REQUIRE (reader.depth () == 1);
        BOOST_REQUIRE (reader.name () == "id");
        BOOST_REQUIRE (reader.value () == "simpleTokenizer");

        reader.moveToAttribute (3);

        // Reader iteruje tak samo po elementach jak i po ich atrybutach.
        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ATTRIBUTE);
        BOOST_REQUIRE (reader.depth () == 1);
        BOOST_REQUIRE (reader.name () == "b");
        BOOST_REQUIRE (reader.value () == "atribB");

        BOOST_REQUIRE (!reader.moveToAttribute (4));
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testAttributesNamespace)
{
        XmlTextReader reader;
        reader.readerForDoc (
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<bean xmlns:nmspc=\"http://www.w3.org/TR/html4/\"\n"
                "    id=\"simpleTokenizer\" class=\"SimpleTokenizer\" a=\"atribA\" b=\"atribB\">\n"
                "    <property name=\"separator\" nmspc:name=\"test\">\n"
                "        <value>.</value>\n"
                "    </property>\n"
                "</bean>\n");

        reader.read ();

        reader.moveToAttribute (0);

        // Reader iteruje tak samo po elementach jak i po ich atrybutach.
        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ATTRIBUTE);
        BOOST_REQUIRE (reader.depth () == 1);
        BOOST_REQUIRE (reader.name () == "xmlns:nmspc");
        BOOST_REQUIRE (reader.value () == "http://www.w3.org/TR/html4/");

        reader.read ();
        reader.read ();
        reader.moveToAttribute (0);

        // Reader iteruje tak samo po elementach jak i po ich atrybutach.
        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ATTRIBUTE);
        BOOST_REQUIRE (reader.depth () == 2);
        BOOST_REQUIRE (reader.name () == "name");
        BOOST_REQUIRE (reader.value () == "separator");

        BOOST_REQUIRE (!reader.moveToAttribute (4));

        // Tak to dziala. Fmiefnie.
        BOOST_REQUIRE (reader.moveToAttribute ("name", "http://www.w3.org/TR/html4/"));

        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ATTRIBUTE);
        BOOST_REQUIRE (reader.depth () == 2);
        BOOST_REQUIRE (reader.name () == "nmspc:name");
        BOOST_REQUIRE (reader.value () == "test");

        BOOST_REQUIRE (reader.localName () == "name");
        BOOST_REQUIRE (reader.namespaceUri () == "http://www.w3.org/TR/html4/");
        BOOST_REQUIRE (reader.lookupNamespace ("nmspc") == "http://www.w3.org/TR/html4/");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testGetAttributeValue)
{
        XmlTextReader reader;
        reader.readerForDoc (
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<bean xmlns:nmspc=\"http://www.w3.org/TR/html4/\"\n"
                "    id=\"simpleTokenizer\" class=\"SimpleTokenizer\" a=\"atribA\" b=\"atribB\">\n"
                "    <property name=\"separator\" nmspc:name=\"test\">\n"
                "        <value>.</value>\n"
                "    </property>\n"
                "</bean>\n");

        BOOST_REQUIRE (reader.read ());

        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ELEMENT);
        BOOST_REQUIRE (reader.depth () == 0);
        BOOST_REQUIRE (reader.name () == "bean");

        BOOST_REQUIRE (reader.moveToAttribute ("a"));

        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_ATTRIBUTE);
        BOOST_REQUIRE (reader.depth () == 1);
        BOOST_REQUIRE (reader.name () == "a");
        BOOST_REQUIRE (reader.value () == "atribA");

        BOOST_REQUIRE (reader.readAttributeValue ());

        BOOST_REQUIRE (reader.nodeType () == XML_READER_TYPE_TEXT);
        BOOST_REQUIRE (reader.depth () == 2);
        BOOST_REQUIRE (reader.name () == "#text");
        BOOST_REQUIRE (reader.value () == "atribA");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testGetAttribute)
{
        XmlTextReader reader;
        reader.readerForDoc (
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<bean xmlns:nmspc=\"http://www.w3.org/TR/html4/\"\n"
                "    id=\"simpleTokenizer\" class=\"SimpleTokenizer\" a=\"atribA\" b=\"atribB\">\n"
                "    <property name=\"separator\" nmspc:name=\"test\">\n"
                "        <value>.</value>\n"
                "    </property>\n"
                "</bean>\n");

        reader.read ();

//        reader.moveToAttribute ("a");

        BOOST_REQUIRE (reader.getAttribute ("a") == "atribA");
        BOOST_REQUIRE (reader.getAttribute ("b") == "atribB");
        BOOST_REQUIRE (reader.getAttribute ("id") == "simpleTokenizer");
        BOOST_REQUIRE (reader.getAttribute ("class") == "SimpleTokenizer");
        BOOST_REQUIRE (reader.getAttribute ("xmlns:nmspc") == "http://www.w3.org/TR/html4/");

        BOOST_REQUIRE (reader.getAttribute (0) == "http://www.w3.org/TR/html4/");
        BOOST_REQUIRE (reader.getAttribute (1) == "simpleTokenizer");
        BOOST_REQUIRE (reader.getAttribute (2) == "SimpleTokenizer");
        BOOST_REQUIRE (reader.getAttribute (3) == "atribA");
        BOOST_REQUIRE (reader.getAttribute (4) == "atribB");

        reader.read ();
        reader.read ();

        BOOST_REQUIRE (reader.getAttribute ("name", "http://www.w3.org/TR/html4/") == "test");
//        Tak sie nie da:
//        BOOST_REQUIRE (reader.getAttribute ("name") == "separator");
        BOOST_REQUIRE (reader.getAttribute ("name") == "separator");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testInputOutputXml)
{
        XmlTextReader reader;
        reader.readerForDoc (
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<bean xmlns:nmspc=\"http://www.w3.org/TR/html4/\"\n"
                "    id=\"simpleTokenizer\" class=\"SimpleTokenizer\" a=\"atribA\" b=\"atribB\">\n"
                "    <property name=\"separator\" nmspc:name=\"test\">\n"
                "        <value>.</value>\n"
                "    </property>\n"
                "</bean>\n");

        reader.read ();
        reader.read ();
        reader.read ();

        BOOST_REQUIRE (reader.readInnerXml ().size ());
        BOOST_REQUIRE (reader.readOuterXml ().size ());

        /*
         *  Wystarczy, ze nie zrzuci wyjatku. Tu sie pojawiaja jakies numerki,
         *  nie ma sensu testowac tego na obecnosc jakichs konkretnych numerow
         *  wierszy, czy kolumn.
         */
        reader.getParserColumnNumber ();
        reader.getParserLineNumber ();

        BOOST_REQUIRE (reader.byteConsumed () > 0);

        BOOST_REQUIRE (!reader.hasValue ());
        BOOST_REQUIRE (reader.read ()); // Jestem na <value>
        BOOST_REQUIRE (reader.hasValue ());
        BOOST_REQUIRE (reader.read ()); // Jestem na tekscie #text
        BOOST_REQUIRE (!reader.hasValue ());
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testNext)
{
        XmlTextReader reader;
        reader.readerForDoc (
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<tags>\n"
                "<bean>\n"
                "       <prop/>\n"
                "       <klop/>\n"
                "</bean>\n"
                "<srean>\n"
                "       <prop1/>\n"
                "       <klop1/>\n"
                "</srean>\n"
                "<pierdziean>\n"
                "       <prop2/>\n"
                "       <klop2/>\n"
                "</pierdziean>\n"
                "</tags>\n"
        );

        reader.read ();
        reader.read ();
        BOOST_REQUIRE (reader.name () == "#text");
        reader.read ();
        BOOST_REQUIRE (reader.name () == "bean");
        reader.next ();
        reader.next (); // Glupie z tymi znakami nowej linii. Komu to potrzebne!?
        BOOST_REQUIRE (reader.name () == "srean");
        reader.read ();
        reader.read ();
        BOOST_REQUIRE (reader.name () == "prop1");
        reader.next ();
        reader.next ();
        BOOST_REQUIRE (reader.name () == "klop1");
        BOOST_REQUIRE (reader.next ());
//        std::cerr << reader.name () << std::endl;
        BOOST_REQUIRE (reader.next ());
//        std::cerr << reader.name () << std::endl;
        BOOST_REQUIRE (reader.next ());
//        std::cerr << reader.name () << std::endl;
        BOOST_REQUIRE (reader.next ()); // Az 4 razy!
        BOOST_REQUIRE (reader.name () == "pierdziean");
}

BOOST_AUTO_TEST_SUITE_END ();
