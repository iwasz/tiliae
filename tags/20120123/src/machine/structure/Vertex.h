/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef VERTEX_H_
#define VERTEX_H_

#include <string>
#include "Transition.h"

namespace Machine {

/**
 * A vertex is an abstraction of a node in a state machine graph. In general, it can be the source or destination of any number
 * of transitions.
 */
class Vertex {
public:

        virtual ~Vertex () {}

        /**
         * Vertex is a generalization of NamedElement, which has name property
         * (among others).
         */
        std::string const &getName () const { return name; }
        void setName (std::string const &n) { name = n; }

        /**
         * Outgoing transitions multimap. Single transition can be put multiple times here.
         */
        TransitionMultiMap const &getOutgoung () const { return outgoing; }
        void setOutgoing (TransitionMultiMap const &o) { outgoing = o; }

private:

        std::string name;
        TransitionMultiMap outgoing;

};

} /* namespace Machine */

#	endif /* VERTEX_H_ */
