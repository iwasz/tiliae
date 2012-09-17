/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BYTE_CODE_H__
#define BYTE_CODE_H__

#include "core/variant/Variant.h"
#include "core/Typedefs.h"
#include "core/string/String.h"
#include "core/IToStringEnabled.h"
#include "expression/ExpressionCollection.h"

namespace k202 {

class Context;

/**
 * Odpowiedzialność : "skompilowany kod wynikowy skryptu". Pozwala na uruchamianie skryptu,
 * zawiera wszystkie jego wyrażenia, zawiera kod źródłowy (a może nie).
 */
class ByteCode : public Core::IToStringEnabled {
public:

        ByteCode (const ExpressionList &expr) : expressions (expr) {}
        virtual ~ByteCode () {}

        /**
         * Runs the code. Returns value of last executed expression.
         */
        Core::Variant run (Context *ctx);

        static Ptr <ByteCode> create (const ExpressionList &expr) { return Ptr <ByteCode> (new ByteCode (expr)); }
        virtual std::string toString () const;

private:

        ExpressionList expressions;

};

}

#endif /* SCRIPT_H_ */
