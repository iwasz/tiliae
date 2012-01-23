/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/lexical_cast.hpp>
#include "SimpleIdGenerator.h"
#include "metaStructure/model/meta/IMeta.h"

namespace Container {

const char *SIMPLE_ID_GENERATOR_PREFIX = "ID_";

std::string SimpleIdGenerator::generate (IMeta *m) const
{
        return m->getClass() + "_" + boost::lexical_cast <std::string> (num++);
}

}
