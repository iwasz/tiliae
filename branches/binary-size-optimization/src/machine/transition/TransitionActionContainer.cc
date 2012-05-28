/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TransitionActionContainer.h"

namespace Machine {

using namespace ::boost;
using namespace ::boost::multi_index;

ActionList TransitionActionContainer::get (const std::string &f, const std::string &t) const
{
        std::pair <Container::iterator, Container::iterator> p = container.equal_range (boost::make_tuple (f, t));

        ActionList ret;

        for (Container::iterator i = p.first; i != p.second; i++) {
                Ptr <TransitionAction> ta = *i;
                ret.push_back (ta->getAction ());
        }

        return ret;
}

}
