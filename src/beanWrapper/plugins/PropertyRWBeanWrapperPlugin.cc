/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include "PropertyRWBeanWrapperPlugin.h"
#include "path/Path.h"
#include "../../reflection/Manager.h"
#include "../../reflection/model/Class.h"
#include "../../reflection/model/Method.h"
#include "../../reflection/ReflectionTools.h"
#include "../../core/Typedefs.h"
#include "../../core/DebugContext.h"
#include "../../beanWrapper/IBeanWrapper.h"
#include "../beanWrapper/BeanWrapper.h"

/****************************************************************************/

namespace Wrapper {
using Core::StringList;
using Core::Variant;
using Core::DebugContext;
using Core::VariantVector;
using Reflection::ReflectionTools;
using namespace Common;

/****************************************************************************/

Reflection::Class *PropertyRWBeanWrapperPlugin::getClass (const Variant &bean, const IPath *path) const
{
        // Sprawdz, czy bean w ogole cos zawiera. Moze nic nie zawierac, czyli ze w mapie map nie bylo obiektu glownego.
        if (!path->countSegments () || bean.isNone ())
                return NULL;

        // Kazdy nastepny element wymaga juz uzycia reflexji:
        return Reflection::Manager::classForType (bean.getTypeInfo ());
}

/****************************************************************************/

Variant PropertyRWBeanWrapperPlugin::get (const Variant &bean,
                                        IPath *path,
                                        bool *error,
                                        DebugContext *ctx,
                                        Editor::IEditor *) const
{
        assert (path);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "PropertyRWBeanWrapperPlugin::get "
                << path << ", path.countSegments = " << path->countSegments () << std::endl;
#endif

        Reflection::Class *cls = getClass (bean, path);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << (unsigned long int)cls << std::endl;
#endif

        if (!cls) {
                dcError (ctx, "PropertyRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Nie udalo sie pobrac obiektu klasy (Class) dla nastepujacego type_info : " + std::string (bean.getTypeInfo ().name ()) + ")");
                setError (error);
                return Variant ();
        }

        // Znajdz getter:
        std::string property = path->getFirstSegment ();
        Reflection::Method *getter = ReflectionTools::findGetter (cls, property);

        if (!getter) {
                dcError (ctx, "PropertyRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Class '" + cls->getName () + "' does not have getter for property with name '" + property + "').");
                setError (error);
                return Variant ();
        }

        path->cutFirstSegment ();

        try {
                clearError (error);
                return getter->invoke (bean);
        }
        catch (Core::Exception const &e) {
                ctx->addContext (e.getContext ());
                dcError (ctx, "PropertyRWBeanWrapperPlugin (Path : '" +
                                path->toString () + "'). Exception from 'get' method has been thrown.");
                setError (error);
                return Variant ();
        }
        catch (std::exception const &e) {
                dcError (ctx, "PropertyRWBeanWrapperPlugin (Path : '" +
                                path->toString () + "'). Exception from 'get' method has been thrown : " + e.what ());
                setError (error);
                return Variant ();
        }
}

/****************************************************************************/

bool PropertyRWBeanWrapperPlugin::set (Core::Variant *bean,
                                       IPath *path,
                                       const Core::Variant &objectToSet,
                                       DebugContext *ctx,
                                       Editor::IEditor *editor)
{
#if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "PropertyRWBeanWrapperPlugin::get "
                << path << ", path.countSegments = " << path->countSegments () << std::endl;
#endif

        assert (path);

        Reflection::Class *cls = getClass (*bean, path);

        if (!cls) {
                dcError (ctx, "PropertyRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Nie udalo sie pobrac obiektu klasy (Class) dla nastepujacego type_info : " + std::string (bean->getTypeInfo ().name ()) + ")");
                return false;
        }

        // Znajdz getter:
        std::string property = path->getFirstSegment ();
        Reflection::Method *setter = ReflectionTools::findSetter (cls, property);

        if (!setter) {
                dcError (ctx, "PropertyRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Class '" + cls->getName () + "' does not have setter for property with name '" + property + "').");
        	return false;
        }

        path->cutFirstSegment ();

        try {
                if (editor) {
                        Variant output;
                        output.setTypeInfo (setter->getType ());

                        dcBegin (ctx);

                        if (!editor->convert (objectToSet, &output, ctx)) {
                                dcError (ctx, "PropertyRWBeanWrapperPlugin (Path : '" + path->toString () + "'). Editor failed.");
                                return false;
                        }

                        setter->invoke (*bean, (!output.isNone () ? output : objectToSet));

                        /*
                         * Rolbakujemy dopiero tu, bo tu wiemy, ze invoke nie zrzuciło wyjatku. Edytor mógł przecierz
                         * skonwertować input na coś bezsensownego i wtedy chcemy wiedziec co to było.
                         */
                        dcRollback (ctx);
                }
                else {
                        setter->invoke (*bean, objectToSet);
                }
        }
        catch (Core::Exception const &e) {
                ctx->addContext (e.getContext ());
                dcError (ctx, "PropertyRWBeanWrapperPlugin (Path : '" +
                                path->toString () + "'). Exception from 'set' method has been thrown.");
                return false;
        }
        catch (std::exception const &e) {
                dcError (ctx, "PropertyRWBeanWrapperPlugin (Path : '" +
                                path->toString () + "'). Exception from 'set' method has been thrown : " + e.what () + ".");
                return false;
        }

        return true;
}

} // namespace

