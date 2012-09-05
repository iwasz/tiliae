/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EXPRESSIONCOLLECTION_H_
#define EXPRESSIONCOLLECTION_H_

#include <vector>
#include <list>
#include "../../core/Pointer.h"

namespace k202 {
class IExpression;

typedef std::list <Ptr <IExpression> > ExpressionList;
typedef std::vector <Ptr <IExpression> > ExpressionStack;

}

#endif /* EXPRESSIONCOLLECTION_H_ */
