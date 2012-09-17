/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef INTOBJECT_H_
#define INTOBJECT_H_

#include "IObject.h"
#include "core/Typedefs.h"
#include "core/string/String.h"
#include "core/ApiMacro.h"

namespace StateMachine {

/**
 * Obiekt mapujący jeden fizyczny integer na przestrzeń wejść maszyny stanów
 * skończonych. Działa tak, że podajemy fizyczy obiekt typu int,
 * oraz obiekt odniesienia, a IntObject mówi nam, czy obiekt wejściowy zgadza
 * się z odniesieniem, czy nie.
 * \ingroup StateMachine
 */
class TILIAE_API IntObject : public IObject {
public:

        IntObject () : object (0), match (0) {}
        virtual ~IntObject () {}

        virtual Core::VariantList run () const;

        std::string getName () const { return name; }
        void setName (const std::string &name) { this->name = name; }

        int getObject () const { return object; }
        void setObject (int object) { this->object = object; }

        int getMatch () const { return match; }
        void setMatch (int match) { this->match = match; }

private:

        std::string name;
        int object;
        int match;

};

} // nam

#endif /* INTOBJECT_H_ */
