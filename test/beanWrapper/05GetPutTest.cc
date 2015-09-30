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
#include "beanWrapper/plugins/IBeanWrapperPlugin.h"
#include "beanWrapper/plugins/PropertyRWBeanWrapperPlugin.h"
#include "beanWrapper/plugins/GetPutMethodRWBeanWrapperPlugin.h"
#include "beanWrapper/plugins/MethodPlugin.h"
#include "testHelpers/Reflection_output.cc.h"

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (BWTest05);
using namespace Wrapper;
using namespace Core;
using namespace Common;
using namespace Editor;

/****************************************************************************/

/**
 * Wyszedł na jaw błąd, który uniemożliwia jednoczesne stosowanie GetPut i Method
 * pluginów. Kiedy się bowiem doda do klasy metody get/set, to MethodPlugin przestaje
 * już działać.
 */
BOOST_AUTO_TEST_CASE (testComplexGetPut)
{
        T::A a;
        a.setField ("testowy");
        BeanWrapper *bw = BeanWrapper::create (Variant (&a));

        BOOST_REQUIRE_EQUAL (vcast <std::string> (bw->get ("field")), "testowy");
        a.setField ("kupa");
        BOOST_REQUIRE_EQUAL (vcast <std::string> (bw->get ("name")), "kupa");
        BOOST_REQUIRE_NO_THROW (bw->get ("init"));
        delete bw;
}

/**
 * GetPut z greedy na true.
 */
BOOST_AUTO_TEST_CASE (testGreedyGetPut)
{
//        A a;
//
///*--------------------------------------------------------------------------*/
//
//        Ptr <BeanWrapper> beanWrapper = std::make_shared <BeanWrapper> (Core::Variant (&a));
//        Ptr <BeanWrapperPluginList> pluginList = std::make_shared <BeanWrapperPluginList> ();
//
//        Ptr <IBeanWrapperPlugin> plugin = std::make_shared <PropertyRWBeanWrapperPlugin> ();
//        pluginList->push_back (plugin);
//
//        plugin = std::make_shared <GetPutMethodRWBeanWrapperPlugin> (true);
//        pluginList->push_back (plugin);
//
//        plugin = std::make_shared <MethodPlugin> (MethodPlugin::METHOD);
//        pluginList->push_back (plugin);
//
//        beanWrapper->setPluginList (pluginList);
//
///*--------------------------------------------------------------------------*/
//
//        a.setField ("testowy");
//        BOOST_REQUIRE_EQUAL (vcast <std::string> (beanWrapper->get ("field")), "testowy");
//        a.setField ("kupa");
//        BOOST_REQUIRE_EQUAL (vcast <std::string> (beanWrapper->get ("name")), "kupa");
//        BOOST_REQUIRE_NO_THROW (beanWrapper->get ("init"));
//        BOOST_REQUIRE_EQUAL (vcast <std::string> (beanWrapper->get ("pole.name")), "ala ma kota");
}

BOOST_AUTO_TEST_CASE (testMethodVoid)
{
        Ptr <BeanWrapper> beanWrapper = std::make_shared <BeanWrapper> ();
        beanWrapper->addPlugin (new PropertyRWBeanWrapperPlugin);
        beanWrapper->addPlugin (new GetPutMethodRWBeanWrapperPlugin);
        beanWrapper->addPlugin (new MethodPlugin (MethodPlugin::IMMEDIATE_CALL));

/*--------------------------------------------------------------------------*/

        City c;
        Variant v (&c);
        Core::DebugContext ctx;

        bool err;
        beanWrapper->get (&v, "init", &err, &ctx);
        BOOST_REQUIRE (!err);
}

BOOST_AUTO_TEST_SUITE_END ();
