/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IDATA_H_
#define IDATA_H_

#include "metaStructure/interface/IDataVisitor.h"
#include "../../../../core/string/String.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

/**
 * Jest to najbardziej elementarna (atomowa) część meta-struktur.
 * Za jej pomocą implementowane są takie pojęcia jak <ref>, <idref>,
 * <value>, i <null>. Ustawiamy je meta-elementom.
 * \ingroup Container
 */
struct TILIAE_API IData {
        virtual ~IData () {}
        virtual std::string const &getData () const = 0;
        virtual void accept (IDataVisitor *visitor) = 0;
};

}//nms

#endif /* IDATA_H_ */
