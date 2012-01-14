/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "Reflection.h"
#include "Core.h"
#include "../../testHelpers/Bar.h"
#include "../../core/Typedefs.h"

BOOST_AUTO_TEST_SUITE (ConstructorTest);

using namespace boost;
using namespace Core;
using namespace Reflection;

/**
 * W pliku XClass jest zdefiniowana lista XList z adnotacją f_.
 * Próbujemy ją zinstancjonować.
 */
BOOST_AUTO_TEST_CASE (testConstructor)
{
        Core::VariantVector args;

/*--------------------------------------------------------------------------*/

        Ptr <Class> cls = Manager::classForName ("Bar");
        BOOST_REQUIRE (cls);

        Ptr <Constructor> constr;

/*--------------------------------------------------------------------------*/

        // 7 argumentowy.
        constr = cls->getConstructor (7);
        BOOST_REQUIRE (constr);

        args.push_back (Core::Variant (String ("test1")));
        args.push_back (Core::Variant ("test2"));
        args.push_back (Core::Variant (12));
        args.push_back (Core::Variant (12.3));
        args.push_back (Core::Variant ('f'));
        args.push_back (Core::Variant (true));
        args.push_back (Core::Variant ('c'));

        Variant obj = constr->newInstance (&args);

        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <Bar *> (obj));

        Bar *bar = vcast <Bar *> (obj);

        BOOST_REQUIRE (bar->getField0() == "test1");
        BOOST_REQUIRE (bar->getField4() == 'f');

/*--------------------------------------------------------------------------*/

        constr = cls->getConstructor (3);
        BOOST_REQUIRE (constr);

        args.clear ();
        args.push_back (Core::Variant (String ("test7")));
        args.push_back (Core::Variant ("test78"));
        // Dodaj pusty.
        args.push_back (Core::Variant (Ptr <City> ()));

        obj = constr->newInstance (&args);
        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <Bar *> (obj));

        bar = vcast <Bar *> (obj);
        BOOST_REQUIRE (bar->getField0() == "test7");
        BOOST_REQUIRE (bar->getField1() == "test78");

/*--------------------------------------------------------------------------*/

        constr = cls->getConstructor (1);
        BOOST_REQUIRE (constr);

        args.clear ();
        args.push_back (Core::Variant (String ("test99")));

        obj = constr->newInstance (&args);
        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <Bar *> (obj));

        bar = vcast <Bar *> (obj);
        BOOST_REQUIRE (vcast <String> (bar->getButter()) == "test99");

/*--------------------------------------------------------------------------*/

        Core::TypeList tl;
        constr = cls->getConstructor (typeid (Core::Variant));
        BOOST_REQUIRE (constr);

        args.clear ();
        args.push_back (Core::Variant (String ("test789")));

        obj = constr->newInstance (&args);
        BOOST_REQUIRE (!obj.isNone ());
        BOOST_REQUIRE (ccast <Bar *> (obj));

        bar = vcast <Bar *> (obj);
        BOOST_REQUIRE (vcast <String> (bar->getButter()) == "test789");

/*--------------------------------------------------------------------------*/

//        TODO, nie przechodzi
//        tl.clear ();
//        tl.push_back (typeid (const Core::String &));
//        tl.push_back (typeid (const Core::String &));
//        tl.push_back (typeid (City *));
//        constr = cls->getConstructor (tl);
//        BOOST_REQUIRE (constr);

        args.clear ();
        args.push_back (Core::Variant (String ("test5")));
        args.push_back (Core::Variant (String ("test6")));
        args.push_back (Core::Variant ((City*)NULL));

//        obj = constr->newInstance (args);
//        BOOST_REQUIRE (!obj.isNone ());
//        BOOST_REQUIRE (can_cast <Bar *> (obj));

//        bar = vcast <Bar *> (obj);
//        BOOST_REQUIRE (bar->getField0() == "test5");
//        BOOST_REQUIRE (bar->getField1() == "test6");
//
///*--------------------------------------------------------------------------*/
//
//        tl.clear ();
//        tl.push_back (typeid (const Core::String &));
//        tl.push_back (typeid (const Core::String &));
//        tl.push_back (typeid (int));
//        tl.push_back (typeid (double));
//        tl.push_back (typeid (char));
//        tl.push_back (typeid (bool));
//        tl.push_back (typeid (char *));
//        constr = cls->getConstructor (tl);
//        BOOST_REQUIRE (constr);
//
//        args.clear ();
//        args.push_back (Core::Variant (String ("TST5")));
//        args.push_back (Core::Variant (String ("TST6")));
//        args.push_back (Core::Variant (44));
//        args.push_back (Core::Variant (55.6));
//        args.push_back (Core::Variant ('x'));
//        args.push_back (Core::Variant (false));
//        args.push_back (Core::Variant ((char *)NULL));
//
//        obj = constr->newInstance (args);
//
//        BOOST_REQUIRE (!obj.isNone ());
//        BOOST_REQUIRE (can_cast <Bar *> (obj));
//
//        bar = vcast <Bar *> (obj);
//
//        BOOST_REQUIRE (bar->getField0() == "TST5");
//        BOOST_REQUIRE (bar->getField1() == "TST6");
//        BOOST_REQUIRE (bar->getField2() == 44);
//        BOOST_REQUIRE (bar->getField3() == 55.6);
//        BOOST_REQUIRE (bar->getField4() == 'x');
//
///*--------------------------------------------------------------------------*/
//
//        constr = cls->getConstructor (89);
//        BOOST_REQUIRE (!constr);
//
//        constr = cls->getConstructor (Reflection::TypeList ());
//        BOOST_REQUIRE (!constr);
}

BOOST_AUTO_TEST_SUITE_END ();
