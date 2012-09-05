/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include "K202.h"
#include "TestHelpers.h"
#include "../extension/CacheExtension.h"
#include "../../core/variant/Variant.h"
#include "../../testHelpers/Address.h"
#include "../../testHelpers/City.h"
#include "../../testHelpers/Country.h"
#include "../../beanWrapper/beanWrapper/BeanWrapper.h"

BOOST_AUTO_TEST_SUITE (ContextDepTest06);
using namespace k202;
using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testPlaceholder)
{
        Ptr <K202> k202 = K202::create (Wrapper::BeanWrapper::create ());

        VariantVector paramList;
        paramList.push_back (Core::Variant (6667));
        TestRuntime <int>::test (k202, "%0", 6667, Variant (), paramList);

        paramList.clear ();
        paramList.push_back (Core::Variant (1));
        paramList.push_back (Core::Variant (2.6));
        paramList.push_back (Core::Variant (String ("kupa")));
        paramList.push_back (Core::Variant (std::string ("siku")));

        TestRuntime <int>::test (k202, "%0", 1, Variant (), paramList);
        TestRuntime <double>::test (k202, "%1", 2.6, Variant (), paramList);
        TestRuntime <String>::test (k202, "%2", "kupa", Variant (), paramList);
        TestRuntime <std::string>::test (k202, "%3", "siku", Variant (), paramList);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testProperty)
{
        Ptr <K202> k202 = K202::create (Wrapper::BeanWrapper::create ());

        VariantMap argsMap;
        Address a;
        a.setStreet ("Katalonska");
        a.setPostalCode ("05-500");
        argsMap["address"] = Core::Variant (&a);
        Variant vv = Core::Variant (&argsMap);

        TestRuntime <String>::test (k202, "$address.street", "Katalonska", vv);
        TestRuntime <String>::test (k202, "${address.postalCode}", "05-500", vv);
        TestRuntime <Address *>::test (k202, "$address", &a, vv);

        {
                Ptr <CacheExtension> cache = CacheExtension::create ();
                Ptr <K202> k202 = K202::create (Wrapper::BeanWrapper::create (), cache);

                VariantMap argsMap;
                Address a;
                a.setStreet ("Katalonska");
                a.setPostalCode ("05-500");
                argsMap["address"] = Core::Variant (&a);
                Variant vv = Core::Variant (&argsMap);

                TestRuntime <String>::test (k202, "$!address.street", "Katalonska", vv);
                TestRuntime <String>::test (k202, "$!address.street", "Katalonska", vv);
                TestRuntime <String>::test (k202, "$!address.street", "Katalonska", vv);
                a.setStreet ("XXX");
                TestRuntime <String>::test (k202, "$!address.street", "Katalonska", vv);
                cache->clearCache();
                TestRuntime <String>::test (k202, "$!address.street", "XXX", vv);

                TestRuntime <String>::test (k202, "${address.postalCode}", "05-500", vv);
                TestRuntime <Address *>::test (k202, "$!address", &a, vv);
        }
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testPropertyArgsMap)
{
        Ptr <K202> k202 = K202::create (Wrapper::BeanWrapper::create ());

        VariantMap argsMap;
        Address a;
        a.setStreet ("Katalonska");
        a.setPostalCode ("05-500");
        argsMap["address"] = Core::Variant (&a);

        TestRuntime <String>::test (k202, "$address.street", "Katalonska", Variant (), VariantVector (), argsMap);
        TestRuntime <String>::test (k202, "${address.postalCode}", "05-500", Variant (), VariantVector (), argsMap);
        TestRuntime <Address *>::test (k202, "$address", &a, Variant (), VariantVector (), argsMap);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testPropertyDomain)
{
        Ptr <K202> k202 = K202::create (Wrapper::BeanWrapper::create ());

        Address a;
        a.setStreet ("Katalonska");
        a.setPostalCode ("05-500");
        Variant v = Core::Variant (&a);

        TestRuntime <String>::test (k202, "$street", "Katalonska", v);
        TestRuntime <String>::test (k202, "${postalCode}", "05-500", v);
        TestRuntime <Address *>::test (k202, "${this}", &a, v);

        StringList vec;
        vec.push_back ("kupa");
        vec.push_back ("siku");

        v = Core::Variant (&vec);
        TestRuntime <std::string>::test (k202, "$0", "kupa", v);
        TestRuntime <std::string>::test (k202, "$1", "siku", v);

        /*--------------------------------------------------------------------------*/

        {
                VariantList a;
                VariantList b;
                VariantList c;
                VariantList d;

                a.push_back (Core::Variant (&b));
                b.push_back (Core::Variant (&c));
                c.push_back (Core::Variant (&d));
                d.push_back (Core::Variant ("tesciorek"));

                v = Core::Variant (&a);

                TestRuntime <bool>::test (k202, "$0.0.0.0 == 'tesciorek'", true, v);
        }
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testConditionalProperty)
{
        Ptr <K202> k202 = K202::create (Wrapper::BeanWrapper::create ());

        VariantMap argsMap;
        Address a;
        a.setStreet ("Katalonska");
        a.setPostalCode ("05-500");
        argsMap["address"] = Core::Variant (&a);
        Variant vv = Core::Variant (&argsMap);

        TestRuntime <String>::test (k202, "$!address.street", "Katalonska", vv);
        TestRuntime <String>::test (k202, "$!address.postalCode", "05-500", vv);
        TestRuntime <Address *>::test (k202, "$!address", &a, vv);

        assert (k202->run ("$!kupa", vv).isNone ());
        assert (k202->run ("$!kupa.siku", vv).isNone ());
        assert (k202->run ("$!address.street1", vv).isNone ());
        assert (k202->run ("$!address.street.2", vv).isNone ());
        //assert (k202->run ("$!kupa || false", vv).isNone ());
//        assert (k202->run ("$!{}", vv).isNone ());
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testConditionalPropertyArgsMap)
{
        Ptr <K202> k202 = K202::create (Wrapper::BeanWrapper::create ());

        VariantMap argsMap;
        Address a;
        a.setStreet ("Katalonska");
        a.setPostalCode ("05-500");
        argsMap["address"] = Core::Variant (&a);

        TestRuntime <String>::test (k202, "$!address.street", "Katalonska", Variant (), VariantVector (), argsMap);
        TestRuntime <String>::test (k202, "$!address.postalCode", "05-500", Variant (), VariantVector (), argsMap);
        TestRuntime <Address *>::test (k202, "$!address", &a, Variant (), VariantVector (), argsMap);

        assert (k202->run ("$!kupa", Variant (), VariantVector (), argsMap).isNone ());
        assert (k202->run ("$!kupa.siku", Variant (), VariantVector (), argsMap).isNone ());
        assert (k202->run ("$!address.street1", Variant (), VariantVector (), argsMap).isNone ());
        assert (k202->run ("$!address.street.2", Variant (), VariantVector (), argsMap).isNone ());
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testConditionalPropertyDomain)
{
        Ptr <K202> k202 = K202::create (Wrapper::BeanWrapper::create ());

        Address a;
        a.setStreet ("Katalonska");
        a.setPostalCode ("05-500");
        Variant v = Core::Variant (&a);

        TestRuntime <String>::test (k202, "$!street", "Katalonska", v);
        TestRuntime <String>::test (k202, "$!postalCode", "05-500", v);
        TestRuntime <Address *>::test (k202, "$!this", &a, v);

        StringList vec;
        vec.push_back ("kupa");
        vec.push_back ("siku");

        v = Core::Variant (&vec);
        TestRuntime <std::string>::test (k202, "$!0", "kupa", v);
        TestRuntime <std::string>::test (k202, "$!1", "siku", v);

        /*--------------------------------------------------------------------------*/

        {
                VariantList a;
                VariantList b;
                VariantList c;
                VariantList d;

                a.push_back (Core::Variant (&b));
                b.push_back (Core::Variant (&c));
                c.push_back (Core::Variant (&d));
                d.push_back (Core::Variant ("tesciorek"));

                v = Core::Variant (&a);

                TestRuntime <bool>::test (k202, "$!0.0.0.0 == 'tesciorek'", true, v);
        }
}

BOOST_AUTO_TEST_SUITE_END ();
