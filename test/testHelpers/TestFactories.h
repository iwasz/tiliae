/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/


#ifndef TESTFACTORIES_H_
#define TESTFACTORIES_H_

#include "reflection/Reflection.h"
#include "factory/IFactory.h"
#include "core/variant/Variant.h"
#include "core/Typedefs.h"
#include "testHelpers/City.h"
#include "core/ApiMacro.h"

/**
 * Klasa tymczasowa - zastapi ja BeanFactory + ProxyFactory.
 */
struct TILIAE_API __tiliae_reflect__ CityFactory : public Factory::IFactory {

        virtual ~CityFactory () {}
        virtual Core::Variant create (const Core::VariantMap &parameters, Core::DebugContext *context = NULL) const
        {
                return Core::Variant (std::make_shared <City> ());
        }

        REFLECTION_END_ (CityFactory)
};

#endif /* TESTFACTORIES_H_ */
