/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef WITH_CORE_STRING
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "core/string/String.h"

BOOST_AUTO_TEST_SUITE (StringTest08);

using namespace boost;
using namespace Core;

/**
 * Tekst testowy : zażółć gęślą jaźń, ZAŻÓŁĆ GĘŚLĄ JAŹŃ. Wartości
 * decymalne to :
 * z = 122, a = 97, ż = 380, ó = 243, ł = 322, ć = 263, spce = 32,
 * g = 103, ę = 281, ś = 347, l = 108, ą = 261, j = 106, ź = 378,
 * ń = 324, comma = 44, Z = 90, A = 65, Ż = 379, Ó = 211, Ł = 321,
 * Ć = 262, G = 71, Ę = 280, Ś = 346, L = 76, Ą = 260, J = 74, Ź = 377,
 * Ń = 323.
 */
const char *testString = "\x7A\x61\xC5\xBC\xC3\xB3\xC5\x82\xC4\x87\x20\x67\xC4\x99\xC5\x9B\x6C\xC4\x85\x20\x6A\x61\xC5\xBA\xC5\x84\x2C\x20\x5A\x41\xC5\xBB\xC3\x93\xC5\x81\xC4\x86\x20\x47\xC4\x98\xC5\x9A\x4C\xC4\x84\x20\x4A\x41\xC5\xB9\xC5\x83";

/**
 * Testuje jedynie, czy da sie utworzyc i skasowac pbiekt typu
 * String.
 */
BOOST_AUTO_TEST_CASE (testCreateAndDestroy)
{
        String *s = new String (testString);
        delete s;
}

/**
 * Ewentualnie dodatkowe testy : compare, operator <, >, !=, ==, sortowanie.
 */

/**
 * Testuje iteratory i funkcje, ktore je swracaja (czyli begin, end, rbegin, rend).
 */
BOOST_AUTO_TEST_CASE (testIterators)
{
        String s = testString;
        String::iterator i = s.begin ();

        BOOST_REQUIRE_EQUAL (*i++, 122U);
        BOOST_REQUIRE_EQUAL (*i++, 97U);
        BOOST_REQUIRE_EQUAL (*i++, 380U);
        BOOST_REQUIRE_EQUAL (*i++, 243U);
        BOOST_REQUIRE_EQUAL (*i++, 322U);
        BOOST_REQUIRE_EQUAL (*i++, 263U);
        BOOST_REQUIRE_EQUAL (*i++, 32U);
        BOOST_REQUIRE_EQUAL (*i++, 103U);
        BOOST_REQUIRE_EQUAL (*i++, 281U);
        BOOST_REQUIRE_EQUAL (*i++, 347U);
        BOOST_REQUIRE_EQUAL (*i++, 108U);
        BOOST_REQUIRE_EQUAL (*i++, 261U);
        BOOST_REQUIRE_EQUAL (*i++, 32U);
        BOOST_REQUIRE_EQUAL (*i++, 106U);
        BOOST_REQUIRE_EQUAL (*i++, 97U);
        BOOST_REQUIRE_EQUAL (*i++, 378U);
        BOOST_REQUIRE_EQUAL (*i++, 324U);
        BOOST_REQUIRE_EQUAL (*i++, 44U);
        BOOST_REQUIRE_EQUAL (*i++, 32U);
        BOOST_REQUIRE_EQUAL (*i++, 90U);
        BOOST_REQUIRE_EQUAL (*i++, 65U);
        BOOST_REQUIRE_EQUAL (*i++, 379U);
        BOOST_REQUIRE_EQUAL (*i++, 211U);
        BOOST_REQUIRE_EQUAL (*i++, 321U);
        BOOST_REQUIRE_EQUAL (*i++, 262U);
        BOOST_REQUIRE_EQUAL (*i++, 32U);
        BOOST_REQUIRE_EQUAL (*i++, 71U);
        BOOST_REQUIRE_EQUAL (*i++, 280U);
        BOOST_REQUIRE_EQUAL (*i++, 346U);
        BOOST_REQUIRE_EQUAL (*i++, 76U);
        BOOST_REQUIRE_EQUAL (*i++, 260U);
        BOOST_REQUIRE_EQUAL (*i++, 32U);
        BOOST_REQUIRE_EQUAL (*i++, 74U);
        BOOST_REQUIRE_EQUAL (*i++, 65U);
        BOOST_REQUIRE_EQUAL (*i++, 377U);
        BOOST_REQUIRE_EQUAL (*i++, 323U);

        i = s.end ();

        BOOST_REQUIRE_EQUAL (*(--i), 323U);
        BOOST_REQUIRE_EQUAL (*(--i), 377U);
        BOOST_REQUIRE_EQUAL (*(--i), 65U);
        BOOST_REQUIRE_EQUAL (*(--i), 74U);
        BOOST_REQUIRE_EQUAL (*(--i), 32U);
        BOOST_REQUIRE_EQUAL (*(--i), 260U);
        BOOST_REQUIRE_EQUAL (*(--i), 76U);
        BOOST_REQUIRE_EQUAL (*(--i), 346U);
        BOOST_REQUIRE_EQUAL (*(--i), 280U);
        BOOST_REQUIRE_EQUAL (*(--i), 71U);
        BOOST_REQUIRE_EQUAL (*(--i), 32U);
        BOOST_REQUIRE_EQUAL (*(--i), 262U);
        BOOST_REQUIRE_EQUAL (*(--i), 321U);
        BOOST_REQUIRE_EQUAL (*(--i), 211U);
        BOOST_REQUIRE_EQUAL (*(--i), 379U);
        BOOST_REQUIRE_EQUAL (*(--i), 65U);
        BOOST_REQUIRE_EQUAL (*(--i), 90U);
        BOOST_REQUIRE_EQUAL (*(--i), 32U);
        BOOST_REQUIRE_EQUAL (*(--i), 44U);
        BOOST_REQUIRE_EQUAL (*(--i), 324U);
        BOOST_REQUIRE_EQUAL (*(--i), 378U);
        BOOST_REQUIRE_EQUAL (*(--i), 97U);
        BOOST_REQUIRE_EQUAL (*(--i), 106U);
        BOOST_REQUIRE_EQUAL (*(--i), 32U);
        BOOST_REQUIRE_EQUAL (*(--i), 261U);
        BOOST_REQUIRE_EQUAL (*(--i), 108U);
        BOOST_REQUIRE_EQUAL (*(--i), 347U);
        BOOST_REQUIRE_EQUAL (*(--i), 281U);
        BOOST_REQUIRE_EQUAL (*(--i), 103U);
        BOOST_REQUIRE_EQUAL (*(--i), 32U);
        BOOST_REQUIRE_EQUAL (*(--i), 263U);
        BOOST_REQUIRE_EQUAL (*(--i), 322U);
        BOOST_REQUIRE_EQUAL (*(--i), 243U);
        BOOST_REQUIRE_EQUAL (*(--i), 380U);
        BOOST_REQUIRE_EQUAL (*(--i), 97U);
        BOOST_REQUIRE_EQUAL (*(--i), 122U);
}

/**
 * Testuje operator indeksowania [], oraz metode at, bo ona
 * go implementuje.
 */
BOOST_AUTO_TEST_CASE (testRandomAccess)
{
        String s = testString;
        int i = 0;

        BOOST_REQUIRE_EQUAL (s[i++], 122U);
        BOOST_REQUIRE_EQUAL (s[i++], 97U);
        BOOST_REQUIRE_EQUAL (s[i++], 380U);
        BOOST_REQUIRE_EQUAL (s[i++], 243U);
        BOOST_REQUIRE_EQUAL (s[i++], 322U);
        BOOST_REQUIRE_EQUAL (s[i++], 263U);
        BOOST_REQUIRE_EQUAL (s[i++], 32U);
        BOOST_REQUIRE_EQUAL (s[i++], 103U);
        BOOST_REQUIRE_EQUAL (s[i++], 281U);
        BOOST_REQUIRE_EQUAL (s[i++], 347U);
        BOOST_REQUIRE_EQUAL (s[i++], 108U);
        BOOST_REQUIRE_EQUAL (s[i++], 261U);
        BOOST_REQUIRE_EQUAL (s[i++], 32U);
        BOOST_REQUIRE_EQUAL (s[i++], 106U);
        BOOST_REQUIRE_EQUAL (s[i++], 97U);
        BOOST_REQUIRE_EQUAL (s[i++], 378U);
        BOOST_REQUIRE_EQUAL (s[i++], 324U);
        BOOST_REQUIRE_EQUAL (s[i++], 44U);
        BOOST_REQUIRE_EQUAL (s[i++], 32U);
        BOOST_REQUIRE_EQUAL (s[i++], 90U);
        BOOST_REQUIRE_EQUAL (s[i++], 65U);
        BOOST_REQUIRE_EQUAL (s[i++], 379U);
        BOOST_REQUIRE_EQUAL (s[i++], 211U);
        BOOST_REQUIRE_EQUAL (s[i++], 321U);
        BOOST_REQUIRE_EQUAL (s[i++], 262U);
        BOOST_REQUIRE_EQUAL (s[i++], 32U);
        BOOST_REQUIRE_EQUAL (s[i++], 71U);
        BOOST_REQUIRE_EQUAL (s[i++], 280U);
        BOOST_REQUIRE_EQUAL (s[i++], 346U);
        BOOST_REQUIRE_EQUAL (s[i++], 76U);
        BOOST_REQUIRE_EQUAL (s[i++], 260U);
        BOOST_REQUIRE_EQUAL (s[i++], 32U);
        BOOST_REQUIRE_EQUAL (s[i++], 74U);
        BOOST_REQUIRE_EQUAL (s[i++], 65U);
        BOOST_REQUIRE_EQUAL (s[i++], 377U);
        BOOST_REQUIRE_EQUAL (s[i++], 323U);
}

/**
 * Testuje metode length ()
 */
BOOST_AUTO_TEST_CASE (testLengthMethod)
{
        String s = testString;
        BOOST_REQUIRE_EQUAL (s.length (), 36U);

        s = "";
        BOOST_REQUIRE_EQUAL (s.length (), 0U);

        s = "a";
        BOOST_REQUIRE_EQUAL (s.length (), 1U);
}

/**
 * Testuje metode (metody?) push_back. Nie do konca
 * dobry jest ten test, bo sprawdzenie jest robione za pomoca
 * length i operatora [], wiec jesli te metody zle dzialaja,
 * to test bedzie nierzetelny.
 */
BOOST_AUTO_TEST_CASE (testPushBack)
{
        String s;
        String data = testString;

        s.push_back ('a');

        BOOST_REQUIRE_EQUAL (s.length (), 1U);
        BOOST_REQUIRE_EQUAL (s[0], 97U);

        s.push_back (data[2]); //ż
        BOOST_REQUIRE_EQUAL (s.length (), 2U);
        BOOST_REQUIRE_EQUAL (s[1], 380U);
}

/**
 * testuje rozliczne metody append. Te metody dzialaja tak jak
 * push_back, ale potrafia dodawac cale stringi zamiast pojedynczych
 * znakow.
 */
BOOST_AUTO_TEST_CASE (testAppend)
{
        String s;
        String data = testString;

        s.append (data);
        BOOST_REQUIRE_EQUAL (s, data);

        String s2;
        s2.append ("lala");
        BOOST_REQUIRE_EQUAL (s2, "lala");
}

/**
 * Testuje operatory +=, ktore sa zaimplementowane za pomoca
 * append, wiec wiele nie wnosi.
 */
BOOST_AUTO_TEST_CASE (testOperatorPlusEq)
{
        String s;
        String data = testString;

        s += data;
        BOOST_REQUIRE_EQUAL (s, data);

        String s2;
        s2 += "lala";
        BOOST_REQUIRE_EQUAL (s2, "lala");
}

/**
 * Testuje clear
 */
BOOST_AUTO_TEST_CASE (testClear)
{
        String s = "bakldfjsklajdgfkldhglire";
        s.clear ();
        BOOST_REQUIRE_EQUAL (s, "");
}

/**
 * Testuje rozne metody erase z jednym iteratorem.
 */
BOOST_AUTO_TEST_CASE (testErase)
{
        String s = testString;

        String::iterator i = s.begin (); // i wskazuje na ,,z''
        i++; // ,,a''
        i++; // ,,ż''
        i++; // ,,ó''
        s.erase (i);

        i = s.begin ();

        BOOST_REQUIRE_EQUAL (*i++, 122U);
        BOOST_REQUIRE_EQUAL (*i++, 97U);
        BOOST_REQUIRE_EQUAL (*i++, 380U);
        BOOST_REQUIRE_EQUAL (*i++, 322U);

        // Test na end - podajemy end jako znak do usuniecia.

        i = s.end ();
        String::iterator j = s.erase (i);
        BOOST_REQUIRE (j == s.end ());
}

/**
 * Testuje metode erase z dwoma iteratorami.
 */
BOOST_AUTO_TEST_CASE (testErase2)
{
        String s = testString;

        String::iterator i = s.begin (); // i wskazuje na ,,z''
        i++; // ,,a''
        i++; // ,,ż''
        i++; // ,,ó''
        String::iterator j = i;
        j++; // ł
        j++; // ć
        s.erase (i, j);

        i = s.begin ();

        BOOST_REQUIRE_EQUAL (*i++, 122U);
        BOOST_REQUIRE_EQUAL (*i++, 97U);
        BOOST_REQUIRE_EQUAL (*i++, 380U);
//      BOOST_REQUIRE_EQUAL (*i++, 243U);
//      BOOST_REQUIRE_EQUAL (*i++, 322U);
        BOOST_REQUIRE_EQUAL (*i++, 263U); // ć
        BOOST_REQUIRE_EQUAL (*i++, 32U);
        BOOST_REQUIRE_EQUAL (*i++, 103U);
}

/**
 * Testuje metode erase z dwoma liczbami calkowitymi jako
 * parametry.
 * TODO testowac warunki brzegowe!!!
 */
BOOST_AUTO_TEST_CASE (testErase3)
{
        String s = testString;

        // Wytnij 2 znaki zaczynając (czyli łącznie z) od ó.
        s.erase (3, 2);

        String::iterator i = s.begin ();

        BOOST_REQUIRE_EQUAL (*i++, 122U);
        BOOST_REQUIRE_EQUAL (*i++, 97U);
        BOOST_REQUIRE_EQUAL (*i++, 380U);
//      BOOST_REQUIRE_EQUAL (*i++, 243U);
//      BOOST_REQUIRE_EQUAL (*i++, 322U);
        BOOST_REQUIRE_EQUAL (*i++, 263U); // ć
        BOOST_REQUIRE_EQUAL (*i++, 32U);
        BOOST_REQUIRE_EQUAL (*i++, 103U);
}

/**
 * Testuje insert z iteratorem i jednym znakiem.
 * Znak powinen byc wstawiany PRZED znakiem wskazywanym
 * przez iterator.
 */
BOOST_AUTO_TEST_CASE (testInsert)
{
        String s = testString;

        String::iterator i = s.begin (); // i wskazuje na ,,z''
        i++; // ,,a''
        i++; // ,,ż''
        i++; // ,,ó''

        // Wstaw ,,a'' przed ó
        s.insert (i, 'a');

        i = s.begin ();

        BOOST_REQUIRE_EQUAL (*i++, 122U);
        BOOST_REQUIRE_EQUAL (*i++, 97U);
        BOOST_REQUIRE_EQUAL (*i++, 380U);
        BOOST_REQUIRE_EQUAL (*i++, 97U); // znow ,,a''
        BOOST_REQUIRE_EQUAL (*i++, 243U);
        BOOST_REQUIRE_EQUAL (*i++, 322U);
        BOOST_REQUIRE_EQUAL (*i++, 263U); // ć

        /*
         * Nie mozna drugi raz insertowac z tym samym iteratorem,
         * bo sie inwaliduje ten iterator. Trzeba iterator stworzyc
         * jeszcze raz i ustawic od nowa:
         */
        //s.insert (i, 'a');
        i = s.begin ();
        i++; // i -> ,,a''
        i++; // i -> ,,ż''
        i++; // i -> ,,a''
        i++; // i -> ,,ó''
        i++; // i -> ,,ł''

        // Wstaw ,,b'' przed ł
        s.insert (i, 'b');
        i = s.begin ();

        BOOST_REQUIRE_EQUAL (*i++, 122U); // z
        BOOST_REQUIRE_EQUAL (*i++, 97U);  // z
        BOOST_REQUIRE_EQUAL (*i++, 380U); // ż
        BOOST_REQUIRE_EQUAL (*i++, 97U);  // znow ,,a''
        BOOST_REQUIRE_EQUAL (*i++, 243U); // ó
        BOOST_REQUIRE_EQUAL (*i++, 98U);  // a tu ,,b''
        BOOST_REQUIRE_EQUAL (*i++, 322U); // ł
        BOOST_REQUIRE_EQUAL (*i++, 263U); // ć

        i = s.end ();
        // Wstaw ,,c'' przed end, czyli na samym koncu!
        s.insert (i, 'c');
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testInsert2)
{
        String s = testString;

        String::iterator i = s.begin (); // i wskazuje na ,,z''
        i++; // ,,a''
        i++; // ,,ż''
        i++; // ,,ó''

        // Wstaw ,,żaba'' przed ó
        s.insert (i, "żaba");

        i = s.begin ();

        BOOST_REQUIRE_EQUAL (*i++, 122U); // z
        BOOST_REQUIRE_EQUAL (*i++, 97U);  // a
        BOOST_REQUIRE_EQUAL (*i++, 380U); // ż
        BOOST_REQUIRE_EQUAL (*i++, 380U);  // ż
        BOOST_REQUIRE_EQUAL (*i++, 97U); // a
        BOOST_REQUIRE_EQUAL (*i++, 98U); // b
        BOOST_REQUIRE_EQUAL (*i++, 97U); // a

        s = "ża";
        s.insert (s.end (), "żaba");
        BOOST_REQUIRE_EQUAL (s, "żażaba");
}

/**
 * Test inserta wstawiajacego pojedyncze znaki i indeksowanego
 * nie iteratorem, ale liczba calkowta (insert (3, 'a')).
 */
BOOST_AUTO_TEST_CASE (testInsert3)
{
        String s = testString;

        // Wstaw ,,a'' przed 4 tym znakiem (numeracja od 0, wiec 3), czyli przed ó
        s.insert (3, 'a');

        String::iterator i = s.begin ();

        BOOST_REQUIRE_EQUAL (*i++, 122U); // z
        BOOST_REQUIRE_EQUAL (*i++, 97U);  // a
        BOOST_REQUIRE_EQUAL (*i++, 380U); // ż
        BOOST_REQUIRE_EQUAL (*i++, 97U);  // a

        s = "ża";
        s.insert (2, 'b');
        s.insert (3, 'a');
        BOOST_REQUIRE_EQUAL (s, "żaba");

#if defined (TEST_OVERFLOW)
        bool caught = false;
        try {
                s.insert (s.length () + 1, 'a');
        }
        catch (Core::IndexOutOfBoundsException) {
                caught = true;
        }
        BOOST_REQUIRE_EQUAL (caught);
#endif
}

/**
 * Test inserta wstawiajacego caĸłe stringi i indeksowanego
 * nie iteratorem, ale liczba calkowta (insert (3, "żabaółć")).
 */
BOOST_AUTO_TEST_CASE (testInsert4)
{
        String s = testString;

        // Wstaw ,,żaba'' przed 4 tym znakiem (numeracja od 0, wiec 3), czyli przed ó
        s.insert (3, "żaba");

        String::iterator i = s.begin ();

        BOOST_REQUIRE_EQUAL (*i++, 122U); // z
        BOOST_REQUIRE_EQUAL (*i++, 97U);  // a
        BOOST_REQUIRE_EQUAL (*i++, 380U); // ż
        BOOST_REQUIRE_EQUAL (*i++, 380U);  // ż
        BOOST_REQUIRE_EQUAL (*i++, 97U); // a
        BOOST_REQUIRE_EQUAL (*i++, 98U); // b
        BOOST_REQUIRE_EQUAL (*i++, 97U); // a

        s = "ża";
        s.insert (2, "baabaż");
        BOOST_REQUIRE_EQUAL (s, "żabaabaż");

#if defined (TEST_OVERFLOW)
        bool caught = false;
        try {
                s.insert (s.length () + 1, "baabaż");
        }
        catch (Core::IndexOutOfBoundsException) {
                caught = true;
        }
        BOOST_REQUIRE_EQUAL (caught);
#endif
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testOperatorPlus)
{
        String s1 = testString;
        String s2 = testString;

        String s3 = s1 + s2;

        BOOST_REQUIRE_EQUAL (s3[36], 122U); // z
        BOOST_REQUIRE_EQUAL (s3[71], 323U); // Ń
}

/**
 * substr.
 */
BOOST_AUTO_TEST_CASE (testSubstr)
{
        String s1 = testString;

        String s2 = s1.substr (0, 3);
        BOOST_REQUIRE_EQUAL (s2, "zaż");

        s2 = s1.substr (2, 4);
        BOOST_REQUIRE_EQUAL (s2, "żółć");

        s2 = s1.substr (4, 0);
        BOOST_REQUIRE_EQUAL (s2, "");

#if defined (TEST_OVERFLOW)
        bool caught = false;
        try {
                s2 = s1.substr (47655, 0);
                BOOST_REQUIRE_EQUAL (s2);
        }
        catch (Core::IndexOutOfBoundsException) {
                caught = true;
        }
        BOOST_REQUIRE_EQUAL (caught);
#endif

        // A tu test z jednym parametrem. Powinno zwrocic strnga od 1 do konca.
        s2 = s1.substr (1);
        BOOST_REQUIRE_EQUAL (s2, "ażółć gęślą jaźń, ZAŻÓŁĆ GĘŚLĄ JAŹŃ");

        // A tu kolejny test, warunek brzegowy : dajemy długosc rowna dlugosci stringa
        s2 = s1.substr (0, s1.length ());
        BOOST_REQUIRE_EQUAL (s2, s1);

        s2 = s1.substr (0, s1.length () + 1);
        BOOST_REQUIRE_EQUAL (s2, s1);

        s2 = s1.substr (0, s1.length () + 100);
        BOOST_REQUIRE_EQUAL (s2, s1);
}

/**
 * replace - wariant z indeksami od + N, oraz
 * stringiem, ktory wklejamy zamiast.
 */
BOOST_AUTO_TEST_CASE (testReplace)
{
        String s1 = testString;

        s1.replace (1, 34, "asŁO");
        BOOST_REQUIRE_EQUAL (s1, "zasŁOŃ");
}

/**
 * Drugi warian replace. Podajemy dwa iteratory i on podmienia.
 */
BOOST_AUTO_TEST_CASE (testReplace2)
{
        String s1 = testString;

        String::iterator b = s1.begin ();
        String::iterator e = s1.end ();

        b++;
        e--;

        s1.replace (b, e, "asŁO");
        BOOST_REQUIRE_EQUAL (s1, "zasŁOŃ");
}

/**
 * To jest test najfajniejszego replace - takiego, ktore
 * zamienia jeden string na drugi.
 */
BOOST_AUTO_TEST_CASE (testReplace3)
{
        String s = "żółcień koszelinowo cyjanowo pruska";

        s.replace ("koszelin", "wanili").replace ("pru", "cze").replace ("kupa", "siku");

        BOOST_REQUIRE_EQUAL (s, "żółcień waniliowo cyjanowo czeska");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testIndexOf)
{
        String s1 = testString;

        String::size_type i = s1.indexOf ("GĘŚ");
        BOOST_REQUIRE_EQUAL (i, 26U);

        i = s1.indexOf ("zażół");
        BOOST_REQUIRE_EQUAL (i, 0U);

        i = s1.indexOf ("zażół", 20);
        BOOST_REQUIRE_EQUAL (i, String::npos);

        i = s1.indexOf ("a", 0);
        BOOST_REQUIRE_EQUAL (i, 1U);

        i = s1.indexOf ("a", s1.length () + 1);
        BOOST_REQUIRE_EQUAL (i, String::npos);
}

/**
 * TODO kiedy bedzie konwersja iterator do const_iterator, to to zacznie
 * sie kompilowac.
 *
 * Chyba jakoś źle używam utf8::iterator, albo on się poprostu do tego nie
 * nadaje. W wolnej chwili możnaby to poprawić.
 */
BOOST_AUTO_TEST_CASE (testFind)
{
//      String s1 = testString;
//
//      String::const_iterator i = s1.find ("zażół");
//      BOOST_REQUIRE (i == s1.begin ());
//
//      i++;
//      i++;
//      i++;
//
//      String::const_iterator j = s1.find ("ółć", 2);
//      BOOST_REQUIRE (j == i);
//
//      i = s1.find ("zażół", 20);
//      BOOST_REQUIRE (i == s1.end ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testContains)
{
        String s = testString;
        BOOST_REQUIRE (s.contains ("JAŹŃ"));
        BOOST_REQUIRE (s.contains ("jaźń"));
        BOOST_REQUIRE (s.contains ("ZAŻÓŁ"));
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testCount)
{
        String s = testString;

        BOOST_REQUIRE_EQUAL (s.count ("a"), 2U);

        s = "łąłąłąłąłą";

        BOOST_REQUIRE_EQUAL (s.count ("łą"), 5U);
        BOOST_REQUIRE_EQUAL (s.count ("kupa"), 0U);
        BOOST_REQUIRE_EQUAL (s.count ("897689678967896986897"), 0U);
        // Gupie to, ale tak dziala std::string::find - kiedy podasz "", to znajduje co znak.
        BOOST_REQUIRE_EQUAL (s.count (""), 11U);
}

/**
 * Testy operatorów + z roznymi dziwnymi typami calkowitymi i rzeczywistymi,
 * oraz posrednio testy metody from, ktora implementuje te operatory.
 */
BOOST_AUTO_TEST_CASE (testFrom)
{
        BOOST_REQUIRE_EQUAL (String ("test") + 1, "test1");
        BOOST_REQUIRE_EQUAL (String ("test-") + true, "test-1");
        BOOST_REQUIRE_EQUAL (String ("test-") + (bool)0, "test-0");
        BOOST_REQUIRE_EQUAL (String ("test-") + 'a', "test-a");
        BOOST_REQUIRE_EQUAL (String ("test-") + 123.456, "test-123.456");
        BOOST_REQUIRE_EQUAL (String ("test-") + (short)1, "test-1");

        BOOST_REQUIRE_EQUAL (1 + String ("test"), "1test");
        BOOST_REQUIRE_EQUAL (true + String ("-test"), "1-test");
        BOOST_REQUIRE_EQUAL ((bool)0 + String ("-test"), "0-test");
        BOOST_REQUIRE_EQUAL ('a' + String ("-test"), "a-test");
        BOOST_REQUIRE_EQUAL (123.456 + String ("-test"), "123.456-test");
        BOOST_REQUIRE_EQUAL ((short)-1 + String ("-test"), "-1-test");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testTolowerToupper)
{
        String s = "zażółć gęślą jaźń";

        /*
         * Bez tego, lub tego drugiego nie działa. Locale ustala między innymi takie rzeczy
         * jak colation order, i inne operacje na znakach. Moje domyślne locale to en_EN,
         * więc bez tego nie działa.
         */
        setlocale (LC_ALL, "en_US.UTF-8");
        // setlocale (LC_ALL, "pl_PL.UTF-8");

        // std::cerr << "[" << s.toUpper () << "]" << std::endl;
        BOOST_REQUIRE_EQUAL (s.toUpper (), "ZAŻÓŁĆ GĘŚLĄ JAŹŃ");

        s = "ZAŻÓŁĆ GĘŚLĄ JAŹŃ";

        BOOST_REQUIRE_EQUAL (s.toLower (), "zażółć gęślą jaźń");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testTrim)
{
        String s = "     \t\t  zażółć gęślą jaźń\t\t     ";
        BOOST_REQUIRE_EQUAL (s.trimmed (), "zażółć gęślą jaźń");
}

/**
 * Testuje metode String::at, oraz czy poprawnie zrzuca ona
 * wyjatek, kiedy index jest poza zakresem.
 */
BOOST_AUTO_TEST_CASE (testAt)
{
        String s = testString;
        int i = 0;

        BOOST_REQUIRE_EQUAL (s.at (i++), 122U);
        BOOST_REQUIRE_EQUAL (s.at (i++), 97U);
        BOOST_REQUIRE_EQUAL (s.at (i++), 380U);
        BOOST_REQUIRE_EQUAL (s.at (i++), 243U);
        BOOST_REQUIRE_EQUAL (s.at (i++), 322U);
        BOOST_REQUIRE_EQUAL (s.at (i++), 263U);
        BOOST_REQUIRE_EQUAL (s.at (i++), 32U);
        BOOST_REQUIRE_EQUAL (s.at (i++), 103U);

#if defined (TEST_OVERFLOW)
        bool caught = false;
        try {
                s.at (9878);
        }
        catch (Core::IndexOutOfBoundsException) {
                caught = true;
        }
        BOOST_REQUIRE_EQUAL (caught);

        caught = false;
        try {
                s.at (-12);
        }
        catch (Core::IndexOutOfBoundsException) {
                caught = true;
        }
        BOOST_REQUIRE_EQUAL (caught);
#endif
}

BOOST_AUTO_TEST_SUITE_END ();
#endif
