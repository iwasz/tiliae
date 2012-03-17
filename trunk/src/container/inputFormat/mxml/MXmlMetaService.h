/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MXMLMETASERVICE_H_
#define MXMLMETASERVICE_H_

#include <string>
#include "ApiMacro.h"

namespace Container {
class MetaContainer;

class TILIAE_API MXmlMetaService {
public:

        MetaContainer *parse (std::string const &path, MetaContainer *container) const;

};

} /* namespace Container */

#	endif /* MXMLMETASERVICE_H_ */
