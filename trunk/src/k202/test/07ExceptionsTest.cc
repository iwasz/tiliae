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
#include "../Exceptions.h"
#include "../../testHelpers/Bar.h"
#include "../../core/variant/Variant.h"
#include "../compiler/Compiler.h"

BOOST_AUTO_TEST_SUITE (ExceptionsTest07);
using namespace k202;
using namespace Core;

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testExceptions)
{
        Ptr <K202> k202 = K202::create ();

        Bar bar = Bar (Variant ());
        Variant vv = Core::Variant (&bar);

        BOOST_REQUIRE_THROW ((k202->run ("kjshgfdkja")), SyntaxErrorException);
        BOOST_REQUIRE_THROW ((k202->run ("%a")), SyntaxErrorException);

        // Nie ma w ogóle obiketu domenowego, nie ma skąd wyciągnąć g.
        BOOST_REQUIRE_THROW ((k202->run ("$g")), RuntimeException);
        BOOST_REQUIRE_THROW ((k202->run ("$g$")), SyntaxErrorException);

        // Nie podano parametór, a zarządano placeholdera.
        BOOST_REQUIRE_THROW ((k202->run ("%1")), RuntimeException);

        // Pośredniku oczekiwane jest instruction, kodu nie kończymy średnikiem.
        BOOST_REQUIRE_THROW ((k202->run ("true;")), SyntaxErrorException);
        BOOST_REQUIRE_THROW ((k202->run ("!#")), SyntaxErrorException);

        StringMap mapa;
        Variant domain = Core::Variant (&mapa);

        BOOST_REQUIRE_THROW ((k202->run ("$p = #", domain)), SyntaxErrorException);
        BOOST_REQUIRE_NO_THROW ((k202->run ("$p = 'test'", domain)));

        BOOST_REQUIRE_THROW ((k202->run ("$p == #", domain)), SyntaxErrorException);
        BOOST_REQUIRE_THROW ((k202->run ("$p != #", domain)), SyntaxErrorException);
        BOOST_REQUIRE_THROW ((k202->run ("$p && #", domain)), SyntaxErrorException);
        BOOST_REQUIRE_THROW ((k202->run ("$p || #", domain)), SyntaxErrorException);

        BOOST_REQUIRE_THROW ((k202->run ("${} = 'test'", domain)), RuntimeException);
}

BOOST_AUTO_TEST_SUITE_END ();
