/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include "k202/K202.h"
#include "TestHelpers.h"
#include "core/variant/Variant.h"
#include "core/Typedefs.h"
#include "beanWrapper/beanWrapper/BeanWrapper.h"

BOOST_AUTO_TEST_SUITE (OperatorsTest03);
using namespace k202;
using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testLogicNegation)
{
        Ptr <K202> k202 = K202::create (Ptr <Wrapper::BeanWrapper> (Wrapper::BeanWrapper::create ()));

        TestRuntime <bool>::test (k202, "true", true);
        TestRuntime <bool>::test (k202, "!true", false);
        TestRuntime <bool>::test (k202, "!false", true);

        VariantVector paramList;
        paramList.push_back (Core::Variant (true));
        TestRuntime <bool>::test (k202, "%0", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "!%0", false, Variant (), paramList);
        TestRuntime <bool>::test (k202, "!!%0", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "!!!%0", false, Variant (), paramList);
        TestRuntime <bool>::test (k202, "!!!!%0", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "!(!(!(!%0)))", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "(!!!!%0)", true, Variant (), paramList);

        TestRuntime <bool>::test (k202, "!none", true);
        TestRuntime <bool>::test (k202, "!$!prop", true);
        TestRuntime <bool>::test (k202, "!!$!prop", false);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testLogicAnd)
{
        Ptr <K202> k202 = K202::create (Ptr <Wrapper::BeanWrapper> (Wrapper::BeanWrapper::create ()));

        TestRuntime <bool>::test (k202, "true && true", true);
        TestRuntime <bool>::test (k202, "true && false", false);
        TestRuntime <bool>::test (k202, "true && !true", false);

        TestRuntime <bool>::test (k202, "none && true", false);
        TestRuntime <bool>::test (k202, "none && none", false);
        TestRuntime <bool>::test (k202, "true && $!prop", false);
        TestRuntime <bool>::test (k202, "true && !$!prop", true);
        TestRuntime <bool>::test (k202, "!$!test && !$!prop", true);

        VariantVector paramList;
        paramList.push_back (Core::Variant (true));
        paramList.push_back (Core::Variant (false));
        paramList.push_back (Core::Variant (true));
        paramList.push_back (Core::Variant (false));

        TestRuntime <bool>::test (k202, "%0 && %0", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%0 && %2", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%0 && %1", false, Variant (), paramList);
        TestRuntime <bool>::test (k202, "!%3 && !%1", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%0 && %0 && %2", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%0 && %0 && %2 && true", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%1 && %0 && false", false, Variant (), paramList);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testLogicOr)
{
        Ptr <K202> k202 = K202::create (Ptr <Wrapper::BeanWrapper> (Wrapper::BeanWrapper::create ()));

        TestRuntime <bool>::test (k202, "true || true", true);
        TestRuntime <bool>::test (k202, "true || false", true);
        TestRuntime <bool>::test (k202, "false || true", true);
        TestRuntime <bool>::test (k202, "false || false", false);
        TestRuntime <bool>::test (k202, "true || !true", true);
        TestRuntime <bool>::test (k202, "!true || !true", false);
        TestRuntime <bool>::test (k202, "!true || true", true);

        TestRuntime <bool>::test (k202, "true || none", true);
        TestRuntime <bool>::test (k202, "none || true", true);
        TestRuntime <bool>::test (k202, "none || false", false);
        TestRuntime <bool>::test (k202, "none || none", false);
        TestRuntime <bool>::test (k202, "true || $!prop", true);
        TestRuntime <bool>::test (k202, "$!test || $!prop", false);
        TestRuntime <bool>::test (k202, "$!test || true || $!prop", true);

        VariantVector paramList;
        paramList.push_back (Core::Variant (true));
        paramList.push_back (Core::Variant (false));
        paramList.push_back (Core::Variant (true));
        paramList.push_back (Core::Variant (false));

        TestRuntime <bool>::test (k202, "%0 || %0", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%0 || %2", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%0 || %1", true , Variant (), paramList);
        TestRuntime <bool>::test (k202, "!%3 || !%1", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%1 || %1", false, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%0 || %1 || %3", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%1 || %3 || false", false, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%1 || %3 || true", true, Variant (), paramList);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testLogicEq)
{
        try {
                Ptr <K202> k202 = K202::create (Ptr <Wrapper::BeanWrapper> (Wrapper::BeanWrapper::create ()));

                TestRuntime <bool>::test (k202, "true == true", true);
                TestRuntime <bool>::test (k202, "true == false", false);

                VariantVector paramList;
                paramList.push_back (Core::Variant (12));
                paramList.push_back (Core::Variant (true));
                paramList.push_back (Core::Variant (12));
                paramList.push_back (Core::Variant (std::string ("test1")));
                paramList.push_back (Core::Variant (std::string ("lskdjfkl")));
                paramList.push_back (Core::Variant (std::string ("test1")));

                TestRuntime <bool>::test (k202, "%0 == 13", false, Variant (), paramList);
                TestRuntime <bool>::test (k202, "%0 == 12", true, Variant (), paramList);
                TestRuntime <bool>::test (k202, "%3 == 'test3'", false, Variant (), paramList);
                TestRuntime <bool>::test (k202, "%3 == 'test1'", true, Variant (), paramList);
                TestRuntime <bool>::test (k202, "%3 == 'test1' == %1", true, Variant (), paramList);

                VariantMap argsMap;
                argsMap["a"] = Core::Variant (std::string ("testA"));
                argsMap["b"] = Core::Variant (std::string ("testB"));
                argsMap["c"] = Core::Variant (std::string ("testC"));
                argsMap["d"] = Core::Variant (std::string ("testD"));
                argsMap["e"] = Core::Variant (std::string ("testA"));
                Variant vv = Core::Variant (&argsMap);

                TestRuntime <bool>::test (k202, "$a == 'testA'", true, vv);
                TestRuntime <bool>::test (k202, "'testB' == $b", true, vv);
                TestRuntime <bool>::test (k202, "$c == 'kjashfd'", false, vv);
                TestRuntime <bool>::test (k202, "$d == 'testD' == true", true, vv);
                TestRuntime <bool>::test (k202, "($a == 'testA') == true", true, vv);
                TestRuntime <bool>::test (k202, "true == ($d == 'testD')", true, vv);

                TestRuntime <bool>::test (k202, "$!prop == none", true);
                TestRuntime <bool>::test (k202, "$!prop == 1", false);
                TestRuntime <bool>::test (k202, "$!prop == true", false);
                TestRuntime <bool>::test (k202, "$!prop == false", false);
                TestRuntime <bool>::test (k202, "$!prop == 'test'", false);
                TestRuntime <bool>::test (k202, "$!prop == 12.3", false);
                TestRuntime <bool>::test (k202, "$!prop == $!test", true);

                // Segfoltuje na tym.
                TestRuntime <bool>::test (k202, "$!a.b.c.d.e == none", true);
                // k202->run ("$!a.b.c.d.e");
                //TestRuntime <bool>::test (k202, "$!asd.asd.1.32.4 == none", true);
        }
        catch (const Core::Exception &e) {
                std::cerr << e.what () << std::endl;
        }
        catch (...) {
                std::cerr << "Error" << std::endl;
        }
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testLogicNe)
{
        Ptr <K202> k202 = K202::create (Ptr <Wrapper::BeanWrapper> (Wrapper::BeanWrapper::create ()));

        TestRuntime <bool>::test (k202, "true != true", false);
        TestRuntime <bool>::test (k202, "true != false", true);
        TestRuntime <bool>::test (k202, "'a' != 'b'", true);

        VariantVector paramList;
        paramList.push_back (Core::Variant (12));
        paramList.push_back (Core::Variant (true));
        paramList.push_back (Core::Variant (12));
        paramList.push_back (Core::Variant (std::string ("test1")));
        paramList.push_back (Core::Variant (std::string ("lskdjfkl")));
        paramList.push_back (Core::Variant (std::string ("test1")));

        TestRuntime <bool>::test (k202, "%0 != 13", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%0 != 12", false, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%3 != 'test3'", true, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%3 != 'test1'", false, Variant (), paramList);
        TestRuntime <bool>::test (k202, "%3 != 'test1' != %1", true, Variant (), paramList);

        VariantMap argsMap;
        argsMap["a"] = Core::Variant (std::string ("testA"));
        argsMap["b"] = Core::Variant (std::string ("testB"));
        argsMap["c"] = Core::Variant (std::string ("testC"));
        argsMap["d"] = Core::Variant (std::string ("testD"));
        argsMap["e"] = Core::Variant (std::string ("testA"));
        Variant vv = Core::Variant (&argsMap);

        TestRuntime <bool>::test (k202, "$a != 'testA'", false, vv);
        TestRuntime <bool>::test (k202, "'testB' != $b", false, vv);
        TestRuntime <bool>::test (k202, "$c != 'kjashfd'", true, vv);
        TestRuntime <bool>::test (k202, "$d != 'testD' != true", true, vv);
        TestRuntime <bool>::test (k202, "($a != 'testA') != true", true, vv);
        TestRuntime <bool>::test (k202, "true != ($d != 'testD')", true, vv);

        TestRuntime <bool>::test (k202, "$!prop != none", false);
        TestRuntime <bool>::test (k202, "$!prop != 1", true);
        TestRuntime <bool>::test (k202, "$!prop != true", true);
        TestRuntime <bool>::test (k202, "$!prop != false", true);
        TestRuntime <bool>::test (k202, "$!prop != 'test'", true);
        TestRuntime <bool>::test (k202, "$!prop != 12.3", true);
        TestRuntime <bool>::test (k202, "$!prop != $!test", false);
        TestRuntime <bool>::test (k202, "$!asd.asd.1.32.4 != none", false);
}

BOOST_AUTO_TEST_SUITE_END ();
