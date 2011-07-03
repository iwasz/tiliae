/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include "WrapperCommons.h"

namespace Reflection {

void checkArgList (Core::VariantVector const *list, unsigned int size)
{
        if (!list) {
                if (!size) {
                        return;
                }
                else {
                        throw WrapperException (std::string ("Wrong number of arguments. Is : NULL-arg-list, expected : ") +
                                        boost::lexical_cast <std::string> (size));
                }
        }

        if (list->size () != size) {
                throw WrapperException (std::string ("Wrong number of arguments. Is : ") +
                                boost::lexical_cast <std::string> (list->size ()) + std::string (", expected : ") +
                                boost::lexical_cast <std::string> (size));
        }
}


void checkCollectionSize (unsigned int requestedIdx, unsigned int size)
{
        if (requestedIdx >= size) {
                throw WrapperException (std::string ("Index out of bound exception. Collection size is : ") +
                                boost::lexical_cast <std::string> (size) + std::string (", you requested : ") +
                                boost::lexical_cast <std::string> (requestedIdx));
        }
}

} // namespace
