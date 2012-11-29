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
#include "core/ApiMacro.h"
#include "core/Pointer.h"

#ifdef ANDROID
struct AAssetManager;
#endif

namespace Common {
class DataSource;
}

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
        static void loadDataSource (Common::DataSource *ds, std::string *xml, std::string const &path);

//#ifdef ANDROID
////        static Ptr <MetaContainer> parseAndroidAsset (AAssetManager *assetManager, std::string const &path, Ptr <MetaContainer> container = Ptr <MetaContainer> ());
////        static void loadAsset (std::string *xml, AAssetManager *assetManager, std::string const &path);
//#endif


};

} /* namespace Container */

#	endif /* MXMLMETASERVICE_H_ */
