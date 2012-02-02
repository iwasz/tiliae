/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include "ReflectionFactory.h"
#include "../core/string/String.h"
#include "../core/Typedefs.h"
#include "../core/variant/Cast.h"
#include "../reflection/model/Constructor.h"
#include "../reflection/model/Class.h"
#include "../reflection/Manager.h"
#include "../core/DebugContext.h"

namespace Factory {
using namespace Core;

const char *ReflectionFactory::CLASS_NAME = "class";
const char *ReflectionFactory::CONSTRUCTOR_ARGS = "constructor-args";

/****************************************************************************/

Core::Variant ReflectionFactory::create (const VariantMap &parameters, Core::DebugContext *context) const
{
        VariantMap::const_iterator i = parameters.find (CLASS_NAME);
        assert (i != parameters.end ());
        std::string const &className = vcast <std::string const &> (i->second);

        i = parameters.find (CONSTRUCTOR_ARGS);
        Ptr <Reflection::Constructor> constructor;
        Core::VariantVector *classArgs = 0;

        if (i != parameters.end ()) {
                classArgs = vcast <Core::VariantVector *> (i->second);
        }

        Ptr <Reflection::Class> cls = Reflection::Manager::classForName (className);

        if (!cls) {
                dcError (context, "ReflectionFactory::create : Can't find class with name [" + className + "] with reflection.");
                return Variant ();
        }

        /*
         * Najprostzy możliwy sposób : pobieramy pierwszy konstruktor, który ma
         * właściwą liczbę argumentów.
         */
        constructor = cls->getConstructor ((classArgs) ? (classArgs->size ()) : (0));

        if (!constructor) {
                dcError (context, "ReflectionFactory::create : Can't get constructor for class " + className);
                return Variant ();
        }

        try {

                if (classArgs) {
                        return constructor->newInstance (classArgs);
                }
                else {
                        return constructor->newInstance ();
                }

        }
        catch (Exception const &e) {
                context->addContext (e.getContext ());
                dcError (context, "ReflectionFactory::create : Exception during execution of constructor of class " + className);
                return Variant ();
        }
        catch (std::exception const &e) {
                dcError (context, "ReflectionFactory::create : Exception during execution of constructor of class " + className + ". Exception message : " + e.what ());
                return Variant ();
        }
}

}
