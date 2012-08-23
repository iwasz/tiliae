/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_CLASS_IMPL_H
#define TILIAE_CLASS_IMPL_H

#include <list>

#include "Constructor.h"
#include "Method.h"
#include "IToStringEnabled.h"
#include "string/String.h"
#include "Pointer.h"
#include "Typedefs.h"
#include "ApiMacro.h"
#include "../model/Field.h"
#include "../wrapper/Deleter.h"

/****************************************************************************/

namespace Reflection {

class Class;

/// TODO std:vector
typedef std::list <Class *> ClassList;

/**
 *
 */
class TILIAE_API Class : public Core::IToStringEnabled {
public:

        Class (const std::string &n, std::type_info const &t, IDeleter *d) :
                name (n),
                type (t),
                initialized (false),
                deleter (d) {}

        virtual ~Class ();

        std::string getName () const { return name; }
        void setName (const std::string &n) { name = n; }

        ClassList getBaseClassList() const;
        void addBaseClassNames (const Core::StringVector &names);

        const ConstructorList &getConstructorList() const { return constructorList; }
        Constructor *getConstructor (std::type_info const &type) const;
        Constructor *getConstructor (unsigned int noOfArgs = 0) const;
        void setConstructorList (const ConstructorList &constructorList) { this->constructorList = constructorList; }
        void addConstructor (Constructor *constructor) { this->constructorList.push_back (constructor); }

        const MethodList &getMethodList() const;
        Method *getMethod (const std::string &name, std::type_info const &ti) const;
        Method *getMethod (const std::string &name, int noOfArgs = -1) const;
        void setMethodList (const MethodList &methodList) { this->methodList = methodList; }
        void addMethod (Method *method) { this->methodList.push_back (method); }

        void addField (Field *field) { fields[field->getName ()] = field; }
        Field *getField (std::string const &name) const;

        void destruct (Core::Variant *v) { deleter->free (*v); }

        /// Zwraca pierwszy element types, czyli typ "podstawowy" - nie wskaźnik.
        std::type_info const &getType () const { return type; }

/*--------------------------------------------------------------------------*/

        /**
         *  Returns string representation (formatted) of this class. Useful for debugging.
         */
        std::string toString () const;

        /**
         *  Operator == tess us whether two Class objects are related to one C++ type.
         */
        bool operator== (const Class &c) const { return name == c.name; }

        /**
         *  Operator != tess us whether two Class objects are related to one C++ type or not.
         */
        bool operator!= (const Class &c) const { return name != c.name; }

private:

        /**
         * Uzupełnia listę baseClassList an podstawie baseClassNames.
         */
        void initBaseClasses ();

        /**
         * Iintializes. Can be run many times.
         */
        void initWithCheck ();

private:

        std::string name;
        MethodList methodList;
        ConstructorList constructorList;
        Core::StringVector baseClassNames;
        ClassList baseClassList;
        FieldMap fields;
        std::type_info const &type;
        bool initialized;
        IDeleter *deleter;

};

} //namespace

#endif

