/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IEXPRESSION_H_
#define IEXPRESSION_H_

#include "Type.h"
#include "core/IToStringEnabled.h"
#include "core/variant/Variant.h"

namespace k202 {

class Context;

/**
 *
 */
class IExpression : public Core::IToStringEnabled {
public:

        virtual ~IExpression () {}

        virtual Core::Variant evaluate (Context *ctx) = 0;
        virtual const IType *getType () const = 0;

        // Diagnostyka
//        virtual int getCharNumber () const = 0;
//        virtual void setCharNumber () = 0;

};

}

#endif /* IEXPRESSION_H_ */
