/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TRANSITIONACTIONCONTAINER_H_
#define TRANSITIONACTIONCONTAINER_H_

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include "core/Pointer.h"

#include "TransitionAction.h"

namespace StateMachine {

/**
 * Kontener, który indeksuje dodawane do niego obiekty TransitionAction
 * i umożliwia szybkie (hash-table) wyszukiwanie po nazwie stanu from
 * i nazwie stanu to (jednocześnie).
 * \ingroup StateMachine
 */
struct TransitionActionContainer {

        typedef boost::multi_index::multi_index_container<
                Ptr <TransitionAction>,
                boost::multi_index::indexed_by<
                        boost::multi_index::ordered_non_unique<
                                boost::multi_index::composite_key<
                                        TransitionAction,
                                        boost::multi_index::const_mem_fun <TransitionAction, std::string, &TransitionAction::getFromState>,
                                        boost::multi_index::const_mem_fun <TransitionAction, std::string, &TransitionAction::getToState>
                                >
                        >
                >
        > Container;

        void add (Ptr <TransitionAction> act) { container.insert (act); }
        ActionList get (const std::string &f, const std::string &t) const;

private:

        Container container;

};

}

#endif /* TRANSITIONACTIONCONTAINER_H_ */
