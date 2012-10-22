/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef WITH_CORE_STRING
#include <wctype.h>
#include <sstream>
#include <boost/lexical_cast.hpp>

#include "String.h"
#include "core/Exception.h"

namespace Core {
using namespace boost;

const String::size_type String::npos = std::string::npos;

/**
 * Uzywane przy konwersjach z glibc w stylu strtol etc.
 */
const unsigned int MAX_CHARS = 256;

String::value_type String::at (size_type pos) const
{
        checkIndexThrow (pos);
	std::string::const_iterator b = body.begin ();
        utf8::unchecked::advance (b, pos);
        return utf8::unchecked::peek_next(b);
}

/****************************************************************************/

String::size_type String::length () const
{
        return utf8::unchecked::distance (body.begin (), body.end ());
}

/****************************************************************************/

void String::push_back (value_type c)
{
	/*
	 * Wstaw przed iteratorem end (). Ale end wskazuje na cos po ostatnim
	 * znaku, wiec to oznacza, ze wstaw c na sam koniec!
	 */
	insert (end (), c);
}

/****************************************************************************/

String &String::append (const String &another)
{
	body += another.body;
	return *this;
}

/****************************************************************************/

String &String::erase (size_type i, size_type n)
{
	std::string::const_iterator b = body.begin ();

	checkIndexThrow (i);
        utf8::unchecked::advance (b, i);

	size_type i2 = b - body.begin ();
	std::string::const_iterator b2 = b;

	size_type len = length (), num = n;
	if (i + num > len || num == npos) {
	        num = len - i;
	}

        utf8::unchecked::advance (b2, num);

	size_type n2 = b2 - b;
	body.erase (i2, n2);
	return *this;
}

/****************************************************************************/

String::iterator String::erase (const iterator &i)
{
	iterator a = i;

	if (a == end ()) {
		return end ();
	}

	iterator b = i;
	b++;

	return iterator (body.erase (a.base (), b.base ()), body.begin (), body.end ());
}

/****************************************************************************/

String::iterator String::erase (const iterator &a, const iterator &b)
{
	if (a == end ()) {
		return end ();
	}

	return iterator (body.erase (a.base (), b.base ()), body.begin (), body.end ());
}

/****************************************************************************/

void String::resize (size_type n, char c)
{
	body.resize (n, c);
}

/****************************************************************************/

String &String::insert (size_type i, value_type c)
{
	std::string::iterator b = body.begin ();
        checkIndexThrow (i);
	utf8::unchecked::advance (b, i);

	std::insert_iterator <std::string> j (body, b);
	utf8::unchecked::append (c, j);
	return *this;
}

/****************************************************************************/

String &String::insert (size_type i, const String &string)
{
	std::string::iterator b = body.begin ();
        checkIndexThrow (i);
        utf8::unchecked::advance (b, i);

	size_type n = b - body.begin ();
	body.insert (n, string.body);
	return *this;
}

/****************************************************************************/

String &String::insert (const iterator &i, value_type c)
{
        std::insert_iterator <std::string> j (body, i.base ());
        utf8::unchecked::append (c, j);
        return *this;
}

/****************************************************************************/

String &String::insert (const iterator &i, const String &string)
{
        size_type n = i.base () - body.begin ();
        body.insert (n, string.body);
        return *this;
}

/****************************************************************************/

String String::substr (size_type i, size_type n) const
{
        checkIndexThrow (i);
	std::string::const_iterator b = body.begin ();
	utf8::unchecked::advance (b, i);

        size_type n2 = npos;
        size_type i2 = b - body.begin ();
        std::string::const_iterator b2 = b;

        if (n != npos && i + n < length ()) {
                utf8::unchecked::advance (b2, n);
                n2 = b2 - b;
        }

	return String (body.substr (i2, n2));
}

/****************************************************************************/

String &String::replace (size_type pos, size_type n, const String &s)
{
	erase (pos, n);
	insert (pos, s);
	return *this;
}

/****************************************************************************/

String &String::replace (const iterator &b, const iterator &e, const String &s)
{
	erase (b, e);
	insert (b, s);
	return *this;
}

/****************************************************************************/

String &String::replace (const String &a, const String &b)
{
	size_type i = indexOf (a);

	if (i == npos) {
		return *this;
	}

	size_type n = a.length ();
	return replace (i, n, b);
}

/****************************************************************************/

String::const_iterator String::find (const String &string, size_type from) const
{
	std::string::const_iterator b = body.begin ();
	utf8::unchecked::advance(b, from);

	std::string::size_type octetFrom = b - body.begin ();
	std::string::size_type i = body.find (string.body, octetFrom);

	if (i == std::string::npos) {
		return end ();
	}

	b = body.begin ();
	b += i;
	return const_iterator (b, body.begin (), body.end ());
}

/****************************************************************************/

String::size_type String::indexOf (const String &string, size_type from) const
{
	std::string::const_iterator b = body.begin ();
        utf8::unchecked::advance(b, from);

	std::string::size_type octetFrom = b - body.begin ();
	std::string::size_type i = body.find (string.body, octetFrom);

	if (i == std::string::npos) {
		return String::npos;
	}

	b = body.begin ();
	b += i;
	return utf8::unchecked::distance (body.begin (), b);
}

/****************************************************************************/

bool String::contains (const String &string) const
{
	return indexOf (string) != npos;
}

/****************************************************************************/

String::size_type String::count (const String &string) const
{
	size_type n = 0;
	size_type cnt = 0;

	while ((n = indexOf (string, n)) != npos) {
		cnt++;
		n++;
	}

	return cnt;
}

/****************************************************************************/

String String::toLower () const
{
	String ret;

	for (const_iterator i = begin (); i != end (); i++) {
		ret += static_cast <value_type> (towlower (*i));
	}

	return ret;
}

/****************************************************************************/

String String::toUpper () const
{
	String ret;

	for (const_iterator i = begin (); i != end (); i++) {
		ret += static_cast <value_type> (towupper (*i));
	}

	return ret;
}

/****************************************************************************/

String String::trimmed () const
{
        // Make a copy
        String s = *this;
        s.trim ();
        return s;
}

/****************************************************************************/

void String::trim ()
{
        String &s = *this;

        size_t i, j = s.size () - 1;

        if (!s.size ()) {
                return;
        }

        //'\t', '\n', '\v', '\f', '\r', and ' '
        for (i = 0; (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\v' || s[i] == '\f' || s[i] == '\r'); i++);

        if (i) {
                s.erase (0, i);
        }

        j = s.size ();

        if (!j) {
                return;
        }

        j--;

        for (i = j; i && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\v' || s[i] == '\f' || s[i] == '\r'); i--);

        if (i != j) {
                s.erase (i + 1);
        }
}

void String::checkIndexThrow (size_type pos) const
{
//        if (pos > length ()) {
//                throw Core::IndexOutOfBoundsException ();
//        }
}

/****************************************************************************/

String operator+ (const String &a, const String &b)
{
	return String (a.body + b.body);
}

/****************************************************************************/

Core::String operator+ (const char* lhs, const Core::String& rhs)
{
        return Core::String (lhs) + rhs;
}

/****************************************************************************/

Core::String operator+ (const Core::String& a, const char* b)
{
        return a + Core::String (b);
}

/****************************************************************************/

Core::String operator+ (const std::string &lhs, const Core::String& rhs)
{
        return Core::String (lhs) + rhs;
}

/****************************************************************************/

Core::String operator+ (const Core::String& lhs, const std::string &rhs)
{
        return lhs + Core::String (rhs);
}

/****************************************************************************/

String operator+ (const String &s, bool b)
{
	return s + lexical_cast <std::string> (b);
}

/****************************************************************************/

String operator+ (const String &s, char c)
{
        return s + lexical_cast <std::string> (c);
}

/****************************************************************************/

String operator+ (const String &s, signed char c)
{
        return s + lexical_cast <std::string> (c);
}

/****************************************************************************/

String operator+ (const String &s, unsigned char c)
{
        return s + lexical_cast <std::string> (c);
}

/****************************************************************************/

String operator+ (const String &s, double d)
{
        return s + lexical_cast <std::string> (d);
}

/****************************************************************************/

String operator+ (const String &s, long double d)
{
        return s + lexical_cast <std::string> (d);
}

/****************************************************************************/

String operator+ (const String &s, float f)
{
        return s + lexical_cast <std::string> (f);
}

/****************************************************************************/

String operator+ (const String &s, int i)
{
        return s + lexical_cast <std::string> (i);
}

/****************************************************************************/

String operator+ (const String &s, unsigned int i)
{
        return s + lexical_cast <std::string> (i);
}

/****************************************************************************/

String operator+ (const String &s, long int i)
{
        return s + lexical_cast <std::string> (i);
}

/****************************************************************************/

String operator+ (const String &s, unsigned long int i)
{
        return s + lexical_cast <std::string> (i);
}

/****************************************************************************/

String operator+ (const String &s, short int i)
{
        return s + lexical_cast <std::string> (i);
}

/****************************************************************************/

String operator+ (const String &s, unsigned short int i)
{
        return s + lexical_cast <std::string> (i);
}

/****************************************************************************/

String operator+ (bool b, const String &s)
{
	return lexical_cast <std::string> (b) + s;
}

/****************************************************************************/

String operator+ (char c, const String &s)
{
        return lexical_cast <std::string> (c) + s;
}

/****************************************************************************/

String operator+ (signed char c, const String &s)
{
        return lexical_cast <std::string> (c) + s;
}

/****************************************************************************/

String operator+ (unsigned char c, const String &s)
{
        return lexical_cast <std::string> (c) + s;
}

/****************************************************************************/

String operator+ (double d, const String &s)
{
        return lexical_cast <std::string> (d) + s;
}

/****************************************************************************/

String operator+ (long double d, const String &s)
{
        return lexical_cast <std::string> (d) + s;
}

/****************************************************************************/

String operator+ (float f, const String &s)
{
        return lexical_cast <std::string> (f) + s;
}

/****************************************************************************/

String operator+ (int i, const String &s)
{
        return lexical_cast <std::string> (i) + s;
}

/****************************************************************************/

String operator+ (unsigned int i, const String &s)
{
        return lexical_cast <std::string> (i) + s;
}

/****************************************************************************/

String operator+ (long int i, const String &s)
{
        return lexical_cast <std::string> (i) + s;
}

/****************************************************************************/

String operator+ (unsigned long int i, const String &s)
{
        return lexical_cast <std::string> (i) + s;
}

/****************************************************************************/

String operator+ (short int i, const String &s)
{
        return lexical_cast <std::string> (i) + s;
}

/****************************************************************************/

String operator+ (unsigned short int i, const String &s)
{
        return lexical_cast <std::string> (i) + s;
}

/****************************************************************************/

std::istream &operator>> (std::istream &i, Core::String &s)
{
        i >> s.body;
        return i;
}

/****************************************************************************/

std::ostream &operator<< (std::ostream &o, const Core::String &s)
{
        o << s.body;
        return o;
}

} // nms
#endif
