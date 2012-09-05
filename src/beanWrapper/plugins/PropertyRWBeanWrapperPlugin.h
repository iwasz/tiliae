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
 *  pola obiektow. Najpierw zprawdza, czy jest w klasie Field o danej
 *  nazwie, a jesli nie ma, szuka setterów i getterów.
 */
class TILIAE_API PropertyRWBeanWrapperPlugin : public IBeanWrapperPlugin {
public:

        virtual ~PropertyRWBeanWrapperPlugin () {}

        virtual Core::Variant get (const Core::Variant &bean,
                                   Common::IPath *path,
                                   bool *error,
                                   Core::DebugContext *ctx = NULL,
                                   Editor::IEditor *editor = NULL) const;

        virtual bool set (Core::Variant *bean,
                          Common::IPath *path,
                          const Core::Variant &objectToSet,
                          Core::DebugContext *ctx = NULL,
                          Editor::IEditor *editor = NULL);

        virtual bool add (Core::Variant *,
                          Common::IPath *path,
                          const Core::Variant &,
                          Core::DebugContext *,
                          Editor::IEditor * = NULL) { return false; }

        virtual Core::Variant iterator (const Core::Variant &bean,
                                        Common::IPath *path,
                                        bool *error,
                                        Core::DebugContext *ctx) const { return Core::Variant (); };

private:

        Reflection::Class *getClass (const Core::Variant &bean, const Common::IPath *path) const;

};

} // namespace

#endif

