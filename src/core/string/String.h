/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef _STRING_ADAPTER_TILIAE_H_
#define _STRING_ADAPTER_TILIAE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include <string>
#include <list>
#include <iostream>
#include <string>
#include <stdint.h>

#include "utf8.h"
#include "core/ApiMacro.h"

namespace Core {

/**
 * \page String String : napisy UTF-8.
 * Opis
 */

/**
 * Klasa string UTF-8.
 * \ingroup CoreAPI
 */
class TILIAE_API String {
public:

        typedef std::string::size_type size_type;
        typedef uint32_t value_type;

        typedef utf8::iterator <std::string::iterator> iterator;
        typedef utf8::iterator <std::string::const_iterator> const_iterator;

        //		typedef utf8::iterator <std::string::reverse_iterator> reverse_iterator;
        //		typedef utf8::iterator <std::string::const_reverse_iterator> const_reverse_iterator;

        static const size_type npos;

        /**
         * Konstruuje pusty string UTF-8.
         */
        String ()
        {
        }

        /**
         * Konstruuje string zawierajacy dane z parametru s. s musi byc
         * stringiem C, zakonczonym znakiem '\0'. String ten moze zawierac dane
         * zakodowane za pomoca UTF-8.
         */
        String (const char *s) :
                body (s)
        {
        }

        /**
         * Konstruuje string zawierajacy dane z parametru s. s musi byc
         * std::stringiem C++, string ten moze zawierac dane
         * zakodowane za pomoca UTF-8.
         */
        String (const std::string &s) :
                body (s)
        {
        }

        friend std::istream &operator>> (std::istream &is, Core::String &utf8_string);
        friend std::ostream &operator<< (std::ostream &o, const Core::String &s);

        /**
         * TODO Co z innymi platformami? Czy na windowsie strcoll bedzie
         * dzialalo tak samo ladnie jak pod linuxem? Zakladam sie, ze nie!
         */
        bool operator> (const String &s) const
        {
                return strcoll (body.c_str (), s.body.c_str ()) > 0;
        }

        bool operator>= (const String &s) const
        {
                return strcoll (body.c_str (), s.body.c_str ()) >= 0;
        }

        bool operator< (const String &s) const
        {
                return strcoll (body.c_str (), s.body.c_str ()) < 0;
        }

        bool operator<= (const String &s) const
        {
                return strcoll (body.c_str (), s.body.c_str ()) <= 0;
        }

        bool operator== (const String &s) const
        {
                return strcoll (body.c_str (), s.body.c_str ()) == 0;
        }

        bool operator!= (const String &s) const
        {
                return strcoll (body.c_str (), s.body.c_str ()) != 0;
        }

        int compare (const String& s) const
        {
                return strcoll (body.c_str (), s.body.c_str ());
        }

        String &operator= (const String &s)
        {
                body = s.body;
                return *this;
        }

        /**
         * Zwraca dlugosc stringa w znakach (czyli ta dlugosc
         * moze byc mniejsza lub rowna ilosci bajtow zajmowanych
         * przez string. Synonim length ();
         */
        size_type size () const
        {
                return length ();
        }

        /**
         * Zwraca dlugosc stringa w znakach (czyli ta dlugosc
         * moze byc mniejsza lub rowna ilosci bajtow zajmowanych
         * przez string. Synonim size ();
         */
        size_type length () const;

        size_type max_size () const
        {
                return body.max_size ();
        }
        size_type capacity () const
        {
                return body.capacity ();
        }

        /**
         * Sprawdza, czy napis jest pusty.
         */
        bool empty () const
        {
                return body.empty ();
        }

        // TODO iterator nie daje sie skonwertowac na const_iterator
        iterator begin ()
        {
                return iterator (body.begin (), body.begin (), body.end ());
        }
        const_iterator begin () const
        {
                return const_iterator (body.begin (), body.begin (),
                                body.end ());
        }

        iterator end ()
        {
                return iterator (body.end (), body.begin (), body.end ());
        }
        const_iterator end () const
        {
                return const_iterator (body.end (), body.begin (), body.end ());
        }

        /**
         * Działa tak samo jak at, czyli daje (przez wartość) wartość znaku na pozycji pos.
         * Zrzuca wyjątki Core::IndexOutOfBoundsException, oraz Core::InvalidCodePoint.
         * @param pos
         * @return
         */
        value_type operator[] (size_type pos) const
        {
                return at (pos);
        }

        /**
         * Daje (przez wartość) wartość znaku na pozycji pos. Zrzuca wyjątki Core::IndexOutOfBoundsException,
         * oraz Core::InvalidCodePoint.
         * @param pos
         * @return
         */
        value_type at (size_type pos) const;

        const char *c_str () const
        {
                return body.c_str ();
        }
        const char *data () const
        {
                return body.data ();
        }
        std::string &getBody () { return body; }
        std::string const &getBody () const { return body; }

        void reserve (size_type res_arg)
        {
                body.reserve (res_arg);
        }

        /**
         * Dodaje znak na koniec.
         */
        void push_back (value_type c);

        /**
         * Dopisuje podany parametr na koniec.
         * TODO Dodac wiecej wariantow - znaczy poprzeciazac.
         */
        String &append (const String &another);

        /**
         * Dziala jak append = dodaje argument na koniec.
         */
        String &operator+= (const String &another)
        {
                return append (another);
        }

        /**
         * Dziala jak push_back = dodaje argument na koniec.
         */
        String &operator+= (value_type c)
        {
                push_back (c);
                return *this;
        }

        /**
         * Czysci caly string.
         */
        void clear ()
        {
                body.clear ();
        }

        /**
         * Usuwa n znaków zaczynając od numeru i (włącznie). Jesli nie podamy
         * ostatniego parametru, lub bedzie on za duzy (tak ze w sumie erase
         * czysciloby poza koncem), to nie bedzie bledu - string zostanie
         * wyczyszczony od i do konca.
         */
        String &erase (size_type i, size_type n = npos);

        /**
         * Usuwa znak pod iteratorem i
         */
        iterator erase (const iterator &i);

        /**
         * Usuwa znaki od do. Dla przykładu mamy napis ,,zażółć gęślą jaźń''.
         * Jesli iterator a -> ó, a iterator b -> ć, to po użyciu erase (a, b)
         * dostaniemy napis ,,zażć gęślą jaźń''. Czyli znak wskazywany przez
         * b nie jest usuwany.
         */
        iterator erase (const iterator &pbegin, const iterator &pend);

        /**
         * Zwieksza lub zmienjsza rozmiar stringu. Oczywiscie jednostka,
         * w ktorej jest n, jest liczba bajtow, a nie zadnych jednostek
         * UTF-8. c jest wypelnieniem.
         */
        void resize (size_type n, char c = '\0');

        /**
         * Wstawia znak *przed* pozycja i. Zwraca referencje do
         * samego siebie.
         */
        String &insert (size_type i, value_type c);

        /**
         * Wstawia napis s *przed* pozycja i. Zwraca referencje do
         * samego siebie.
         */
        String &insert (size_type i, const String &s);

        /**
         * Wstawia znak *przed* pozycja i. Zwraca referencje do
         * samego siebie.
         */
        String &insert (const iterator &i, value_type c);

        /**
         * Przed znakiem wskazywanym przez iterator i wstawia caly
         * string z parametru ,,string''.
         */
        String &insert (const iterator &i, const String &string);

        /**
         * Dodaje dwa stringi do siebie.
         */
        friend String operator+ (const String &a, const String &b);

        /**
         * Zwraca substring o dlugosci n znakow, zaczynajac od
         * znaku o indeksie i (wlacznie).
         */
        String substr (size_type i, size_type n = npos) const;

        /**
         * Equivalent to erase(pos, n) followed by insert(pos, s). Czyli
         * podsumowując : usunie n znaków zaczynajac od pos (włącznie z tym
         * pos) i zamiast tego wstawia napis s.
         */
        String &replace (size_type pos, size_type n, const String &s);

        /**
         * Zamienia znaki poczawszy od wskazywanego przez b skonczywszy na
         * znaku przed e na ciag znakow w s.
         */
        String &replace (const iterator &b, const iterator &e, const String &s);

        /**
         * Zamienia pierwszy podany ciag znakow w stringu na drugi.
         * Oczywiscie jesli ten pierwszy jest obecny w stringu.
         * Jesli a nie wsystepuje w stringu, to nic sie nie dzieje!
         */
        String &replace (const String &a, const String &b);

        /**
         * Wyszukuje zaczynajac od znaku from. Zwraca iterator do znalezionego
         * substringa, albo end(), jesli nie udalo sie znalezc nic.
         */
        const_iterator find (const String &string, size_type from = 0) const;

        /**
         * Wyszukuje zaczynajac od znaku from. Zwraca index do znalezionego
         * substringa, albo String::npos, jesli nie udalo sie znalezc nic.
         */
        size_type indexOf (const String &string, size_type from = 0) const;

        /**
         * Sprawdza, czy podany string wystepuje w tym stringu, czy nie.
         */
        bool contains (const String &string) const;

        /**
         * Zlicza wystepowanie napisu ,,string'' w naszym stringu.
         */
        size_type count (const String &string) const;

        /**
         * Zwraca kopie tego stringa, ale wszystkie litery
         * sa zamienione na małe.
         */
        String toLower () const;

        /**
         * Zwraca kopie tego stringa, ale wszystkie litery
         * sa zamienione na wielkie.
         */
        String toUpper () const;

        /**
         *
         */
        String trimmed () const;

        /**
         *
         */
        void trim ();

private:

        void checkIndexThrow (size_type i) const;

private:

        /**
         *  Implementacja.
         */
        std::string body;

};

/*##########################################################################*/

/**
 * Wyjątek zrzucany kiedy probujemy utworzyć String z niepoprawnych
 * danych UTF8.
 */
struct TILIAE_API InvalidUTF8 {};

extern TILIAE_API String operator+ (const String &a, const String &b);

extern TILIAE_API String operator+ (const String &s, bool b);
extern TILIAE_API String operator+ (const String &s, char c);
extern TILIAE_API String operator+ (const String &s, signed char c);
extern TILIAE_API String operator+ (const String &s, unsigned char c);
extern TILIAE_API String operator+ (const String &s, double d);
extern TILIAE_API String operator+ (const String &s, long double d);
extern TILIAE_API String operator+ (const String &s, float f);
extern TILIAE_API String operator+ (const String &s, int i);
extern TILIAE_API String operator+ (const String &s, unsigned int i);
extern TILIAE_API String operator+ (const String &s, long int i);
extern TILIAE_API String operator+ (const String &s, unsigned long int i);
extern TILIAE_API String operator+ (const String &s, short int i);
extern TILIAE_API String operator+ (const String &s, unsigned short int i);
extern TILIAE_API String operator+ (const String &s, const std::string &s2);
extern TILIAE_API String operator+ (const String &s, const char *s2);

extern TILIAE_API String operator+ (bool b, const String &s);
extern TILIAE_API String operator+ (char c, const String &s);
extern TILIAE_API String operator+ (signed char c, const String &s);
extern TILIAE_API String operator+ (unsigned char c, const String &s);
extern TILIAE_API String operator+ (double d, const String &s);
extern TILIAE_API String operator+ (long double d, const String &s);
extern TILIAE_API String operator+ (float f, const String &s);
extern TILIAE_API String operator+ (int i, const String &s);
extern TILIAE_API String operator+ (unsigned int i, const String &s);
extern TILIAE_API String operator+ (long int i, const String &s);
extern TILIAE_API String operator+ (unsigned long int i, const String &s);
extern TILIAE_API String operator+ (short int i, const String &s);
extern TILIAE_API String operator+ (unsigned short int i, const String &s);
extern TILIAE_API String operator+ (const std::string &s2, const String &s);
extern TILIAE_API String operator+ (const char *s2, const String &s);

extern TILIAE_API std::ostream &operator<< (std::ostream &o, const Core::String &s);
extern TILIAE_API std::istream &operator>> (std::istream &is, Core::String &utf8_string);

} // Namespace.

#endif

