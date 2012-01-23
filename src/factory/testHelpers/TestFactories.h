/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/


#ifndef TESTFACTORIES_H_
#define TESTFACTORIES_H_

#include <Reflection.h>
#include "../IFactory.h"
#include "../../core/variant/Variant.h"
#include "../../core/Typedefs.h"
#include "../../testHelpers/City.h"
#include "../../core/ApiMacro.h"

/**
 * Klasa tymczasowa - zastapi ja BeanFactory + ProxyFactory.
 */
struct TILIAE_API CityFactory : public Factory::IFactory {

        virtual ~CityFactory () {}
        virtual Core::Variant create (const Core::VariantMap &parameters, Core::Context *context = NULL) const
        {
                return Core::Variant (boost::make_shared <City> ());
        }

        REFLECTION_END_ (CityFactory)
};

#endif /* TESTFACTORIES_H_ */
