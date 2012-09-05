/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SimpleCondition.h"
#include "../../core/Typedefs.h"

namespace Machine {

Ptr <SimpleCondition> SimpleCondition::create (const std::string &p1,
                                               const std::string &p2,
                                               const std::string &p3,
                                               const std::string &p4,
                                               const std::string &p5)
{
        Ptr <SimpleCondition> sc = SimpleCondition::create ();

        if (!p1.empty ()) {
                sc->addParam (p1);
        }

        if (!p2.empty ()) {
                sc->addParam (p2);
        }

        if (!p3.empty ()) {
                sc->addParam (p3);
        }

        if (!p4.empty ()) {
                sc->addParam (p4);
        }

        if (!p5.empty ()) {
                sc->addParam (p5);
        }

        return sc;
}

/****************************************************************************/

bool SimpleCondition::check (MachineContext *context)
{
        foreach (std::string s, params) {

                bool negation = (!s.empty () && s[0] == '!');
                std::string name = s;

                if (negation) {
                        name.erase (0, 1);
                }

                if (context->get (name).isNone () != negation) {
                        return false;
                }
        }

        return true;
}

}
