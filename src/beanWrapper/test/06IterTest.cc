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
#include "../../editor/LexicalEditor.h"
#include "../misc/IndexedEditor.h"
#include "../../core/Typedefs.h"
#include "../beanWrapper/BeanWrapper.h"
#include <vector>
#include <Reflection.h>
#include "../plugins/IBeanWrapperPlugin.h"
#include "../plugins/PropertyRWBeanWrapperPlugin.h"
#include "../plugins/GetPutMethodRWBeanWrapperPlugin.h"
#include "../plugins/MethodPlugin.h"
#include "../../testHelpers/City.h"
#include "../../core/Iterator.h"
#include "../../core/Pointer.h"

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (BWTest06);
using namespace Wrapper;
using namespace Core;
using namespace Common;
using namespace Editor;

/**
 *
 */
BOOST_AUTO_TEST_CASE (testIter)
{
        Ptr <BeanWrapper> beanWrapper = BeanWrapper::create ();

/*##########################################################################*/

        StringList stringList;
        stringList.push_back ("value0");
        stringList.push_back ("value1");
        stringList.push_back ("value2");
        stringList.push_back ("value3");

        // Musi byc wariant handle, bo tylko takie da sie polimorficznie rzutować (na IList *).
        beanWrapper->setWrappedObject (Core::Variant (&stringList));

        Ptr <Core::IIterator> i = beanWrapper->iterator ("");

        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "value0");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "value1");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "value2");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "value3");
        BOOST_REQUIRE (!i->hasNext ());
}

BOOST_AUTO_TEST_CASE (testIterSlightlyMoreComplicated)
{
        Ptr <BeanWrapper> beanWrapper = BeanWrapper::create ();

/*##########################################################################*/

        StringList stringList;
        stringList.push_back ("value0");
        stringList.push_back ("value1");
        stringList.push_back ("value2");
        stringList.push_back ("value3");

        VariantList vList;
        vList.push_back (Variant ("string"));
        vList.push_back (Variant (stringList)); // Kopia stringList

        // Musi byc wariant handle, bo tylko takie da sie polimorficznie rzutować (na IList *).
        beanWrapper->setWrappedObject (Core::Variant (&vList));

        Ptr <Core::IIterator> i = beanWrapper->iterator ("1");

        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "value0");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "value1");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "value2");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "value3");
        BOOST_REQUIRE (!i->hasNext ());
}

BOOST_AUTO_TEST_CASE (testIterComplex)
{
        Ptr <BeanWrapper> beanWrapper = BeanWrapper::create ();

/*##########################################################################*/

        Ptr <StringVector> stringList = boost::make_shared <StringVector> ();
        stringList->push_back ("value0");
        stringList->push_back ("value1");
        stringList->push_back ("value2");
        stringList->push_back ("value3");

        Ptr <VariantList> vList = boost::make_shared <VariantList> ();
        vList->push_back (Variant ("string"));
        vList->push_back (Variant (stringList));

        Ptr <VariantMap> vMap = boost::make_shared <VariantMap> ();
        (*vMap)["key1"] = Variant (vList);

        Ptr <VariantMap> vMap2 = boost::make_shared <VariantMap> ();
        vMap2->operator [] ("key2") = Variant (vMap);

        // Musi byc wariant handle, bo tylko takie da sie polimorficznie rzutować (na IList *).
        beanWrapper->setWrappedObject (Core::Variant (vMap2));

        Ptr <Core::IIterator> i = beanWrapper->iterator ("key2.key1.1");

        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "value0");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "value1");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "value2");
        BOOST_REQUIRE (i->hasNext ());
        BOOST_REQUIRE_EQUAL (vcast <std::string> (i->next ()), "value3");
        BOOST_REQUIRE (!i->hasNext ());
}

BOOST_AUTO_TEST_SUITE_END ();
