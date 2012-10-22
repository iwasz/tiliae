/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/lexical_cast.hpp>
#include "ReflectionFactory.h"
#include "ScalarFactory.h"
#include <cstring>

namespace Factory {
using namespace Core;

enum Type { NONE, STRING, USTRING, DOUBLE, INT, UINT };

/****************************************************************************/

template <typename T>
Variant convertValue (bool classArgs,
                      Type type,
                      std::string const &s,
#ifdef WITH_CORE_STRING
                      Core::String const &us,
#endif
                      long int i,
                      long unsigned int ui,
                      long double d)
{
        if (!classArgs) {
                return Variant (T ());
        }
        else {
                switch (type) {
                case STRING:
                        return Variant (boost::lexical_cast <T> (s));
#ifdef WITH_CORE_STRING
                case USTRING:
                        return Variant (boost::lexical_cast <T> (us));
#endif
                case INT:
                        return Variant (boost::lexical_cast <T> (i));
                case UINT:
                        return Variant (boost::lexical_cast <T> (ui));
                case DOUBLE:
                        return Variant (boost::lexical_cast <T> (d));
                default:
                        return Variant ();
                }
        }

        return Variant ();
}

/****************************************************************************/

template <>
Variant convertValue <std::string> (bool classArgs,
                                Type type,
                                std::string const &s,
#ifdef WITH_CORE_STRING
                                Core::String const &us,
#endif
                                long int i,
                                long unsigned int ui,
                                long double d)
{
        if (!classArgs) {
                return Variant (std::string ());
        }
        else {
                switch (type) {
                case STRING:
                        return Variant (s);
#ifdef WITH_CORE_STRING
                case USTRING:
                        return Variant (Core::String (s));
#endif
                case INT:
                        return Variant (boost::lexical_cast <std::string> (i));
                case UINT:
                        return Variant (boost::lexical_cast <std::string> (ui));
                case DOUBLE:
                        return Variant (boost::lexical_cast <std::string> (d));
                default:
                        return Variant ();
                }
        }

        return Variant ();
}

/****************************************************************************/

#ifdef WITH_CORE_STRING
template <>
Variant convertValue <Core::String> (bool classArgs,
                                Type type,
                                std::string const &s,
                                Core::String const &us,
                                long int i,
                                long unsigned int ui,
                                long double d)
{
        if (!classArgs) {
                return Variant (Core::String ());
        }
        else {
                switch (type) {
                case STRING:
                        return Variant (Core::String (s));
                case USTRING:
                        return Variant (us);
                case INT:
                        return Variant (boost::lexical_cast <Core::String> (i));
                case UINT:
                        return Variant (boost::lexical_cast <Core::String> (ui));
                case DOUBLE:
                        return Variant (boost::lexical_cast <Core::String> (d));
                default:
                        return Variant ();
                }
        }

        return Variant ();
}
#endif

/****************************************************************************/

template <>
Variant convertValue <bool> (bool classArgs,
                Type type,
                std::string const &s,
#ifdef WITH_CORE_STRING
                Core::String const &us,
#endif
                long int i,
                long unsigned int ui,
                long double d)
{
        if (!classArgs) {
                return Variant (bool (false));
        }
        else {

                switch (type) {
                case STRING:
#ifdef WITH_CORE_STRING
                case USTRING:
                {
                        std::string copy = ((type == STRING) ? (s) : (us.getBody ()));

                        if (copy == "1" || copy == "true" || copy == "on" || copy == "yes") {
                                return Variant (true);
                        }
                        else {
                                return Variant (false);
                        }
                }
#endif
                case INT:
                        return Variant (bool (i));
                case UINT:
                        return Variant (bool (ui));
                case DOUBLE:
                        return Variant (bool (d));
                default:
                        return Variant ();
                }

        }

        return Variant ();
}

/****************************************************************************/

Core::Variant ScalarFactory::create (const VariantMap &parameters, Core::DebugContext *context) const
{
        VariantMap::const_iterator it = parameters.find (ReflectionFactory::CLASS_NAME);

        if (it == parameters.end ()) {
                dcError (context, "ScalarFactory has no CLASS_NAME");
                return Core::Variant ();
        }

        // Nazwa klasy.
        std::string const &className = vcast <std::string const &> (it->second);

        // Parametry.
        it = parameters.find (ReflectionFactory::CONSTRUCTOR_ARGS);
        Core::VariantVector const *classArgs = 0;

        if (it != parameters.end ()) {
                classArgs = vcast <Core::VariantVector const *> (it->second);
        }

        if (classArgs && classArgs->size () != 1) {
                dcError (context, "ScalarFactory requires 1 constructor argument or NULL argVector. You provided : " + boost::lexical_cast <std::string> (classArgs->size ()));
                return Core::Variant ();
        }

        Variant arg1;

        long double d = 0.0;
        long int i = 0;
        unsigned long int ui = 0;
        std::string s;
#ifdef WITH_CORE_STRING
        Core::String us;
#endif
        Type type = NONE;

        // Skonwertuj od jednego z 4 pojemnych typów skalarnych.
        if (classArgs) {
                arg1 = classArgs->front ();

                switch (arg1.getType()) {
                case Variant::STRING:
                        s = vcast <std::string> (arg1);
                        type = STRING;
                        break;

                case Variant::STRING_POINTER:
                        s = vcast <std::string> (arg1);
                        type = STRING;
                        break;

                case Variant::STRING_POINTER_CONST:
                        s = vcast <std::string> (arg1);
                        type = STRING;
                        break;

#ifdef WITH_CORE_STRING
                case Variant::USTRING:
                        us = vcast <Core::String> (arg1).getBody ();
                        type = USTRING;
                        break;

                case Variant::USTRING_POINTER:
                        us = vcast <Core::String> (arg1).getBody ();
                        type = USTRING;
                        break;

                case Variant::USTRING_POINTER_CONST:
                        us = vcast <Core::String> (arg1).getBody ();
                        type = USTRING;
                        break;
#endif

                case Variant::BOOL:
                        i = vcast <bool> (arg1);
                        type = INT;
                        break;

                case Variant::CHAR:
                        i = vcast <char> (arg1);
                        type = INT;
                        break;

                case Variant::UNSIGNED_CHAR:
                        i = vcast <unsigned char> (arg1);
                        type = INT;
                        break;

                case Variant::DOUBLE:
                        d = vcast <double> (arg1);
                        type = DOUBLE;
                        break;

                case Variant::LONG_DOUBLE:
                        d = vcast <long double> (arg1);
                        type = DOUBLE;
                        break;

                case Variant::FLOAT:
                        d = vcast <float> (arg1);
                        type = DOUBLE;
                        break;

                case Variant::INT:
                        i = vcast <int> (arg1);
                        type = INT;
                        break;

                case Variant::UNSIGNED_INT:
                        ui = vcast <unsigned int> (arg1);
                        type = UINT;
                        break;

                case Variant::LONG_INT:
                        i = vcast <long int> (arg1);
                        type = INT;
                        break;

                case Variant::UNSIGNED_LONG_INT:
                        ui = vcast <unsigned long int> (arg1);
                        type = UINT;
                        break;

                case Variant::SHORT_INT:
                        i = vcast <short int> (arg1);
                        type = INT;
                        break;

                case Variant::UNSIGNED_SHORT_INT:
                        ui = vcast <unsigned short int> (arg1);
                        type = UINT;
                        break;

                default:
                        dcError (context, "ScalarFactory wrong argument type. Simple scalar type expected. You provided : " + arg1.toString ());
                        return Core::Variant ();
                }

        }

#ifdef WITH_CORE_STRING
#define STR_PARAM_HACK s, us
#else
#define STR_PARAM_HACK s
#endif

        if (className == "string" || className == "text") {
                return convertValue <std::string> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }
#ifdef WITH_CORE_STRING
        else if (className == "String") {
                return convertValue <Core::String> (classArgs, type, s, us, i, ui, d);
        }
#endif
        else if (className == "int") {
                return convertValue <int> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }
        else if (className == "bool") {
                return convertValue <bool> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }
        else if (className == "char") {
                return convertValue <char> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }
        else if (className == "signed char") {
                return convertValue <signed char> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }
        else if (className == "unsigned char") {
                return convertValue <unsigned char> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }
        else if (className == "double") {
                return convertValue <double> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }
        else if (className == "long double") {
                return convertValue <long double> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }
        else if (className == "float") {
                return convertValue <float> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }
        else if (className == "unsigned int") {
                return convertValue <unsigned int> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }
        else if (className == "long int") {
                return convertValue <long int> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }
        else if (className == "unsigned long int") {
                return convertValue <unsigned long int> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }
        else if (className == "short int") {
                return convertValue <short int> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }
        else if (className == "unsigned short int") {
                return convertValue <unsigned short int> (classArgs, type, STR_PARAM_HACK, i, ui, d);
        }

        return Core::Variant ();
}

/*
 * Uwaga - dopisać tu wszystkie typy z metody convertValue.
 */
const char *ScalarFactory::SUPPORTED_TYPES[] = {
                "int",
                "bool",
                "char",
                "signed char",
                "unsigned char",
                "double",
                "long double",
                "float",
                "unsigned int",
                "unsigned long int",
                "short int",
                "unsigned short int",
                "String",
                "string",
                "text",
                NULL
};

/****************************************************************************/

bool ScalarFactory::isTypeSupported (const char *name)
{
        const char *s = NULL;
        for (int i = 0; (s = SUPPORTED_TYPES[i]); ++i) {
                if (!strcmp (name, s)) {
                        return true;
                }
        }
        return false;
}

}
