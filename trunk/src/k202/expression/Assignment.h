/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ASSIGN_EXPRESSION_H
#define ASSIGN_EXPRESSION_H

#include "ExpressionCollection.h"
#include "IExpression.h"
#include "NArryExpression.h"
#include "../../core/string/String.h"
#include "../../core/variant/Variant.h"
#include "../../core/Pointer.h"

namespace k202 {

/**
 * op=
 */
class Assignment : public NArryExpression {
public:

        Assignment () : NArryExpression (2) {}
        virtual ~Assignment () {}

        static Ptr <Assignment> create () { return Ptr <Assignment> (new Assignment ()); }

        virtual std::string toString () const;
        virtual Core::Variant evaluate (Context *);

        const IType *getType () const { return &type; }

private:

        Type <Core::Variant> type;
};

}

#endif /* PLACEHOLDER_H_ */
