/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STRINGLITERAL_H_
#define STRINGLITERAL_H_

#include "IExpression.h"
#include "../../core/string/String.h"
#include "../../core/variant/Variant.h"
#include <boost/lexical_cast.hpp>

using boost::detail::lexical_cast;

namespace k202 {

template <typename T>
struct LiteralToStringHelper {
        static std::string toString (const T &val, const std::string &toStringName) { return toStringName + " (" + boost::lexical_cast <std::string> (val) + ")"; }
};

template <>
struct LiteralToStringHelper <Core::Variant> {
        static std::string toString (const Core::Variant &, const std::string &toStringName) { return toStringName + " ()"; }
};

/**
 * Literal constatnt for example string literal or integer.
 */
template <typename T>
class Literal : public IExpression {
public:

        Literal (const T &v, const std::string &t) : val (v), toStringName (t) {}
        virtual ~Literal () {}

        static Ptr <Literal <T> > create (const T &v, const std::string &t) { return Ptr <Literal <T> > (new Literal <T> (v, t)); }

        virtual std::string toString () const { return LiteralToStringHelper <T>::toString (val, toStringName); }
        virtual Core::Variant evaluate (Context *) { return Core::Variant (val); }

        const IType *getType () const { return &type; }


private:

        T val;
        std::string toStringName;
        Type <T> type;

};

}

#endif /* STRINGLITERAL_H_ */
