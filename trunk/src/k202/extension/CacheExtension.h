/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CACHEEXTENSION_H_
#define CACHEEXTENSION_H_

#include "IExtension.h"
#include "core/Typedefs.h"
#include "core/ApiMacro.h"

namespace k202 {

class TILIAE_API CacheExtension : public IExtension {
public:
        virtual ~CacheExtension () {}
        static Ptr <CacheExtension> create () { return Ptr <CacheExtension> (new CacheExtension); }

        Ptr <IExpression> popStack (Ptr <IExpression> e);
        Ptr <IExpression> onProperty (Ptr <Property> p, ExpressionStack *s, const std::string &k);
        // TODO inne metody.

        void clearCache () { cache.clear (); }

private:

        Core::VariantMap cache;

};

} // nam

#	endif /* CACHEEXTENSION_H_ */
