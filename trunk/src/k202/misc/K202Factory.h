/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/


#ifndef K202_FACTORIES_H_
#define K202_FACTORIES_H_

#include <Reflection.h>
#include "../../factory/IFactory.h"

namespace k202 {

/**
 * K202 IOC container supprot.
 */
struct TILIAE_API K202Factory : public Factory::IFactory {

        virtual ~K202Factory () {}
        virtual Core::Variant create (const Core::VariantMap &parameters, Common::Context *context = NULL) const;

        e__ (K202Factory)
};

}

#endif /* TESTFACTORIES_H_ */
