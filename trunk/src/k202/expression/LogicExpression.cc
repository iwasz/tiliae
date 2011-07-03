/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>

#include "LogicExpression.h"
#include "../Exceptions.h"
#include "Type.h"

namespace k202 {

struct EqMsg {
        static const char *msg;
};

const char *EqMsg::msg = "RuntimeException : LogicEq::evaluate. Both lhs and rhs are of type not-none-variant.";

struct NeMsg {
        static const char *msg;
};

const char *NeMsg::msg = "RuntimeException : LogicNe::evaluate. Both lhs and rhs are of type not-none-variant.";

template <typename Msg>
struct Helper01 {

        static bool run (const ExpressionList &args, Context *ctx);

};

template <typename Msg>
bool Helper01<Msg>::run (const ExpressionList &args, Context *ctx)
{
        assert (args.size () == 2);
        ExpressionList::const_iterator i = args.begin ();

        Ptr <IExpression> lhs = *i++;
        Ptr <IExpression> rhs = *i;

        const IType *lhsType = lhs->getType ();
        const IType *rhsType = rhs->getType ();
        Type <Core::Variant> variantType;

        Core::Variant vLhs = lhs->evaluate (ctx);
        Core::Variant vRhs = rhs->evaluate (ctx);

        // lhs i rhs nie moga byc w jednym monencie wariatami:
        if (*lhsType == variantType && *rhsType == variantType) {

                if (vLhs.isNone () && vRhs.isNone ()) {
                        return true;
                }

                throw RuntimeException (Msg::msg);
        }

        const IType *castToType = ((*lhsType == variantType) ? (rhsType) : (lhsType));
        return castToType->equals (vLhs, vRhs);
}

/****************************************************************************/

std::string LogicEq::toString () const
{
        assert (getArgs().size () == 2);
        ExpressionList::const_iterator i1 = getArgs().begin ();
        ExpressionList::const_iterator i2 = i1; ++i2;

        return std::string ("LogicEq (") + (*i1)->toString () + ", " +
                        (*i2)->toString () + ")";
}

Core::Variant LogicEq::evaluate (Context *ctx)
{
        bool ret = Helper01 <EqMsg>::run (getArgs (), ctx);
        return Core::Variant (ret);
}

/****************************************************************************/

std::string LogicNe::toString () const
{
        assert (getArgs().size () == 2);
        ExpressionList::const_iterator i1 = getArgs().begin ();
        ExpressionList::const_iterator i2 = i1; ++i2;

        return std::string ("LogicNe (") + (*i1)->toString () + ", " +
                        (*i2)->toString () + ")";
}

/****************************************************************************/

Core::Variant LogicNe::evaluate (Context *ctx)
{
        bool ret = Helper01 <NeMsg>::run (getArgs (), ctx);
        return Core::Variant (!ret);
}

/****************************************************************************/

std::string LogicAnd::toString () const
{
        assert (getArgs().size () == 2);
        ExpressionList::const_iterator i1 = getArgs().begin ();
        ExpressionList::const_iterator i2 = i1; ++i2;

        return std::string ("LogicAnd (") + (*i1)->toString () + ", " +
                        (*i2)->toString () + ")";

}

Core::Variant LogicAnd::evaluate (Context *ctx)
{
        try {
                assert (getArgs().size () == 2);
                ExpressionList::const_iterator i = getArgs().begin ();

                Core::Variant lhs = (*i++)->evaluate (ctx);
                Core::Variant rhs = (*i)->evaluate (ctx);

                bool bLhs = ((lhs.isNone ()) ? (false) : (vcast <bool> (lhs)));
                bool bRhs = ((rhs.isNone ()) ? (false) : (vcast <bool> (rhs)));

                return Core::Variant (bLhs && bRhs);
        }
        catch (const Core::Exception &e) {
                RuntimeException n2 (e);
                n2.addMessage ("RuntimeException : LogicAnd::evaluate. Propably cannot "
                                "cast one of inner expression to bool.");
                throw n2;
        }
        catch (...) {
                throw RuntimeException ("RuntimeException : LogicAnd::evaluate. Propably cannot "
                                "cast one of inner expression to bool.");
        }
}

/****************************************************************************/

std::string LogicOr::toString () const
{
        assert (getArgs().size () == 2);
        ExpressionList::const_iterator i1 = getArgs().begin ();
        ExpressionList::const_iterator i2 = i1; ++i2;

        return std::string ("LogicOr (") + (*i1)->toString () + ", " +
                        (*i2)->toString () + ")";
}

Core::Variant LogicOr::evaluate (Context *ctx)
{
        try {
                assert (getArgs().size () == 2);
                ExpressionList::const_iterator i = getArgs().begin ();

                Core::Variant lhs = (*i++)->evaluate (ctx);
                Core::Variant rhs = (*i)->evaluate (ctx);

                bool bLhs = ((lhs.isNone ()) ? (false) : (vcast <bool> (lhs)));
                bool bRhs = ((rhs.isNone ()) ? (false) : (vcast <bool> (rhs)));

                return Core::Variant (bLhs || bRhs);
        }
        catch (const Core::Exception &e) {
                RuntimeException n2 (e);
                n2.addMessage ("RuntimeException : LogicOr::evaluate. Propably cannot "
                                "cast one of inner expression to bool.");
                throw n2;

        }
        catch (...) {
                throw RuntimeException ("RuntimeException : LogicOr::evaluate. Propably cannot "
                                "cast one of inner expression to bool.");
        }
}

/****************************************************************************/

std::string LogicNegation::toString () const
{
        assert (getArgs ().size () == 1);
        return std::string ("LogicNegation (") + getArgs ().front()->toString () + ")";

}

Core::Variant LogicNegation::evaluate (Context *ctx)
{
        Core::Variant ret = getArgs ().front ()->evaluate (ctx);

        try {
                if (ret.isNone ()) {
                        return Core::Variant (true); // !(variant-with-isNone-true)
                }

                bool val = vcast <bool> (ret);
                return Core::Variant (!val);
        }
        catch (const Core::Exception &e) {
                RuntimeException n2 (e);
                n2.addMessage ("RuntimeException : LogicNegation::evaluate. Propably cannot "
                                "cast one of inner expression to bool.");
                throw n2;
        }
        catch (...) {
                throw RuntimeException ("RuntimeException : LogicNegation::evaluate. Propably cannot "
                                "cast inner expression to bool.");
        }}

} //nam
