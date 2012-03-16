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

class TILIAE_API MXmlMetaService {
public:

        void parse (std::string const &path);

};

} /* namespace Container */

#	endif /* MXMLMETASERVICE_H_ */
