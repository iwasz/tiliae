/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MANAGER_H_
#define MANAGER_H_

#include "visitor/ClassVisitor.h"
#include "IClassContainer.h"
#include "../core/IToStringEnabled.h"
#include "../core/string/String.h"
#include "../core/Pointer.h"
#include "../core/ApiMacro.h"

namespace Reflection {

class Class;

/**
 *
 */
class TILIAE_API Manager : public Core::IToStringEnabled {
public:

        ~Manager ();

        /**
         * Służy do pobierania obiektu managera.
         * @return Obiekt managera, singleton, inicjowany przy pierwszym wywołaniu.
         * http://www.parashift.com/c++-faq-lite/ctors.html#faq-10.12
         */
        static Manager &instance ();

        /**
         *  Inits the manager. Not obligatory to call, since all other
         *  methods calls this for the first time they are used.
         */
        static void init ();

        /**
         * Gets a Class object for a given name. Returns empty pointer
         * if no class is found.
         */
        static Class *classForName (const std::string &className);

        /**
         * Gets a Class object for a given type_info object. Returns
         * empty pointer if no class is found.
         */
        static Class *classForType (std::type_info const &t);

        /**
         * Adds a Class object to Manager. Does not check whether this
         * class allready inside.
         */
        static void add (Class *c);

        /**
         * Zwraca informację, czy manager jest zainicjowany (użycie
         * metod classForType, classForName, init) powoduje
         * zainicjowanie managera.
         */
        static bool getInit () { return instance ().initialized; }

        /**
         *
         */
        std::string toString () const;

private:

        /**
         * Nie da się inaczej utworzyć niż przez Manager::getInstance
         */
        Manager ();
        Manager (const Manager &) {}

        static Class *classForNameImpl (const std::string &className);

        /**
         * Dodaje do managera typy z Core (String, StirngList etc).
         */
        static void addStandardTypes ();

        friend class ClassVisitor;

private:

        bool initialized;
        IClassContainer *classContainer;

};

}

#endif /* MANAGER_H_ */
