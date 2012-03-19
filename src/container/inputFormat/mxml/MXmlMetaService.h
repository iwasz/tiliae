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
#include "Pointer.h"

namespace Container {
class MetaContainer;

/**
 * Składnia springo-podobna.
 */
class TILIAE_API MXmlMetaService {
public:

        /**
         * Tworzy strukture meta-obiektów na podstawie definicji w pliku XML.
         */
        static Ptr <MetaContainer> parseFile (std::string const &path, Ptr <MetaContainer> container = Ptr <MetaContainer> ());

};

} /* namespace Container */

#	endif /* MXMLMETASERVICE_H_ */
