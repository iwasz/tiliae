/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include "MethodPlugin.h"
#include "path/Path.h"
#include "../../core/variant/Variant.h"
#include "../../reflection/model/Class.h"
#include "../../reflection/model/Method.h"
#include "../../reflection/Manager.h"
#include "../../reflection/ReflectionTools.h"
#include "../../beanWrapper/IBeanWrapper.h"
#include "../../core/DebugContext.h"

/****************************************************************************/

namespace Wrapper {
using Core::StringList;
using Core::Variant;
using Core::DebugContext;
using Reflection::ReflectionTools;
using namespace Common;

/****************************************************************************/

Ptr <Reflection::Class> MethodPlugin::getClass (const Variant &bean, const IPath *path) const
{
        // Sprawdz, czy bean w ogole cos zawiera. Moze nic nie zawierac, czyli ze w mapie map nie bylo obiektu glownego.
        if (!path->countSegments () || bean.isNone ())
                return Ptr <Reflection::Class> ();

        // Kazdy nastepny element wymaga juz uzycia reflexji:
        return Reflection::Manager::classForType (bean.getTypeInfo ());
}

/****************************************************************************/

Variant MethodPlugin::get (const Variant &bean,
                        IPath *path,
                        bool *error,
                        DebugContext *ctx,
                        Editor::IEditor *editor) const
{
        assert (path);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "MethodPlugin::get "
                << path << ", path.countSegments = " << path->countSegments () << std::endl;
#endif

        Ptr <Reflection::Class> cls = getClass (bean, path);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << (unsigned long int)cls << std::endl;
#endif

        if (!cls) {
                dcError (ctx, "MethodPlugin (Path : '" + path->toString () + "'. Nie udalo sie pobrac obiektu klasy (Class) dla nastepujacego type_info : " + std::string (bean.getTypeInfo ().name ()) + ")");
                setError (error);
                return Variant ();
        }

        // Znajdz nazwe metody i metode.
        std::string property = path->getFirstSegment ();
        Ptr <Reflection::Method> method = ReflectionTools::findMethod (cls, property);

        try {
                if (method) {

                        clearError (error);

                        if (mode & IMMEDIATE_CALL) {
                                path->cutFirstSegment ();
                                return method->invoke (bean);
                        }

                        if (mode & METHOD) {
                                path->cutFirstSegment ();
                                return Core::Variant (boost::make_shared <Handler> (bean, method));
                        }
                }
        }
        catch (Core::Exception const &e) {
                dcError (ctx, "GetPutMethodRWBeanWrapperPlugin (Path : '" +
                                path->toString () + "'). Exception from 'set' method has been thrown : " + e.what ());
                setError (error);
                return Variant ();
        }

        dcError (ctx, "MethodPlugin (Path : '" + path->toString () + "'. Can't find method with name '" + property + "' in class with name '" + cls->getName () + "')");
        setError (error);
        return Variant ();
}

/****************************************************************************/

bool MethodPlugin::set (Core::Variant *bean,
                        IPath *path,
                        const Core::Variant &objectToSet,
                        DebugContext *ctx,
                        Editor::IEditor *editor)
{
        dcError (ctx, "MethodPlugin (Path : '" + path->toString () + "'. Unsupported operation; Only 'get' works.");
        return false;
}

} // namespace

