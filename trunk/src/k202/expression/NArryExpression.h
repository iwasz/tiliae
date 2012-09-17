/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef N_ARRY_EXPRESSION_H
#define N_ARRY_EXPRESSION_H

#include "ExpressionCollection.h"
#include "IExpression.h"
#include "core/Pointer.h"

namespace k202 {

/**
 * Function, ==operator, logic negation etc.
 */
class NArryExpression : public IExpression {
public:

        NArryExpression (unsigned int p) : arity (p) {}
        virtual ~NArryExpression () {}

        unsigned int getArity () const { return arity; }
        void setArity (unsigned int i) { arity = i; }

        const ExpressionList &getArgs () const { return args; }
        void addArgFront (Ptr <IExpression> ex);
        void addArgBack (Ptr <IExpression> ex);

private:

        unsigned int arity;
        // TODO Vector!
        ExpressionList args;

};

}

#endif /* PLACEHOLDER_H_ */
