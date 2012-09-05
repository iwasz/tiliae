/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "Reflection.h"
#include "Core.h"
#include "variant/Cast.h"

BOOST_AUTO_TEST_SUITE (StandardTypesTest);

using namespace boost;
using namespace Core;
using namespace Reflection;

BOOST_AUTO_TEST_CASE (testInstantiateStandardTypes)
{
        Class *cls = Manager::classForName ("int");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("bool");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("char");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("signed char");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("unsigned char");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("double");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("long double");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("float");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("unsigned int");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("long int");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("unsigned long int");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("short int");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("unsigned short int");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("Variant");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("String");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("string");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("VariantVector");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("UStringVector");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("StringVector");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("VariantList");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("VariantMap");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("UStringList");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("UStringMap");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("StringList");
        BOOST_REQUIRE (cls);

        cls = Manager::classForName ("StringMap");
        BOOST_REQUIRE (cls);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testClassForType)
{
        Class *cls = Manager::classForType (typeid (int));
        BOOST_REQUIRE (cls);

//        cls = Manager::classForName ("bool");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("char");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("signed char");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("unsigned char");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("double");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("long double");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("float");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("unsigned int");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("long int");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("unsigned long int");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("short int");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("unsigned short int");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("Variant");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("String");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("string");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("VariantVector");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("StringVector");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("StdStringVector");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("VariantList");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("VariantMap");
//        BOOST_REQUIRE (cls);
//
        cls = Manager::classForType (typeid (StringList));
        BOOST_REQUIRE (cls);

//        cls = Manager::classForType (typeid (StringMap *));
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("StdStringList");
//        BOOST_REQUIRE (cls);
//
//        cls = Manager::classForName ("StdStringMap");
//        BOOST_REQUIRE (cls);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testStringListMethods)
{
        Class *cls = Manager::classForName ("StringList");
        BOOST_REQUIRE (cls);

        Constructor *constr = cls->getConstructor ();
        BOOST_REQUIRE (constr);

        Variant obj = constr->newInstance ();

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <StringList *> (obj));

        Method *get = cls->getMethod ("get", 1);
        Method *add = cls->getMethod ("add", 1);

        BOOST_REQUIRE (get);
        BOOST_REQUIRE (add);

        add->invoke (obj, Variant ("hfksfdkjsfd"));
        Variant ret = get->invoke (obj, Variant (0U));

        BOOST_REQUIRE (!ret.isNone ());
        BOOST_REQUIRE (ccast <std::string> (ret));
        BOOST_REQUIRE_EQUAL (vcast <std::string> (ret), "hfksfdkjsfd");
}

BOOST_AUTO_TEST_SUITE_END ();
