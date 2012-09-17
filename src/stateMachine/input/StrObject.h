/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STROBJECT_H_
#define STROBJECT_H_

#include "IObject.h"
#include "core/Typedefs.h"
#include "core/string/String.h"
#include "core/ApiMacro.h"

namespace StateMachine {

/**
 * Obiekt mapujący jeden fizyczny napis na przestrzeń wejść maszyny stanów
 * skończonych. Działa tak, że podajemy fizyczy obiekt typu std::string,
 * oraz obiekt odniesienia, a StrObject mówi nam, czy obiekt wejściowy zgadza
 * się z odniesieniem, czy nie.
 * \ingroup StateMachine
 */
class TILIAE_API StrObject : public IObject {
public:

        virtual ~StrObject () {}
        virtual Core::VariantList run () const;

        std::string getName () const { return name; }
        void setName (const std::string &name) { this->name = name; }

        std::string getObject () const { return object; }
        void setObject (const std::string &object) { this->object = object; }

        std::string getMatch () const { return match; }
        void setMatch (const std::string &match) { this->match = match; }

private:

        std::string name;
        std::string object;
        std::string match;

};

} // name

#endif /* STROBJECT_H_ */
