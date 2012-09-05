/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BOOLEANOBJECT_H_
#define BOOLEANOBJECT_H_

#include "IObject.h"
#include "../../core/string/String.h"
#include "../../core/Typedefs.h"
#include "../../core/ApiMacro.h"

namespace StateMachine {

/**
 * Prosty obiekt Boolowy. _TRUE lub _FALSE.
 * \ingroup StateMachine
 */
class TILIAE_API BooleanObject : public IObject {
public:

        BooleanObject () {}
        BooleanObject (const std::string &n) : name (n) {}
        virtual ~BooleanObject () {}

        virtual Core::VariantList run () const;

        std::string getName () const { return name; }
        void setName (const std::string &name) { this->name = name; }

        bool getObject () const { return object; }
        void setObject (bool object) { this->object = object; }

private:

        std::string name;
        bool object;

};

} // nam

#endif /* BOOLEANOBJECT_H_ */
