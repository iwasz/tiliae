/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include "container/common/Attributes.h"
#include "container/metaStructure/model/MetaObject.h"

using namespace Container;

BOOST_AUTO_TEST_SUITE (OtherTests);

BOOST_AUTO_TEST_CASE (testAttrNoParent)
{
        Attributes attributes;

        BOOST_CHECK_EQUAL (attributes.getBool (Attributes::ABSTRACT_ARGUMENT, false), false);
        BOOST_CHECK_EQUAL (attributes.getBool (Attributes::LAZYINIT_ARGUMENT), false);
        BOOST_CHECK_EQUAL (static_cast <MetaObject::Scope> (attributes.getInt (Attributes::SCOPE_ARGUMENT, false)), MetaObject::SINGLETON);

        BOOST_CHECK_EQUAL (std::string (attributes.getString (Attributes::ID_ARGUMENT, false)), "");
        BOOST_CHECK_EQUAL (std::string (attributes.getString (Attributes::CLASS_ARGUMENT, false)), "");
        BOOST_CHECK_EQUAL (std::string (attributes.getString (Attributes::PARENT_ARGUMENT, false)), "");
        BOOST_CHECK_EQUAL (std::string (attributes.getString (Attributes::INITMETHOD_ARGUMENT, false)), "");
        BOOST_CHECK_EQUAL (std::string (attributes.getString (Attributes::FACTORY_ARGUMENT, false)), "");
        BOOST_CHECK_EQUAL (std::string (attributes.getString (Attributes::EDITOR_ARGUMENT, false)), "");

        attributes.setBool (Attributes::ABSTRACT_ARGUMENT, true);
        BOOST_CHECK_EQUAL (attributes.getBool (Attributes::ABSTRACT_ARGUMENT, false), true);

        attributes.setBool (Attributes::ABSTRACT_ARGUMENT, false);
        BOOST_CHECK_EQUAL (attributes.getBool (Attributes::ABSTRACT_ARGUMENT, false), false);

        attributes.setBool (Attributes::LAZYINIT_ARGUMENT, true);
        BOOST_CHECK_EQUAL (attributes.getBool (Attributes::LAZYINIT_ARGUMENT, false), true);

        attributes.setBool (Attributes::LAZYINIT_ARGUMENT, false);
        BOOST_CHECK_EQUAL (attributes.getBool (Attributes::LAZYINIT_ARGUMENT, false), false);

        attributes.setInt (Attributes::SCOPE_ARGUMENT, MetaObject::SINGLETON);
        BOOST_CHECK_EQUAL (static_cast <MetaObject::Scope> (attributes.getInt (Attributes::SCOPE_ARGUMENT, false)), MetaObject::SINGLETON);

        attributes.setInt (Attributes::SCOPE_ARGUMENT, MetaObject::PROTOTYPE);
        BOOST_CHECK_EQUAL (static_cast <MetaObject::Scope> (attributes.getInt (Attributes::SCOPE_ARGUMENT, false)), MetaObject::PROTOTYPE);

        attributes.setInt (Attributes::SCOPE_ARGUMENT, MetaObject::BEAN);
        BOOST_CHECK_EQUAL (static_cast <MetaObject::Scope> (attributes.getInt (Attributes::SCOPE_ARGUMENT, false)), MetaObject::BEAN);

        std::string str = "test";
        attributes.setString (Attributes::ID_ARGUMENT, str.c_str ());
        BOOST_CHECK_EQUAL (std::string (attributes.getString (Attributes::ID_ARGUMENT, false)), "test");
}

BOOST_AUTO_TEST_CASE (testAttrParent)
{
        Attributes attributes;

        BOOST_CHECK_EQUAL (attributes.getBool (Attributes::ABSTRACT_ARGUMENT, true), false);
        BOOST_CHECK_EQUAL (attributes.getBool (Attributes::LAZYINIT_ARGUMENT), false);
        BOOST_CHECK_EQUAL (static_cast <MetaObject::Scope> (attributes.getInt (Attributes::SCOPE_ARGUMENT, true)), MetaObject::SINGLETON);

        BOOST_CHECK_EQUAL (std::string (attributes.getString (Attributes::ID_ARGUMENT, true)), "");
        BOOST_CHECK_EQUAL (std::string (attributes.getString (Attributes::CLASS_ARGUMENT, true)), "");
        BOOST_CHECK_EQUAL (std::string (attributes.getString (Attributes::PARENT_ARGUMENT, true)), "");
        BOOST_CHECK_EQUAL (std::string (attributes.getString (Attributes::INITMETHOD_ARGUMENT, true)), "");
        BOOST_CHECK_EQUAL (std::string (attributes.getString (Attributes::FACTORY_ARGUMENT, true)), "");
        BOOST_CHECK_EQUAL (std::string (attributes.getString (Attributes::EDITOR_ARGUMENT, true)), "");

}

BOOST_AUTO_TEST_SUITE_END ();
