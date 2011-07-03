/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PROPERTYRWBEANWRAPPERPLUGIN_279553_H
#define PROPERTYRWBEANWRAPPERPLUGIN_279553_H

#include "IBeanWrapperPlugin.h"
#include "../../core/Pointer.h"
#include "../../core/variant/Variant.h"
#include "../../common/path/IPath.h"
#include "../../core/ApiMacro.h"

namespace Reflection {
class Class;
}

namespace Wrapper {

/**
 *  Plugin, ktory potrafi odczytywac i ustawiac za pomoca refleksji
 *  pola obiektow.
 */
class TILIAE_API PropertyRWBeanWrapperPlugin : public IBeanWrapperPlugin {
public:

        virtual ~PropertyRWBeanWrapperPlugin () {}

        virtual Core::Variant get (const Core::Variant &bean,
                                   Common::IPath *path,
                                   Common::Context *ctx = NULL,
                                   Editor::IEditor *editor = NULL) const;

        virtual bool set (Core::Variant *bean,
                          Common::IPath *path,
                          const Core::Variant &objectToSet,
                          Common::Context *ctx = NULL,
                          Editor::IEditor *editor = NULL);

        virtual bool add (Core::Variant *,
                          Common::IPath *path,
                          const Core::Variant &,
                          Common::Context *,
                          Editor::IEditor * = NULL) { return false; }

private:

        Ptr <Reflection::Class> getClass (const Core::Variant &bean, const Common::IPath *path) const;
};

} // namespace

#endif

