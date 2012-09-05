/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MachineContext.h"
#include "../../core/Typedefs.h"

namespace StateMachine {

const std::string MachineContext::MACHINE_LITERAL = "MACHINE";
const std::string MachineContext::RUN_LITERAL = "RUN";
const std::string MachineContext::TRANSITION_LITERAL = "TRANSITION";

/****************************************************************************/

Core::Variant MachineContext::get (const std::string &name) const
{
        if (name == MACHINE_LITERAL && machine) {
                return Core::Variant (machine);
        }

        if (name == RUN_LITERAL && run) {
                return Core::Variant (run);
        }

        if (name == TRANSITION_LITERAL && transition) {
                return Core::Variant (transition);
        }

        Core::Variant ret;
        Core::VariantMap::const_iterator i;

        if (run) {
                i = run->find (name);
        }

        if (i != run->end ()) {
                return i->second;
        }

        if (machine) {
                i = machine->find (name);
        }

        if (i != machine->end ()) {
                return i->second;
        }

        if (transition) {
                i = transition->find (name);
        }

        if (i != transition->end ()) {
                return i->second;
        }

        return ret;
}

/****************************************************************************/

void MachineContext::set (const std::string &name, const Core::Variant &object)
{
        assert (transition);
        transition->operator [] (name) = object;
}

/****************************************************************************/

void MachineContext::setMap (Scope scope, Core::VariantMap *map)
{
        switch (scope) {
        case RUN:
                run = map;
                break;

        case MACHINE:
                machine = map;
                break;

        case TRANSITION:
                transition = map;
                break;

        default:
                break;
        }
}

/****************************************************************************/

Core::VariantMap *MachineContext::getMap (Scope scope)
{
        switch (scope) {
        case RUN:
                return run;

        case MACHINE:
                return machine;

        case TRANSITION:
                return transition;

        default:
                return NULL;
        }
}

/****************************************************************************/

void MachineContext::clearMap (Scope scope)
{
        switch (scope) {
        case RUN:
                if (run) {
                        run->clear ();
                }

                break;

        case MACHINE:
                if (machine) {
                        machine->clear ();
                }

                break;

        case TRANSITION:
                if (transition) {
                        transition->clear ();
                }

                break;

        default:
                break;
        }
}

/****************************************************************************/

std::string MachineContext::toString () const
{
        std::string ret = "MachineContext (";

//        TODO
//        if (machine) {
//                ret += " MACHINE : " + machine->toString ();
//        }
//
//        if (run) {
//                ret += " RUN : " + run->toString ();
//        }
//
//        if (transition) {
//                ret += " TRANSITION : " + transition->toString ();
//        }

        ret += ")";
        return ret;
}

}
