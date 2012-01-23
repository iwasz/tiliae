/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <List.h>

#ifndef RULELIST_H_
#define RULELIST_H_

namespace Editor {

class IRule;

typedef std::list <IRule *> RuleList;

}

#endif /* RULELIST_H_ */
