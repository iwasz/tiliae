/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MEGATONFACTORY_H_
#define MEGATONFACTORY_H_

#include "factory/IFactory.h"
#include "MegaTon.h"
#include "core/variant/Variant.h"
#include "core/Typedefs.h"

/**
 * Fabryka produkujaca megatonowe obiekty.
 */
struct MegaTonFactory : public Factory::IFactory {

        virtual ~MegaTonFactory () {}
        virtual Core::Variant create (const Core::VariantMap &parameters = Core::VariantMap (), Core::DebugContext *context = NULL) const
        {
                return Core::Variant (boost::make_shared <MegaTon> ());
        }
};

#endif /* MEGATONFACTORY_H_ */
