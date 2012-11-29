/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef COMPACTMETASERVICE_H_
#define COMPACTMETASERVICE_H_

#include <string>
#include "core/ApiMacro.h"
#include "core/Pointer.h"

namespace Common {
class DataSource;
}

namespace Container {
class MetaContainer;

struct TILIAE_API CompactMetaService {
        static Ptr <MetaContainer> parseFile (Common::DataSource *ds, std::string const &path, Ptr <MetaContainer> container = Ptr <MetaContainer> ());
        static Ptr <MetaContainer> parseFile (std::string const &path, Ptr <MetaContainer> container = Ptr <MetaContainer> ());
};

} /* namespace Container */
#endif /* COMPACTMETASERVICE_H_ */
