/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IEXTENSION_H_
#define IEXTENSION_H_

#include "k202/expression/IExpression.h"
#include "k202/expression/ContextDependentSimple.h"
#include "k202/expression/ExpressionCollection.h"

namespace k202 {

/**
 * Do kompilatora rozszerzenia. Na przykład optymalizacja.
 */
class IExtension {
public:
        virtual ~IExtension () {}

        /// Podczas zdejmowania ze stosu. Po zdjęciu przechodzi przez to.
        virtual Ptr <IExpression> popStack (Ptr <IExpression>) = 0;
        virtual Ptr <IExpression> onProperty (Ptr <Property> p, ExpressionStack *s, const std::string &k) = 0;

};

}

#	endif /* IEXTENSION_H_ */
