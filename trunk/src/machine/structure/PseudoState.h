/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PSEUDOSTATE_H_
#define PSEUDOSTATE_H_

#include <vector>
#include "Vertex.h"
#include "core/Pointer.h"

namespace Machine {

/**
 *
 */
enum PseudoStateKind {
        INITIAL,        //!< INITIAL
        DEEP_HISTORY,   //!< DEEP_HISTORY
        SHALLOW_HISTORY,//!< SHALLOW_HISTORY
        JOIN,           //!< JOIN
        FORK,           //!< FORK
        JUNCTION,       //!< JUNCTION
        CHOICE,         //!< CHOICE
        ENTRY_POINT,    //!< ENTRY_POINT
        EXIT_POINT,     //!< EXIT_POINT
        TERMINATE       //!< TERMINATE
};

/**
 *
 */
class PseudoState : public Vertex {
public:
        virtual ~PseudoState () {}
};

typedef std::vector <Ptr <PseudoState> > PseudoStateVector;

} /* namespace Machine */

#	endif /* PSEUDOSTATE_H_ */
