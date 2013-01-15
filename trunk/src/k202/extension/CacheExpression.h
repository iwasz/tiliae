/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CACHEEXPRESSION_H_
#define CACHEEXPRESSION_H_

#include "k202/expression/IExpression.h"
#include "core/Typedefs.h"

namespace k202 {

/**
 *
 */
class CacheExpression : public IExpression {
public:

        CacheExpression (Ptr <IExpression> e, Core::VariantMap *cache, const std::string &k) : expression (e), level1 (cache), key (k) {}
        virtual ~CacheExpression () {}

        static Ptr <CacheExpression> create (Ptr <IExpression> e, Core::VariantMap *cache, const std::string &k) { return Ptr <CacheExpression> (new CacheExpression (e, cache, k)); }

        std::string toString () const { return std::string ("CacheExpression (") + expression->toString () + ")"; }
        Core::Variant evaluate (Context *);

        const IType *getType () const { return &type; }

private:

        Ptr <IExpression> expression;
        Type <Core::Variant> type;
        Core::VariantMap *level1;
        std::string key;
};

}

#	endif /* CACHEEXPRESSION_H_ */
