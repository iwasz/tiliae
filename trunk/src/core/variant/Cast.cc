/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <string>
#include "Cast.h"

namespace Core {

void throwExceptionValue (const char *type, const char *TYPE, Variant const &v)
{
        throw VariantCastException (std::string ("Wrong vcast to ") + type +
                        std::string (". variant.getType () is not ") + TYPE +
                        std::string (". Variant info : ") + v.toString () + ".");
}

void throwExceptionHanle (const char *type, Variant const &v, std::type_info const &actual)
{
        throw VariantCastException (std::string ("Wrong vcast to ") + type +
                        std::string (", where typeid (T*) : ") + actual.name () +
                        std::string (". Variant info : ") + v.toString () + ".");
}

/****************************************************************************/

std::string const &VCast<std::string>::run (Variant const &v)
{
        switch (v.type) {
        case Variant::STRING:
                return *boost::static_pointer_cast <std::string> (v.sptr);
        case Variant::STRING_POINTER:
                return *static_cast <std::string*> (v.ptr);
        case Variant::STRING_POINTER_CONST:
                return *static_cast <std::string const *> (v.ptr);
        default:
                throwExceptionValue ("std::string", "STRING", v);
                exit (1); // make copiler happy
        }
}

/****************************************************************************/

std::string &VCast<std::string &>::run (Variant &v)
{
        switch (v.type) {
        case Variant::STRING:
                return *boost::static_pointer_cast <std::string> (v.sptr);
        case Variant::STRING_POINTER:
                return *static_cast <std::string*> (v.ptr);
        default:
                throwExceptionValue ("std::string", "STRING", v);
                exit (1); // make copiler happy
        }
}

/****************************************************************************/

std::string const &VCast<std::string const &>::run (Variant const &v)
{
        switch (v.type) {
        case Variant::STRING:
                return *boost::static_pointer_cast <std::string> (v.sptr);
        case Variant::STRING_POINTER:
                return *static_cast <std::string*> (v.ptr);
        case Variant::STRING_POINTER_CONST:
                return *static_cast <std::string const *> (v.ptr);
        default:
                throwExceptionValue ("std::string", "STRING", v);
                exit (1); // make copiler happy
        }
}

/****************************************************************************/

std::string *VCast<std::string *>::run (Variant &v)
{
        switch (v.type) {
        case Variant::STRING:
                return boost::static_pointer_cast <std::string> (v.sptr).get ();
        case Variant::STRING_POINTER:
                return static_cast <std::string*> (v.ptr);
        default:
                throwExceptionValue ("std::string", "STRING", v);
                exit (1); // make copiler happy
        }
}

/****************************************************************************/

std::string const *VCast<std::string const *>::run (Variant const &v)
{
        switch (v.type) {
        case Variant::STRING:
                return boost::static_pointer_cast <std::string> (v.sptr).get ();
        case Variant::STRING_POINTER:
                return static_cast <std::string*> (v.ptr);
        case Variant::STRING_POINTER_CONST:
                return static_cast <std::string const *> (v.ptr);
        default:
                throwExceptionValue ("std::string", "STRING", v);
                exit (1); // make copiler happy
        }
}

/*##########################################################################*/

Core::String const &VCast<Core::String>::run (Variant const &v)
{
        switch (v.type) {
        case Variant::USTRING:
                return *boost::static_pointer_cast <Core::String> (v.sptr);
        case Variant::USTRING_POINTER:
                return *static_cast <Core::String*> (v.ptr);
        case Variant::USTRING_POINTER_CONST:
                return *static_cast <Core::String const *> (v.ptr);
        default:
                throwExceptionValue ("Core::String", "USTRING", v);
                exit (1); // make copiler happy
        }
}

/****************************************************************************/

Core::String &VCast<Core::String &>::run (Variant &v)
{
        switch (v.type) {
        case Variant::USTRING:
                return *boost::static_pointer_cast <Core::String> (v.sptr);
        case Variant::USTRING_POINTER:
                return *static_cast <Core::String*> (v.ptr);
        default:
                throwExceptionValue ("Core::String", "USTRING", v);
                exit (1); // make copiler happy
        }
}

/****************************************************************************/

Core::String const &VCast<Core::String const &>::run (Variant const &v)
{
        switch (v.type) {
        case Variant::USTRING:
                return *boost::static_pointer_cast <Core::String> (v.sptr);
        case Variant::USTRING_POINTER:
                return *static_cast <Core::String*> (v.ptr);
        case Variant::USTRING_POINTER_CONST:
                return *static_cast <Core::String const *> (v.ptr);
        default:
                throwExceptionValue ("Core::String", "USTRING", v);
                exit (1); // make copiler happy
        }
}

/****************************************************************************/

Core::String *VCast<Core::String *>::run (Variant &v)
{
        switch (v.type) {
        case Variant::USTRING:
                return boost::static_pointer_cast <Core::String> (v.sptr).get ();
        case Variant::USTRING_POINTER:
                return static_cast <Core::String*> (v.ptr);
        default:
                throwExceptionValue ("Core::String", "USTRING", v);
                exit (1); // make copiler happy
        }
}

/****************************************************************************/

Core::String const *VCast<Core::String const *>::run (Variant const &v)
{
        switch (v.type) {
        case Variant::USTRING:
                return boost::static_pointer_cast <Core::String> (v.sptr).get ();
        case Variant::USTRING_POINTER:
                return static_cast <Core::String*> (v.ptr);
        case Variant::USTRING_POINTER_CONST:
                return static_cast <Core::String const *> (v.ptr);
        default:
                throwExceptionValue ("Core::String", "USTRING", v);
                exit (1); // make copiler happy
        }
}

/*##########################################################################*/

std::string LCast <std::string>::run (Core::Variant const &v)
{
        switch (v.type) {
        case Variant::BOOL:
                return boost::lexical_cast <std::string> (v.b);
        case Variant::CHAR:
                return boost::lexical_cast <std::string> (v.c);
        case Variant::UNSIGNED_CHAR:
                return boost::lexical_cast <std::string> (v.uc);
        case Variant::DOUBLE:
                return boost::lexical_cast <std::string> (v.d);
        case Variant::LONG_DOUBLE:
                return boost::lexical_cast <std::string> (v.ld);
        case Variant::FLOAT:
                return boost::lexical_cast <std::string> (v.f);
        case Variant::INT:
                return boost::lexical_cast <std::string> (v.i);
        case Variant::UNSIGNED_INT:
                return boost::lexical_cast <std::string> (v.ui);
        case Variant::LONG_INT:
                return boost::lexical_cast <std::string> (v.li);
        case Variant::UNSIGNED_LONG_INT:
                return boost::lexical_cast <std::string> (v.uli);
        case Variant::SHORT_INT:
                return boost::lexical_cast <std::string> (v.si);
        case Variant::UNSIGNED_SHORT_INT:
                return boost::lexical_cast <std::string> (v.usi);
        case Variant::USTRING:
                return static_pointer_cast <Core::String> (v.sptr)->getBody ();
        case Variant::USTRING_POINTER:
                return static_cast <Core::String *> (v.ptr)->getBody ();
        case Variant::USTRING_POINTER_CONST:
                return static_cast <Core::String const *> (v.cptr)->getBody ();
        case Variant::STRING:
                return *static_pointer_cast <std::string> (v.sptr);
        case Variant::STRING_POINTER:
                return *static_cast <std::string *> (v.ptr);
        case Variant::STRING_POINTER_CONST:
                return *static_cast <std::string const *> (v.cptr);
        default:
                throw VariantCastException ("Bad lcast to std::string unsupported type. Variant info : " + v.toString () + ".");
        }
}

Core::String LCast <Core::String>::run (Core::Variant const &v)
{
        switch (v.type) {
        case Variant::BOOL:
                return boost::lexical_cast <Core::String> (v.b);
        case Variant::CHAR:
                return boost::lexical_cast <Core::String> (v.c);
        case Variant::UNSIGNED_CHAR:
                return boost::lexical_cast <Core::String> (v.uc);
        case Variant::DOUBLE:
                return boost::lexical_cast <Core::String> (v.d);
        case Variant::LONG_DOUBLE:
                return boost::lexical_cast <Core::String> (v.ld);
        case Variant::FLOAT:
                return boost::lexical_cast <Core::String> (v.f);
        case Variant::INT:
                return boost::lexical_cast <Core::String> (v.i);
        case Variant::UNSIGNED_INT:
                return boost::lexical_cast <Core::String> (v.ui);
        case Variant::LONG_INT:
                return boost::lexical_cast <Core::String> (v.li);
        case Variant::UNSIGNED_LONG_INT:
                return boost::lexical_cast <Core::String> (v.uli);
        case Variant::SHORT_INT:
                return boost::lexical_cast <Core::String> (v.si);
        case Variant::UNSIGNED_SHORT_INT:
                return boost::lexical_cast <Core::String> (v.usi);
        case Variant::USTRING:
                return *static_pointer_cast <Core::String> (v.sptr);
        case Variant::USTRING_POINTER:
                return *static_cast <Core::String *> (v.ptr);
        case Variant::USTRING_POINTER_CONST:
                return *static_cast <Core::String const *> (v.cptr);
        case Variant::STRING:
                return *static_pointer_cast <std::string> (v.sptr);
        case Variant::STRING_POINTER:
                return *static_cast <std::string *> (v.ptr);
        case Variant::STRING_POINTER_CONST:
                return *static_cast <std::string const *> (v.cptr);
        default:
                throw VariantCastException ("Bad lcast to Core::String unsupported type. Variant info : " + v.toString () + ".");
        }
}

}
