/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_REFLECTION_FIELD_H_
#define TILIAE_REFLECTION_FIELD_H_

#include <vector>
#include <string>
#include "reflection/wrapper/FieldWrapper.h"

namespace Reflection {

class Field {
public:

        Field (std::string const &n, IFieldWrapper *w) : name (n), wrapper (w) {}
        ~Field () { delete wrapper; }

        std::string getName () const { return this->name; }
        void setName (const std::string &name) { this->name = name; }

        std::type_info const &getType () const { return wrapper->getType (); }

        Core::Variant get (Core::Variant const &object) { return wrapper->get (object);  }
        void set (Core::Variant const &object, Core::Variant const &value) { wrapper->set (object, value); }

private:

        std::string name;
        IFieldWrapper *wrapper;

};

typedef std::vector <Field *> FieldVector;
typedef std::map <std::string, Field *> FieldMap;

} /* namespace Reflection */
#endif /* FIELD_H_ */
