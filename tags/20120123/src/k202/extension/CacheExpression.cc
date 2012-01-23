/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include "CacheExpression.h"
//#define DBG 1

namespace k202 {

using namespace Core;

Core::Variant CacheExpression::evaluate (Context *ctx)
{
        VariantMap::iterator i = level1->find (key);

        if (i == level1->end ()) {
                Variant v = expression->evaluate (ctx);
                level1->operator [] (key) = v;
                return v;
#if DBG
                std::cerr << "MISS [" << key << "]" << std::endl;
#endif
        }
        else {
                return i->second;
#if DBG
                std::cerr << "HIT [" << key << "]" << std::endl;
#endif
        }
}

}
