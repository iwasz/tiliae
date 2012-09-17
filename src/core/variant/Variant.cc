/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>

#include "Variant.h"
#include "core/string/String.h"

namespace Core {
using namespace boost;

Variant::Variant () :
        type (NONE),
        ti (0)
{
}

/****************************************************************************/

Variant::Variant (bool const &j) :
        type (BOOL),
        ti (&typeid (bool &)),
        b (j)
{
}

/****************************************************************************/

Variant::Variant (char const &j) :
        type (CHAR),
        ti (&typeid (char &)),
        c (j)
{
}

/****************************************************************************/

Variant::Variant (unsigned char const &j) :
        type (UNSIGNED_CHAR),
        ti (&typeid (unsigned char &)),
        uc (j)
{
}

/****************************************************************************/

Variant::Variant (double const &j) :
        type (DOUBLE),
        ti (&typeid (double &)),
        d (j)
{
}

/****************************************************************************/

Variant::Variant (long double const &j) :
        type (LONG_DOUBLE),
        ti (&typeid (long double &)),
        ld (j)
{
}

/****************************************************************************/

Variant::Variant (float const &j) :
        type (FLOAT),
        ti (&typeid (float &)),
        f (j)
{
}

/****************************************************************************/

Variant::Variant (int const &j) :
        type (INT),
        ti (&typeid (int &)),
        i (j)
{
}

/****************************************************************************/

Variant::Variant (unsigned int const &j) :
        type (UNSIGNED_INT),
        ti (&typeid (unsigned int &)),
        ui (j)
{
}

/****************************************************************************/

Variant::Variant (long int const &j) :
        type (LONG_INT),
        ti (&typeid (long int &)),
        li (j)
{
}

/****************************************************************************/

Variant::Variant (unsigned long int const &j) :
        type (UNSIGNED_LONG_INT),
        ti (&typeid (unsigned long int &)),
        uli (j)
{
}

/****************************************************************************/

Variant::Variant (short int const &j) :
        type (SHORT_INT),
        ti (&typeid (short int &)),
        si (j)
{
}

/****************************************************************************/

Variant::Variant (unsigned short int const &j) :
        type (UNSIGNED_SHORT_INT),
        ti (&typeid (unsigned short int &)),
        usi (j)
{
}

/****************************************************************************/

Variant::Variant (std::string const &j) :
        type (STRING),
        ti (&typeid (std::string &)),
        sptr (boost::make_shared <std::string> (j))
{
}

Variant::Variant (std::string *j) :
        type (STRING_POINTER),
        ti (&typeid (std::string &)),
        ptr (j)
{
}

Variant::Variant (std::string const *j) :
        type (STRING_POINTER_CONST),
        ti (&typeid (std::string &)),
        cptr (j)
{
}

/*--------------------------------------------------------------------------*/

Variant::Variant (const char *s) :
        type (STRING),
        ti (&typeid (std::string &)),
        sptr (boost::make_shared <std::string> ((s) ? (s) : ("")))
{

}

/****************************************************************************/

Variant::Variant (Core::String const &j) :
        type (USTRING),
        ti (&typeid (Core::String &)),
        sptr (boost::make_shared <Core::String> (j))
{
}

Variant::Variant (Core::String *j) :
        type (USTRING_POINTER),
        ti (&typeid (Core::String &)),
        ptr (j)
{
}

Variant::Variant (Core::String const *j) :
        type (USTRING_POINTER_CONST),
        ti (&typeid (Core::String &)),
        cptr (j)
{
}

/****************************************************************************/

bool Variant::isObject () const
{
        return type == SMART_OBJECT || type == OBJECT || type == OBJECT_CONST || type == SMART_OBJECT_CONST;
}

/****************************************************************************/

bool Variant::isHandle () const
{
    return type == POINTER                      ||
           type == POINTER_CONST                ||
           type == SMART                        ||
           type == SMART_CONST                  ||
           type == OBJECT                       ||
           type == OBJECT_CONST                 ||
           type == SMART_OBJECT                 ||
           type == SMART_OBJECT_CONST           ||
           type == STRING                       ||
           type == STRING_POINTER               ||
           type == STRING_POINTER_CONST         ||
           type == USTRING                      ||
           type == USTRING_POINTER              ||
           type == USTRING_POINTER_CONST;
}

/****************************************************************************/

bool Variant::isValue () const
{
	return !isHandle () && type != NONE;
}

/****************************************************************************/

bool Variant::isNone () const
{
	return type == NONE;
}

/****************************************************************************/

bool Variant::isNull () const
{
    switch (type) {
    case POINTER:
    case OBJECT:
    case STRING_POINTER:
    case USTRING_POINTER:
            return !ptr;
    case POINTER_CONST:
    case OBJECT_CONST:
    case STRING_POINTER_CONST:
    case USTRING_POINTER_CONST:
            return !cptr;
    case SMART:
    case SMART_OBJECT:
    case SMART_CONST:
    case SMART_OBJECT_CONST:
    case STRING:
    case USTRING:
            return !sptr;

    case NIL:
            return true;

    default:
    	return false;
    }
}

void Variant::setNull ()
{
        type = NIL;
}

/****************************************************************************/

std::string Variant::toString () const
{
        std::string ret = "type=";

        switch (type) {
        case POINTER:
                ret += "POINTER, value=[" + lexical_cast <std::string> (ptr);
                break;
        case POINTER_CONST:
                ret += "POINTER_CONST, value=[" + lexical_cast <std::string> (cptr);
                break;
        case SMART:
                ret += "SMART, value=[" + lexical_cast <std::string> (sptr.get ());
                break;
        case SMART_CONST:
                ret += "SMART_CONST, value=[" + lexical_cast <std::string> (sptr.get ());
                break;
        case OBJECT:
                ret += "OBJECT, value=[" + lexical_cast <std::string> (ptr);
                break;
        case OBJECT_CONST:
                ret += "OBJECT_CONST, value=[" + lexical_cast <std::string> (cptr);
                break;
        case SMART_OBJECT:
                ret += "SMART_OBJECT, value=[" + lexical_cast <std::string> (sptr.get ());
                break;
        case SMART_OBJECT_CONST:
                ret += "SMART_OBJECT_CONST, value=[" + lexical_cast <std::string> (sptr.get ());
                break;
        case BOOL:
                ret += "BOOL, value=[" + lexical_cast <std::string> (b);
                break;
        case CHAR:
                ret += "CHAR, value=[" + lexical_cast <std::string> (c);
                break;
        case UNSIGNED_CHAR:
                ret += "UNSIGNED_CHAR, value=[" + lexical_cast <std::string> (uc);
                break;
        case DOUBLE:
                ret += "DOUBLE, value=[" + lexical_cast <std::string> (d);
                break;
        case LONG_DOUBLE:
                ret += "LONG_DOUBLE, value=[" + lexical_cast <std::string> (ld);
                break;
        case FLOAT:
                ret += "FLOAT, value=[" + lexical_cast <std::string> (f);
                break;
        case INT:
                ret += "INT, value=[" + lexical_cast <std::string> (i);
                break;
        case UNSIGNED_INT:
                ret += "UNSIGNED_INT, value=[" + lexical_cast <std::string> (ui);
                break;
        case LONG_INT:
                ret += "LONG_INT, value=[" + lexical_cast <std::string> (li);
                break;
        case UNSIGNED_LONG_INT:
                ret += "UNSIGNED_LONG_INT, value=[" + lexical_cast <std::string> (uli);
                break;
        case SHORT_INT:
                ret += "SHORT_INT, value=[" + lexical_cast <std::string> (si);
                break;
        case UNSIGNED_SHORT_INT:
                ret += "UNSIGNED_SHORT_INT, value=[" + lexical_cast <std::string> (usi);
                break;
        case STRING:
                ret += "STRING, value=[" + *static_pointer_cast <std::string> (sptr);
                break;
        case STRING_POINTER:
                ret += "STRING_POINTER, value=[" + *static_cast <std::string *> (ptr);
                break;
        case STRING_POINTER_CONST:
                ret += "STRING_POINTER_CONST, value=[" + *static_cast <std::string const *> (cptr);
                break;
        case USTRING:
                ret += "USTRING, value=[" + static_pointer_cast <Core::String> (sptr)->getBody ();
                break;
        case USTRING_POINTER:
                ret += "USTRING_POINTER, value=[" + static_cast <Core::String *> (ptr)->getBody ();
                break;
        case USTRING_POINTER_CONST:
                ret += "USTRING_POINTER_CONST, value=[" + static_cast <Core::String const *> (cptr)->getBody ();
                break;
        case NIL:
                ret += "NULL [";
                break;
        case NONE:
        default:
                ret += "NONE, value=[";
                break;
        }

        ret += std::string ("], type_info=[") + ((ti) ? (ti->name ()) : ("NULL")) + "], object=" + ((isObject ()) ? "true" : "false");
        return ret;
}

std::ostream &operator << (std::ostream &s, Core::Variant const &v)
{
	s << "Variant (" << v.toString () << ")";
	return s;
}

} // namespace
