/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef VARIANTCAST_TILIAE_H_
#define VARIANTCAST_TILIAE_H_

#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/call_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/cast.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

#include "Variant.h"
#include "Exception.h"
#include "Pointer.h"
#include "string/String.h"

namespace Core {

/*##########################################################################*/

/**
 * Wyjątek zrzucany z kastów vcast.
 */
class TILIAE_API VariantCastException : public Core::Exception {
public:

        VariantCastException () : Exception () {}
        VariantCastException (std::string const &s) : Exception (s) {}
        virtual ~VariantCastException () throw () {}
};

extern TILIAE_API void throwExceptionValue (const char *type, const char *TYPE, Variant const &v);
extern TILIAE_API void throwExceptionHanle (const char *type, Variant const &v, std::type_info const &actual);

/*##########################################################################*/

template <typename T>
struct LCast {
        static T run (Core::Variant const &v);
};

template <typename T>
T LCast <T>::run (Core::Variant const &v)
{
        switch (v.type) {
        case Variant::BOOL:
                return static_cast <T> (v.b);
        case Variant::CHAR:
                return static_cast <T> (v.c);
        case Variant::UNSIGNED_CHAR:
                return static_cast <T> (v.uc);
        case Variant::DOUBLE:
                return static_cast <T> (v.d);
        case Variant::LONG_DOUBLE:
                return static_cast <T> (v.ld);
        case Variant::FLOAT:
                return static_cast <T> (v.f);
        case Variant::INT:
                return static_cast <T> (v.i);
        case Variant::UNSIGNED_INT:
                return static_cast <T> (v.ui);
        case Variant::LONG_INT:
                return static_cast <T> (v.li);
        case Variant::UNSIGNED_LONG_INT:
                return static_cast <T> (v.uli);
        case Variant::SHORT_INT:
                return static_cast <T> (v.si);
        case Variant::UNSIGNED_SHORT_INT:
                return static_cast <T> (v.usi);
        case Variant::USTRING:
                return boost::lexical_cast <T> (static_pointer_cast <Core::String> (v.sptr)->c_str ());
        case Variant::USTRING_POINTER:
                return boost::lexical_cast <T> (static_cast <Core::String *> (v.ptr)->c_str ());
        case Variant::USTRING_POINTER_CONST:
                return boost::lexical_cast <T> (static_cast <Core::String const *> (v.cptr)->c_str ());
        case Variant::STRING:
                return boost::lexical_cast <T> (*static_pointer_cast <std::string> (v.sptr));
        case Variant::STRING_POINTER:
                return boost::lexical_cast <T> (*static_cast <std::string *> (v.ptr));
        case Variant::STRING_POINTER_CONST:
                return boost::lexical_cast <T> (*static_cast <std::string const *> (v.cptr));
        default:
                throw VariantCastException (std::string ("Bad lcast to T [") + typeid (T).name () + "] unsupported type. Variant info : " + v.toString () + ".");
        }
}

template <>
struct TILIAE_API LCast <std::string> {
        static std::string run (Core::Variant const &v);
};

template <>
struct TILIAE_API LCast <Core::String> {
        static Core::String run (Core::Variant const &v);
};

/*##########################################################################*/
/*# Domyślny                                                               #*/
/*##########################################################################*/

/**
 * Domyślny wzorzec, który działa tak samo jak kast na T const &
 */
template<typename T>
struct VCast {

        static T const &run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
T const &VCast<T>::run (Variant const &v)
{
        if (v.ti != &typeid (T &)) {
                throwExceptionHanle ("T, typeid (T &) != v.ti", v, typeid (T &));
        }

        switch (v.type) {
        case Variant::SMART:
        case Variant::SMART_CONST:
        case Variant::SMART_OBJECT:
        case Variant::SMART_OBJECT_CONST:
                return *(boost::static_pointer_cast<T const> (v.sptr).get ());

        case Variant::POINTER:
        case Variant::OBJECT:
                return *(static_cast <T const *> (v.ptr));

        case Variant::POINTER_CONST:
        case Variant::OBJECT_CONST:
                return *(static_cast <T const *> (v.cptr));

        default:
                throwExceptionHanle ("T, wrong v.type", v, typeid (T &));
                exit (1); // Żeby pozbyć się warninga
        }
}

template<typename T>
bool VCast<T>::can (Variant const &v)
{
        return v.type >= Variant::POINTER && v.type <= Variant::SMART_OBJECT_CONST && v.ti == &typeid (T &);
}

/*##########################################################################*/
/*# Skalary                                                                #*/
/*##########################################################################*/

template<>
struct VCast<bool> {

        static bool const &run (Variant const &v)
        {
                if (v.type != Variant::BOOL) {
                        throwExceptionValue ("bool", "BOOL", v);
                }

                return v.b;
        }

        static bool can (Variant const &v) { return v.type == Variant::BOOL; }

};

template<>
struct VCast<bool &> {

        static bool &run (Variant &v)
        {
                if (v.type != Variant::BOOL) {
                        throwExceptionValue ("bool &", "BOOL", v);
                }

                return v.b;
        }

        static bool can (Variant const &v) { return v.type == Variant::BOOL; }
};

template<>
struct VCast<bool const &> {

        static bool const &run (Variant const &v)
        {
                if (v.type != Variant::BOOL) {
                        throwExceptionValue ("bool const &", "BOOL", v);
                }

                return v.b;
        }

        static bool can (Variant const &v) { return v.type == Variant::BOOL; }
};

template<>
struct VCast<bool *> {

        static bool *run (Variant &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::BOOL) {
                        throwExceptionValue ("bool *", "BOOL", v);
                }

                return &v.b;
        }

        static bool can (Variant const &v) { return v.type == Variant::BOOL || v.type == Variant::NIL; }
};

template<>
struct VCast<bool const *> {

        static bool const *run (Variant const &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::BOOL) {
                        throwExceptionValue ("bool const *", "BOOL", v);
                }

                return &v.b;
        }

        static bool can (Variant const &v) { return v.type == Variant::BOOL || v.type == Variant::NIL; }
};

/****************************************************************************/

template<>
struct VCast<char> {

        static char const &run (Variant const &v)
        {
                if (v.type != Variant::CHAR) {
                        throwExceptionValue ("char", "CHAR", v);
                }

                return v.c;
        }

        static bool can (Variant const &v) { return v.type == Variant::CHAR; }
};

template<>
struct VCast<char &> {

        static char &run (Variant &v)
        {
                if (v.type != Variant::CHAR) {
                        throwExceptionValue ("char &", "CHAR", v);
                }

                return v.c;
        }

        static bool can (Variant const &v) { return v.type == Variant::CHAR; }
};

template<>
struct VCast<char const &> {

        static char const &run (Variant const &v)
        {
                if (v.type != Variant::CHAR) {
                        throwExceptionValue ("char const &", "CHAR", v);
                }

                return v.c;
        }

        static bool can (Variant const &v) { return v.type == Variant::CHAR; }
};

template<>
struct VCast<char *> {

        static char *run (Variant &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::CHAR) {
                        throwExceptionValue ("char *", "CHAR", v);
                }

                return &v.c;
        }

        static bool can (Variant const &v) { return v.type == Variant::CHAR || v.type == Variant::NIL; }
};

template<>
struct VCast<char const *> {

        static char const *run (Variant const &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::CHAR) {
                        throwExceptionValue ("char const *", "CHAR", v);
                }

                return &v.c;
        }

        static bool can (Variant const &v) { return v.type == Variant::CHAR || v.type == Variant::NIL; }
};

/****************************************************************************/

template<>
struct VCast<unsigned char> {

        static unsigned char const &run (Variant const &v)
        {
                if (v.type != Variant::UNSIGNED_CHAR) {
                        throwExceptionValue ("unsigned char", "UNSIGNED_CHAR", v);
                }

                return v.uc;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_CHAR; }
};

template<>
struct VCast<unsigned char &> {

        static unsigned char &run (Variant &v)
        {
                if (v.type != Variant::UNSIGNED_CHAR) {
                        throwExceptionValue ("unsigned char &", "UNSIGNED_CHAR", v);
                }

                return v.uc;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_CHAR; }
};

template<>
struct VCast<unsigned char const &> {

        static unsigned char const &run (Variant const &v)
        {
                if (v.type != Variant::UNSIGNED_CHAR) {
                        throwExceptionValue ("unsigned char const &", "UNSIGNED_CHAR", v);
                }

                return v.uc;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_CHAR; }
};

template<>
struct VCast<unsigned char *> {

        static unsigned char *run (Variant &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::UNSIGNED_CHAR) {
                        throwExceptionValue ("unsigned char *", "UNSIGNED_CHAR", v);
                }

                return &v.uc;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_CHAR || v.type == Variant::NIL; }
};

template<>
struct VCast<unsigned char const *> {

        static unsigned char const *run (Variant const &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::UNSIGNED_CHAR) {
                        throwExceptionValue ("unsigned char const *", "UNSIGNED_CHAR", v);
                }

                return &v.uc;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_CHAR || v.type == Variant::NIL; }
};

/****************************************************************************/

template<>
struct VCast<double> {

        static double const &run (Variant const &v)
        {
                if (v.type != Variant::DOUBLE) {
                        throwExceptionValue ("double", "DOUBLE", v);
                }

                return v.d;
        }

        static bool can (Variant const &v) { return v.type == Variant::DOUBLE; }
};

template<>
struct VCast<double &> {

        static double &run (Variant &v)
        {
                if (v.type != Variant::DOUBLE) {
                        throwExceptionValue ("double &", "DOUBLE", v);
                }

                return v.d;
        }

        static bool can (Variant const &v) { return v.type == Variant::DOUBLE; }
};

template<>
struct VCast<double const &> {

        static double const &run (Variant const &v)
        {
                if (v.type != Variant::DOUBLE) {
                        throwExceptionValue ("double const &", "DOUBLE", v);
                }

                return v.d;
        }

        static bool can (Variant const &v) { return v.type == Variant::DOUBLE; }
};

template<>
struct VCast<double *> {

        static double *run (Variant &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::DOUBLE) {
                        throwExceptionValue ("double *", "DOUBLE", v);
                }

                return &v.d;
        }

        static bool can (Variant const &v) { return v.type == Variant::DOUBLE || v.type == Variant::NIL; }
};

template<>
struct VCast<double const *> {

        static double const *run (Variant const &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::DOUBLE) {
                        throwExceptionValue ("double const *", "DOUBLE", v);
                }

                return &v.d;
        }

        static bool can (Variant const &v) { return v.type == Variant::DOUBLE || v.type == Variant::NIL; }
};

/****************************************************************************/

template<>
struct VCast<long double> {

        static long double const &run (Variant const &v)
        {
                if (v.type != Variant::LONG_DOUBLE) {
                        throwExceptionValue ("long double", "LONG_DOUBLE", v);
                }

                return v.ld;
        }

        static bool can (Variant const &v) { return v.type == Variant::LONG_DOUBLE; }
};

template<>
struct VCast<long double &> {

        static long double &run (Variant &v)
        {
                if (v.type != Variant::LONG_DOUBLE) {
                        throwExceptionValue ("long double &", "LONG_DOUBLE", v);
                }

                return v.ld;
        }

        static bool can (Variant const &v) { return v.type == Variant::LONG_DOUBLE; }
};

template<>
struct VCast<long double const &> {

        static long double const &run (Variant const &v)
        {
                if (v.type != Variant::LONG_DOUBLE) {
                        throwExceptionValue ("long double const &", "LONG_DOUBLE", v);
                }

                return v.ld;
        }

        static bool can (Variant const &v) { return v.type == Variant::LONG_DOUBLE; }
};

template<>
struct VCast<long double *> {

        static long double *run (Variant &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::LONG_DOUBLE) {
                        throwExceptionValue ("long double *", "LONG_DOUBLE", v);
                }

                return &v.ld;
        }

        static bool can (Variant const &v) { return v.type == Variant::LONG_DOUBLE || v.type == Variant::NIL; }
};

template<>
struct VCast<long double const *> {

        static long double const *run (Variant const &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::LONG_DOUBLE) {
                        throwExceptionValue ("long double const *", "LONG_DOUBLE", v);
                }

                return &v.ld;
        }

        static bool can (Variant const &v) { return v.type == Variant::LONG_DOUBLE || v.type == Variant::NIL; }
};

/****************************************************************************/

template<>
struct VCast<float> {

        static float const &run (Variant const &v)
        {
                if (v.type != Variant::FLOAT) {
                        throwExceptionValue ("float", "FLOAT", v);
                }

                return v.f;
        }

        static bool can (Variant const &v) { return v.type == Variant::FLOAT; }
};

template<>
struct VCast<float &> {

        static float &run (Variant &v)
        {
                if (v.type != Variant::FLOAT) {
                        throwExceptionValue ("float &", "FLOAT", v);
                }

                return v.f;
        }

        static bool can (Variant const &v) { return v.type == Variant::FLOAT; }
};

template<>
struct VCast<float const &> {

        static float const &run (Variant const &v)
        {
                if (v.type != Variant::FLOAT) {
                        throwExceptionValue ("float const &", "FLOAT", v);
                }

                return v.f;
        }

        static bool can (Variant const &v) { return v.type == Variant::FLOAT; }
};

template<>
struct VCast<float *> {

        static float *run (Variant &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::FLOAT) {
                        throwExceptionValue ("float *", "FLOAT", v);
                }

                return &v.f;
        }

        static bool can (Variant const &v) { return v.type == Variant::FLOAT || v.type == Variant::NIL; }
};

template<>
struct VCast<float const *> {

        static float const *run (Variant const &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::FLOAT) {
                        throwExceptionValue ("float const *", "FLOAT", v);
                }

                return &v.f;
        }

        static bool can (Variant const &v) { return v.type == Variant::FLOAT || v.type == Variant::NIL; }
};

/****************************************************************************/

template<>
struct VCast<int> {

        static int const &run (Variant const &v)
        {
                if (v.type != Variant::INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.i;
        }

        static bool can (Variant const &v) { return v.type == Variant::INT; }
};

template<>
struct VCast<int &> {

        static int &run (Variant &v)
        {
                if (v.type != Variant::INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.i;
        }

        static bool can (Variant const &v) { return v.type == Variant::INT; }
};

template<>
struct VCast<int const &> {

        static int const &run (Variant const &v)
        {
                if (v.type != Variant::INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.i;
        }

        static bool can (Variant const &v) { return v.type == Variant::INT; }
};

template<>
struct VCast<int *> {

        static int *run (Variant &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return &v.i;
        }

        static bool can (Variant const &v) { return v.type == Variant::INT || v.type == Variant::NIL; }
};

template<>
struct VCast<int const *> {

        static int const *run (Variant const &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return &v.i;
        }

        static bool can (Variant const &v) { return v.type == Variant::INT || v.type == Variant::NIL; }
};

/****************************************************************************/

template<>
struct VCast<unsigned int> {

        static unsigned int const &run (Variant const &v)
        {
                if (v.type != Variant::UNSIGNED_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.ui;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_INT; }
};

template<>
struct VCast<unsigned int &> {

        static unsigned int &run (Variant &v)
        {
                if (v.type != Variant::UNSIGNED_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.ui;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_INT; }
};

template<>
struct VCast<unsigned int const &> {

        static unsigned int const &run (Variant const &v)
        {
                if (v.type != Variant::UNSIGNED_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.ui;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_INT; }
};

template<>
struct VCast<unsigned int *> {

        static unsigned int *run (Variant &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::UNSIGNED_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return &v.ui;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_INT || v.type == Variant::NIL; }
};

template<>
struct VCast<unsigned int const *> {

        static unsigned int const *run (Variant const &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::UNSIGNED_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return &v.ui;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_INT || v.type == Variant::NIL; }
};

/****************************************************************************/

template<>
struct VCast<long int> {

        static long int const &run (Variant const &v)
        {
                if (v.type != Variant::LONG_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.li;
        }

        static bool can (Variant const &v) { return v.type == Variant::LONG_INT; }
};

template<>
struct VCast<long int &> {

        static long int &run (Variant &v)
        {
                if (v.type != Variant::LONG_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.li;
        }

        static bool can (Variant const &v) { return v.type == Variant::LONG_INT; }
};

template<>
struct VCast<long int const &> {

        static long int const &run (Variant const &v)
        {
                if (v.type != Variant::LONG_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.li;
        }

        static bool can (Variant const &v) { return v.type == Variant::LONG_INT; }
};

template<>
struct VCast<long int *> {

        static long int *run (Variant &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::LONG_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return &v.li;
        }

        static bool can (Variant const &v) { return v.type == Variant::LONG_INT || v.type == Variant::NIL; }
};

template<>
struct VCast<long int const *> {

        static long int const *run (Variant const &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::LONG_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return &v.li;
        }

        static bool can (Variant const &v) { return v.type == Variant::LONG_INT || v.type == Variant::NIL; }
};

/****************************************************************************/

template<>
struct VCast<unsigned long int> {

        static unsigned long int const &run (Variant const &v)
        {
                if (v.type != Variant::UNSIGNED_LONG_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.uli;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_LONG_INT; }
};

template<>
struct VCast<unsigned long int &> {

        static unsigned long int &run (Variant &v)
        {
                if (v.type != Variant::UNSIGNED_LONG_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.uli;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_LONG_INT; }
};

template<>
struct VCast<unsigned long int const &> {

        static unsigned long int const &run (Variant const &v)
        {
                if (v.type != Variant::UNSIGNED_LONG_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.uli;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_LONG_INT; }
};

template<>
struct VCast<unsigned long int *> {

        static unsigned long int *run (Variant &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::UNSIGNED_LONG_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return &v.uli;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_LONG_INT || v.type == Variant::NIL; }
};

template<>
struct VCast<unsigned long int const *> {

        static unsigned long int const *run (Variant const &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::UNSIGNED_LONG_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return &v.uli;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_LONG_INT || v.type == Variant::NIL; }
};

/****************************************************************************/

template<>
struct VCast<short int> {

        static short int const &run (Variant const &v)
        {
                if (v.type != Variant::SHORT_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.si;
        }

        static bool can (Variant const &v) { return v.type == Variant::SHORT_INT; }
};

template<>
struct VCast<short int &> {

        static short int &run (Variant &v)
        {
                if (v.type != Variant::SHORT_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.si;
        }

        static bool can (Variant const &v) { return v.type == Variant::SHORT_INT; }
};

template<>
struct VCast<short int const &> {

        static short int const &run (Variant const &v)
        {
                if (v.type != Variant::SHORT_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.si;
        }

        static bool can (Variant const &v) { return v.type == Variant::SHORT_INT; }
};

template<>
struct VCast<short int *> {

        static short int *run (Variant &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::SHORT_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return &v.si;
        }

        static bool can (Variant const &v) { return v.type == Variant::SHORT_INT || v.type == Variant::NIL; }
};

template<>
struct VCast<short int const *> {

        static short int const *run (Variant const &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::SHORT_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return &v.si;
        }

        static bool can (Variant const &v) { return v.type == Variant::SHORT_INT || v.type == Variant::NIL; }
};

/****************************************************************************/

template<>
struct VCast<unsigned short int> {

        static unsigned short int const &run (Variant const &v)
        {
                if (v.type != Variant::UNSIGNED_SHORT_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.usi;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_SHORT_INT; }
};

template<>
struct VCast<unsigned short int &> {

        static unsigned short int &run (Variant &v)
        {
                if (v.type != Variant::UNSIGNED_SHORT_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.usi;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_SHORT_INT; }
};

template<>
struct VCast<unsigned short int const &> {

        static unsigned short int const &run (Variant const &v)
        {
                if (v.type != Variant::UNSIGNED_SHORT_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return v.usi;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_SHORT_INT; }
};

template<>
struct VCast<unsigned short int *> {

        static unsigned short int *run (Variant &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::UNSIGNED_SHORT_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return &v.usi;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_SHORT_INT || v.type == Variant::NIL; }
};

template<>
struct VCast<unsigned short int const *> {

        static unsigned short int const *run (Variant const &v)
        {
                if (v.type == Variant::NIL) {
                        return NULL;
                }

                if (v.type != Variant::UNSIGNED_SHORT_INT) {
                        throwExceptionValue ("int", "INT", v);
                }

                return &v.usi;
        }

        static bool can (Variant const &v) { return v.type == Variant::UNSIGNED_SHORT_INT || v.type == Variant::NIL; }
};

/****************************************************************************/

template<>
struct TILIAE_API VCast<std::string> {

        static std::string const &run (Variant const &v);

        static bool can (Variant const &v)
        {
                return v.type == Variant::STRING ||
                        v.type == Variant::STRING_POINTER ||
                        v.type == Variant::STRING_POINTER_CONST;
        }
};

/*--------------------------------------------------------------------------*/

template<>
struct TILIAE_API VCast<std::string &> {

        static std::string &run (Variant &v);
        static bool can (Variant const &v)
        {
                return v.type == Variant::STRING ||
                        v.type == Variant::STRING_POINTER;
        }
};

/*--------------------------------------------------------------------------*/

template<>
struct TILIAE_API VCast<std::string const &> {

        static std::string const &run (Variant const &v);
        static bool can (Variant const &v)
        {
                return v.type == Variant::STRING ||
                        v.type == Variant::STRING_POINTER ||
                        v.type == Variant::STRING_POINTER_CONST;
        }
};

/*--------------------------------------------------------------------------*/

template<>
struct TILIAE_API VCast<std::string *> {

        static std::string *run (Variant &v);
        static bool can (Variant const &v)
        {
                return v.type == Variant::STRING ||
                        v.type == Variant::STRING_POINTER ||
                        v.type == Variant::NIL;
        }
};

/*--------------------------------------------------------------------------*/

template<>
struct TILIAE_API VCast<std::string const *> {

        static std::string const *run (Variant const &v);
        static bool can (Variant const &v)
        {
                return v.type == Variant::STRING ||
                        v.type == Variant::STRING_POINTER ||
                        v.type == Variant::STRING_POINTER_CONST ||
                        v.type == Variant::NIL;
        }
};

/****************************************************************************/

template<>
struct TILIAE_API VCast<Core::String> {

        static Core::String const &run (Variant const &v);
        static bool can (Variant const &v)
        {
                return v.type == Variant::USTRING ||
                        v.type == Variant::USTRING_POINTER ||
                        v.type == Variant::USTRING_POINTER_CONST;
        }
};

template<>
struct TILIAE_API VCast<Core::String &> {

        static Core::String &run (Variant &v);
        static bool can (Variant const &v)
        {
                return v.type == Variant::USTRING ||
                        v.type == Variant::USTRING_POINTER;
        }
};

template<>
struct TILIAE_API VCast<Core::String const &> {

        static Core::String const &run (Variant const &v);
        static bool can (Variant const &v)
        {
                return v.type == Variant::USTRING ||
                        v.type == Variant::USTRING_POINTER ||
                        v.type == Variant::USTRING_POINTER_CONST;
        }
};

template<>
struct TILIAE_API VCast<Core::String *> {

        static Core::String *run (Variant &v);
        static bool can (Variant const &v)
        {
                return v.type == Variant::USTRING ||
                        v.type == Variant::USTRING_POINTER ||
                        v.type == Variant::NIL;
        }
};

template<>
struct TILIAE_API VCast<Core::String const *> {

        static Core::String const *run (Variant const &v);
        static bool can (Variant const &v)
        {
                return v.type == Variant::USTRING ||
                        v.type == Variant::USTRING_POINTER ||
                        v.type == Variant::USTRING_POINTER_CONST ||
                        v.type == Variant::NIL;
        }
};

/****************************************************************************/

template<>
struct VCast<Core::Variant> {

        static Core::Variant const &run (Variant const &v) { return v; }
        static bool can (Variant const &v) { return true; }
};

template<>
struct VCast<Core::Variant &> {

        static Core::Variant &run (Variant &v) { return v; }
        static bool can (Variant const &v) { return true; }
};

template<>
struct VCast<Core::Variant const &> {

        static Core::Variant const &run (Variant const &v) { return v; }
        static bool can (Variant const &v) { return true; }
};

template<>
struct VCast<Core::Variant *> {

        static Core::Variant *run (Variant &v) { return &v; }
        static bool can (Variant const &v) { return true; }
};

template<>
struct VCast<Core::Variant const *> {

        static Core::Variant const *run (Variant const &v) { return &v; }
        static bool can (Variant const &v) { return true; }
};

/*##########################################################################*/
/*# Wskaźniki, shared_ptr i referencje                                     #*/
/*##########################################################################*/

template<typename T>
struct VCast <T &> {

        static T &run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
T &VCast<T &>::run (Variant const &v)
{
        if (v.getTypeInfo () != typeid (T &)) {
                throwExceptionHanle ("T&, typeid (T &) != v.ti", v, typeid (T &));
        }

        switch (v.type) {
        case Variant::SMART:
        case Variant::SMART_OBJECT:
                return *(boost::static_pointer_cast<T> (v.sptr).get ());

        case Variant::POINTER:
        case Variant::OBJECT:
                return *(static_cast <T *> (v.ptr));

        default:
                throwExceptionHanle ("T&, wrong v.type", v, typeid (T &));
                exit (1); // Żeby pozbyć się warninga
        }
}

template<typename T>
bool VCast<T &>::can (Variant const &v)
{
	return (v.type == Variant::SMART ||
                v.type == Variant::POINTER ||
                v.type == Variant::SMART_OBJECT ||
                v.type == Variant::OBJECT
                ) && v.ti == &typeid (T &);
}

/****************************************************************************/

template<typename T>
struct VCast <T const &> {

        static T const &run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
T const &VCast<T const &>::run (Variant const &v)
{
        if (v.getTypeInfo () != typeid (T &)) {
                throwExceptionHanle ("T const&, typeid (T &) != v.ti", v, typeid (T &));
        }

        switch (v.type) {
        case Variant::SMART:
        case Variant::SMART_CONST:
        case Variant::SMART_OBJECT:
        case Variant::SMART_OBJECT_CONST:
                return *(boost::static_pointer_cast<T const> (v.sptr).get ());

        case Variant::POINTER:
        case Variant::OBJECT:
                return *(static_cast <T const *> (v.ptr));

        case Variant::POINTER_CONST:
        case Variant::OBJECT_CONST:
                return *(static_cast <T const *> (v.cptr));

        default:
                throwExceptionHanle ("T const&, wrong v.type", v, typeid (T &));
                exit (1); // Żeby pozbyć się warninga
        }
}

template<typename T>
bool VCast<T const &>::can (Variant const &v)
{
        return v.type >= Variant::POINTER && v.type <= Variant::SMART_OBJECT_CONST && v.ti == &typeid (T &);
}

/*## wskaźniki #############################################################*/

template<typename T>
struct VCast<T *> {

        static T *run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
T *VCast <T *>::run (Variant const &v)
{
        if (v.getTypeInfo () != typeid (T &)) {
                throwExceptionHanle ("T*, typeid (T &) != v.ti", v, typeid (T &));
        }

        switch (v.type) {
        case Variant::SMART:
        case Variant::SMART_OBJECT:
                return boost::static_pointer_cast<T> (v.sptr).get ();

        case Variant::POINTER:
        case Variant::OBJECT:
                return static_cast<T *> (v.ptr);

        case Variant::NIL:
                return NULL;

        default:
                throwExceptionHanle ("T*, wrong v.type", v, typeid (T &));
        }

        exit (1); // Żeby pozbyć się warninga
}

template<typename T>
bool VCast<T *>::can (Variant const &v)
{
	return ((v.type == Variant::SMART ||
                v.type == Variant::POINTER ||
                v.type == Variant::SMART_OBJECT ||
                v.type == Variant::OBJECT) && v.ti == &typeid (T &)) ||

                (v.type == Variant::NIL);
}

/****************************************************************************/

template<typename T>
struct VCast<T const *> {

        static T const *run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
T const *VCast <T const *>::run (Variant const &v)
{
        if (v.getTypeInfo () != typeid (T &)) {
                throwExceptionHanle ("T const*, typeid (T &) != v.ti", v, typeid (T &));
        }

        switch (v.type) {
        case Variant::POINTER:
        case Variant::OBJECT:
                return static_cast <T const *> (v.ptr);

        case Variant::POINTER_CONST:
        case Variant::OBJECT_CONST:
                return static_cast <T const *> (v.cptr);

        case Variant::SMART:
        case Variant::SMART_CONST:
        case Variant::SMART_OBJECT:
        case Variant::SMART_OBJECT_CONST:
                return boost::static_pointer_cast<T const> (v.sptr).get ();

        case Variant::NIL:
                return NULL;

        default:
                throwExceptionHanle ("T const*, wrong v.type", v, typeid (T &));
                exit (1); // Żeby pozbyć się warninga
        }
}

template<typename T>
bool VCast<T const *>::can (Variant const &v)
{
        return (v.type >= Variant::POINTER && v.type <= Variant::SMART_OBJECT_CONST && v.ti == &typeid (T &)) || (v.type == Variant::NIL);
}

/*## shared_ptr ############################################################*/

template<typename T>
struct VCast<boost::shared_ptr<T> > {

        static boost::shared_ptr<T> run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
boost::shared_ptr<T> VCast<boost::shared_ptr<T> >::run (Variant const &v)
{
        if (v.type == Variant::NIL) {
                return boost::shared_ptr<T> ();
        }

        if (v.type != Variant::SMART && v.type != Variant::SMART_OBJECT) {
                throwExceptionHanle ("shared_ptr<T>, wrong v.type", v, typeid (T &));
        }

        if (v.getTypeInfo () != typeid (T &)) {
                throwExceptionHanle ("shared_ptr<T>, typeid (T &) != v.ti", v, typeid (T &));
        }

        return boost::static_pointer_cast<T> (v.sptr);
}

template<typename T>
bool VCast<boost::shared_ptr<T> >::can (Variant const &v)
{
	return ((v.type == Variant::SMART || v.type == Variant::SMART_OBJECT) && v.ti == &typeid (T &)) || (v.type == Variant::NIL);
}

/****************************************************************************/

template<typename T>
struct VCast<boost::shared_ptr<T const> > {

        static boost::shared_ptr<T const> run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
boost::shared_ptr<T const> VCast<boost::shared_ptr<T const> >::run (Variant const &v)
{
        if (v.type == Variant::NIL) {
                return boost::shared_ptr<T const> ();
        }

        if (v.getTypeInfo () != typeid (T &)) {
                throwExceptionHanle ("shared_ptr<T const>, typeid (T &) != v.ti", v, typeid (T &));
        }

        switch (v.type) {
        case Variant::SMART:
        case Variant::SMART_CONST:
        case Variant::SMART_OBJECT:
        case Variant::SMART_OBJECT_CONST:
                return boost::static_pointer_cast<T> (v.sptr);

        default:
                throwExceptionHanle ("shared_ptr<T const>, wrong v.type", v, typeid (T &));
                exit (1); // Żeby pozbyć się warninga
        }
}

template<typename T>
bool VCast<boost::shared_ptr<T const> >::can (Variant const &v)
{
	return ((v.type == Variant::SMART ||
                v.type == Variant::SMART_CONST ||
                v.type == Variant::SMART_OBJECT ||
                v.type == Variant::SMART_OBJECT_CONST) && v.ti == &typeid (T &)) ||
                (v.type == Variant::NIL);
}

/*##########################################################################*/
/*# Kast dynamiczny, dla typów kompletnych                                 #*/
/*##########################################################################*/

template<typename T>
struct OCast : public VCast <T> {

        static T const &run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
T const &OCast<T>::run (Variant const &v)
{
        switch (v.type) {
        case Variant::SMART_OBJECT:
        case Variant::SMART_OBJECT_CONST:
                return *(boost::polymorphic_downcast <T *> (boost::static_pointer_cast<Object> (v.sptr).get ()));

        case Variant::OBJECT:
                return *(boost::polymorphic_downcast <T *> (static_cast<Object *> (v.ptr)));

        case Variant::OBJECT_CONST:
                return *(boost::polymorphic_downcast <T const *> (static_cast<Object const *> (v.cptr)));

        default:
                return VCast<T>::run (v);
        };
}

template<typename T>
bool OCast<T>::can (Variant const &v)
{
    switch (v.type) {
    case Variant::SMART_OBJECT:
    case Variant::SMART_OBJECT_CONST:
            return dynamic_cast <T *> (boost::static_pointer_cast<Object> (v.sptr).get ());

    case Variant::OBJECT:
            return dynamic_cast <T *> (static_cast<Object *> (v.ptr));

    case Variant::OBJECT_CONST:
            return dynamic_cast <T const *> (static_cast<Object const *> (v.cptr));

    default:
            return VCast<T>::can (v);
    };
}

/*##########################################################################*/

template<typename T>
struct OCast <T &> : public VCast <T &> {

        static T &run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
T &OCast<T &>::run (Variant const &v)
{
        switch (v.type) {
        case Variant::SMART_OBJECT:
                return *(boost::polymorphic_downcast <T *> (boost::static_pointer_cast<Object> (v.sptr).get ()));

        case Variant::OBJECT:
                return *(boost::polymorphic_downcast <T *> (static_cast<Object *> (v.ptr)));

        default:
                return VCast<T &>::run (v);
        };
}

template<typename T>
bool OCast<T&>::can (Variant const &v)
{
	switch (v.type) {
     case Variant::SMART_OBJECT:
             return dynamic_cast <T *> (boost::static_pointer_cast<Object> (v.sptr).get ());

     case Variant::OBJECT:
             return dynamic_cast <T *> (static_cast<Object *> (v.ptr));

     default:
             return VCast<T &>::can (v);
     };
}

/****************************************************************************/

template<typename T>
struct OCast <T const &> : public VCast <T const &> {

        static T const &run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
T const &OCast<T const &>::run (Variant const &v)
{
        switch (v.type) {
        case Variant::SMART_OBJECT:
        case Variant::SMART_OBJECT_CONST:
                return *(boost::polymorphic_downcast <T const *> (boost::static_pointer_cast<Object const> (v.sptr).get ()));

        case Variant::OBJECT:
                return *(boost::polymorphic_downcast <T const *> (static_cast<Object const *> (v.ptr)));

        case Variant::OBJECT_CONST:
                return *(boost::polymorphic_downcast <T const *> (static_cast<Object const *> (v.cptr)));

        default:
                return VCast<T const &>::run (v);
        };
}

template<typename T>
bool OCast<T const &>::can (Variant const &v)
{
    switch (v.type) {
    case Variant::SMART_OBJECT:
    case Variant::SMART_OBJECT_CONST:
            return dynamic_cast <T *> (boost::static_pointer_cast<Object> (v.sptr).get ());

    case Variant::OBJECT:
            return dynamic_cast <T *> (static_cast<Object *> (v.ptr));

    case Variant::OBJECT_CONST:
            return dynamic_cast <T const *> (static_cast<Object const *> (v.cptr));

    default:
            return VCast<T const &>::can (v);
    };
}

/*## wskaźniki #############################################################*/

template<typename T>
struct OCast<T *> : public VCast<T *> {

        static T *run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
T *OCast <T *>::run (Variant const &v)
{
        switch (v.type) {
        case Variant::SMART_OBJECT:
                return boost::polymorphic_downcast <T *> (boost::static_pointer_cast<Object> (v.sptr).get ());

        case Variant::OBJECT:
                return boost::polymorphic_downcast <T *> (static_cast<Object *> (v.ptr));

        default:
                return VCast<T *>::run (v);
        };
}


template<typename T>
bool OCast<T *>::can (Variant const &v)
{
	switch (v.type) {
     case Variant::SMART_OBJECT:
             return dynamic_cast <T *> (boost::static_pointer_cast<Object> (v.sptr).get ());

     case Variant::OBJECT:
             return dynamic_cast <T *> (static_cast<Object *> (v.ptr));

     default:
             return VCast<T *>::can (v);
     };
}

/****************************************************************************/

template<typename T>
struct OCast<T const *> : public VCast<T const *> {

        static T const *run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
T const *OCast <T const *>::run (Variant const &v)
{
        switch (v.type) {
        case Variant::SMART_OBJECT:
        case Variant::SMART_OBJECT_CONST:
                return boost::polymorphic_downcast <T const *> (boost::static_pointer_cast<Object const> (v.sptr).get ());

        case Variant::OBJECT:
                return boost::polymorphic_downcast <T const *> (static_cast<Object const *> (v.ptr));

        case Variant::OBJECT_CONST:
                return boost::polymorphic_downcast <T const *> (static_cast<Object const *> (v.cptr));

        default:
                return VCast<T const *>::run (v);
        };
}


template<typename T>
bool OCast<T const *>::can (Variant const &v)
{
    switch (v.type) {
    case Variant::SMART_OBJECT:
    case Variant::SMART_OBJECT_CONST:
            return dynamic_cast <T *> (boost::static_pointer_cast<Object> (v.sptr).get ());

    case Variant::OBJECT:
            return dynamic_cast <T *> (static_cast<Object *> (v.ptr));

    case Variant::OBJECT_CONST:
            return dynamic_cast <T const *> (static_cast<Object const *> (v.cptr));

    default:
            return VCast<T const *>::can (v);
    };
}

/*## shared_ptr ############################################################*/

template<typename T>
struct OCast<boost::shared_ptr<T> > : public VCast<boost::shared_ptr<T> > {

        static boost::shared_ptr<T> run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
boost::shared_ptr<T> OCast<boost::shared_ptr<T> >::run (Variant const &v)
{
        if (v.type == Variant::SMART_OBJECT) {
                return dynamic_pointer_cast <T> (boost::static_pointer_cast<Object> (v.sptr));
        }

        return VCast<boost::shared_ptr <T> >::run (v);
}


template<typename T>
bool OCast<boost::shared_ptr<T> >::can (Variant const &v)
{
	return (v.type == Variant::SMART_OBJECT && dynamic_cast <T *> (boost::static_pointer_cast<Object> (v.sptr).get ())) ||
			VCast<boost::shared_ptr<T> >::can (v);
}

/****************************************************************************/

template<typename T>
struct OCast<boost::shared_ptr<T const> > : public VCast<boost::shared_ptr<T const> > {

        static boost::shared_ptr<T const> run (Variant const &v);
        static bool can (Variant const &v);
};

template<typename T>
boost::shared_ptr<T const> OCast<boost::shared_ptr<T const> >::run (Variant const &v)
{
        switch (v.type) {
        case Variant::SMART_OBJECT:
        case Variant::SMART_OBJECT_CONST:
                return dynamic_pointer_cast <T const>  (boost::static_pointer_cast<Object const> (v.sptr));

        default:
                return VCast<boost::shared_ptr<T const> >::run (v);
        };
}

template<typename T>
bool OCast<boost::shared_ptr<T const> >::can (Variant const &v)
{
    switch (v.type) {
    case Variant::SMART_OBJECT:
    case Variant::SMART_OBJECT_CONST:
            return dynamic_cast <T const *>  (boost::static_pointer_cast<Object const> (v.sptr).get ());

    default:
            return VCast<boost::shared_ptr<T const> >::can (v);
    };
}

} // namespace

/*##########################################################################*/

/*
 * Paradoksalnie dzięki zastosowaniu tej struktury w vcast zamiast całego
 * tego skomplikowanego typu GCC generuje krótsze symbole w binarce.
 */
template <typename T>
struct Ret {

        typedef typename boost::mpl::if_c <
                        boost::is_pointer <T>::value ||
                        boost::is_reference <T>::value ||
                        Core::is_ptr <T>::value
                        , T, typename boost::call_traits<T>::const_reference>::type type;

};

/****************************************************************************/
/* API                                                                      */
/****************************************************************************/

/**
 * Odpowiednik static_cast dla Variant. Wyciąga z warianta dokładnie taki
 * sam typ jaki został włożony - jeśli int, to int etc.
 * \ingroup CoreAPI
 */
template <typename T>
typename Ret<T>::type
TILIAE_API vcast (Core::Variant const &v)
{
       return Core::VCast <T>::run (v);
}

template <typename T>
typename Ret<T>::type
TILIAE_API vcast (Core::Variant &v)
{
       return Core::VCast <T>::run (v);
}

/*##########################################################################*/

/**
 * Testuje, czy analogiczny vcast się powiedzie.
 * \ingroup CoreAPI
 */
template <typename T>
bool TILIAE_API ccast (Core::Variant const &v)
{
       return Core::VCast <T>::can (v);
}

template <typename T>
bool TILIAE_API ccast (Core::Variant &v)
{
       return Core::VCast <T>::can (v);
}

/*##########################################################################*/

/**
 * Odpowiednik dynamic_cast dla Variant (pod warunkiem, że T dziedziczy z Core::Object).
 * \ingroup CoreAPI
 */
template <typename T>
typename Ret<T>::type
TILIAE_API ocast (Core::Variant const &v)
{
       return Core::OCast <T>::run (v);
}

template <typename T>
typename Ret<T>::type
TILIAE_API ocast (Core::Variant &v)
{
       return Core::OCast <T>::run (v);
}

/*##########################################################################*/

/**
 * Testuje, czy analogiczny ocast się powiedzie.
 * \ingroup CoreAPI
 */
template <typename T>
bool TILIAE_API occast (Core::Variant const &v)
{
       return Core::OCast <T>::can (v);
}

template <typename T>
bool TILIAE_API occast (Core::Variant &v)
{
       return Core::OCast <T>::can (v);
}

/*##########################################################################*/

/**
 * Coś na kształt boost::lexical_cast. Tylko, że dla wariantów. To działa tylko dla
 * wariantow które mają sematykę wartości + wariantów zawierajcych napisy Core::String
 * i std::string. Ten cast próbuje przekonwertować wariant (między innymi za pomocą
 * boost::lexical_cast) na własciwy typ. Konwersje sa możliwe z typów napisowych na
 * liczbowe, zmiennoprzecinkowe na całkowite (ze stratą dokładności) etc.
 * \ingroup CoreAPI
 */
template <typename T>
T lcast (Core::Variant const &v)
{
        return Core::LCast <T>::run (v);
}
#	endif /* CAST_H_ */
