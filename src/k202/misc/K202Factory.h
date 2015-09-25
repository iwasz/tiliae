/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/


#ifndef K202_FACTORIES_H_
#define K202_FACTORIES_H_

#include "reflection/Reflection.h"
#include "factory/IFactory.h"
#include "ReflectionParserAnnotation.h"

namespace k202 {

/**
 * K202 IOC container supprot.
 */
struct TILIAE_API __tiliae_reflect__ K202Factory : public Factory::IFactory {

        virtual ~K202Factory () {}
        virtual Core::Variant create (const Core::VariantMap &parameters, Core::DebugContext *context = NULL) const;

        REFLECTION_END_ (K202Factory)
};

}

#endif /* TESTFACTORIES_H_ */
