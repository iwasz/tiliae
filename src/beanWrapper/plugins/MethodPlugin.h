/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef METHOD_PLUGIN_H
#define METHOD_PLUGIN_H

#include "IBeanWrapperPlugin.h"
#include "../../core/variant/Variant.h"
#include "../../core/Typedefs.h"
#include "../../reflection/model/Method.h"
#include "../../core/Pointer.h"
#include "../../core/ApiMacro.h"

namespace Reflection {
class Class;
}

namespace Wrapper {

/**
 * DTO na obiekt i metodę.
 */
class TILIAE_API Handler {
public:

        Handler (const Core::Variant &v, Ptr <Reflection::Method> m) : object (v), method (m) {}
        Handler (const Handler &h) : object (h.object), method (h.method) {}

        Core::Variant getObject () const { return object; }
        Ptr <Reflection::Method> getMethod () const { return method; }

        Core::Variant invoke (Core::VariantVector *list = NULL) { return method->invoke (object, list); }

private:

        Core::Variant object;
        Ptr <Reflection::Method> method;

};

/**
 *  Plugin, ktory potrafi odpalać metod obiektów które wrapuje. Wywolanie
 *  metody get ("bla()") lub get ("bla") spowoduje uruchomienie metody bla
 *  wraporwanego obiektu lub zrzucenie wyjatku, jesli takiej metody nie ma.
 *  TODO narazie robie bez obsługi argumentów, czyli ten plugin zadziała
 *  identycznie jak PropertyRWBeanWrapperPlugin, tylko można podać dowolną
 *  metodę.
 */
class TILIAE_API MethodPlugin : public IBeanWrapperPlugin {
public:

        enum Mode { IMMEDIATE_CALL = 0x01, METHOD = 0x02/*, GETTER_SETTER = 0x04*/ };

        MethodPlugin (Mode m = IMMEDIATE_CALL) : mode (m) {}
        virtual ~MethodPlugin () {}

        virtual Core::Variant get (const Core::Variant &bean,
                                Common::IPath *path,
                                Core::Context *ctx = NULL,
                                Editor::IEditor *editor = NULL) const;

        virtual bool set (Core::Variant *bean,
        		Common::IPath *path,
        		const Core::Variant &objectToSet,
        		Core::Context *ctx = NULL,
        		Editor::IEditor *editor = NULL);

        virtual bool add (Core::Variant *,
                          Common::IPath *path,
                          const Core::Variant &,
                          Core::Context *,
                          Editor::IEditor * = NULL) { return false; }

        virtual Core::Variant iterator (const Core::Variant &bean,
                                        Common::IPath *path,
                                        Core::Context *ctx) const { return Core::Variant (); };

private:

        Ptr <Reflection::Class> getClass (const Core::Variant &bean, const Common::IPath *path) const;

private:

        Mode mode;
        REFLECTION_END_ (MethodPlugin)
};

} // namespace

#endif

