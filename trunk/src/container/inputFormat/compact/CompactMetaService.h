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

#ifdef ANDROID
struct AAssetManager;
#endif

namespace Container {
class MetaContainer;

struct TILIAE_API CompactMetaService {

        static Ptr <MetaContainer> parseFile (std::string const &path, Ptr <MetaContainer> container = Ptr <MetaContainer> ());

#ifdef ANDROID
        static Ptr <MetaContainer> parseAndroidAsset (AAssetManager *assetManager, std::string const &path, Ptr <MetaContainer> container = Ptr <MetaContainer> ());
#endif
};

} /* namespace Container */
#endif /* COMPACTMETASERVICE_H_ */
