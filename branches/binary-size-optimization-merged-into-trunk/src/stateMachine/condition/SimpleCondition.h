/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SIMPLECONDITION_H_
#define SIMPLECONDITION_H_

#include "ICondition.h"
#include "../../core/Typedefs.h"
#include "../../core/Pointer.h"
#include "../../core/string/String.h"
#include "../../core/ApiMacro.h"

namespace StateMachine {

/**
 * To jest klasa implementująca w prosty sposób interfejs ICondition.
 * Nalezy ustawić jej parametry (params) i wówczas metoda chech sprawdzi,
 * czy params są ustawione w context (isNone musi być false). Innymi słowy,
 * czy da się pobrać z kontekstu obiekty o kluczach z params i czy te
 * obiekty nie są pustymi wariantami.
 *
 * Jednym słowem ta klasa jest równoważna z zapisem PARAM1 && PARAM2 &&
 * ...
 * \ingroup StateMachine
 */
class TILIAE_API SimpleCondition : public ICondition {
public:

        SimpleCondition () {}
        SimpleCondition (const Core::StringList &p) : params (p) {}
        virtual ~SimpleCondition () {}

        static Ptr <SimpleCondition> create () { return Ptr <SimpleCondition> (new SimpleCondition); }
        static Ptr <SimpleCondition> create (const Core::StringList &p) { return Ptr <SimpleCondition> (new SimpleCondition (p)); }
        static Ptr <SimpleCondition> create (const std::string &p1,
                                             const std::string &p2 = std::string (),
                                             const std::string &p3 = std::string (),
                                             const std::string &p4 = std::string (),
                                             const std::string &p5 = std::string ());

        virtual bool check (MachineContext *context);

        Core::StringList getParams () const { return params; }
        void setParams (const Core::StringList &params) { this->params = params; }
        void addParam (const std::string &param) { params.push_back (param); }
//        void addParams (const Core::StringList &params) { this->params.addAll (params); }
        void removeParam (const std::string &param) { params.remove (param); }

private:

        Core::StringList params;

};

} // nam

#endif /* SIMPLECONDITION_H_ */
