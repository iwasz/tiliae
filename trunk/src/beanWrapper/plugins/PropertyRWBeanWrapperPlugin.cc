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
#include "../../core/Context.h"
#include "../../beanWrapper/IBeanWrapper.h"

/****************************************************************************/

namespace Wrapper {
using Core::StringList;
using Core::Variant;
using Core::Context;
using Core::VariantVector;
using Reflection::ReflectionTools;
using namespace Common;

/****************************************************************************/

Ptr <Reflection::Class> PropertyRWBeanWrapperPlugin::getClass (const Variant &bean, const IPath *path) const
{
        // Sprawdz, czy bean w ogole cos zawiera. Moze nic nie zawierac, czyli ze w mapie map nie bylo obiektu glownego.
        if (!path->countSegments () || bean.isNone ())
                return Ptr <Reflection::Class> ();

        // Kazdy nastepny element wymaga juz uzycia reflexji:
        return Reflection::Manager::classForType (bean.getTypeInfo ());
}

/****************************************************************************/

Variant PropertyRWBeanWrapperPlugin::get (const Variant &bean,
                                        IPath *path,
                                        Context *ctx,
                                        Editor::IEditor *) const
{
        assert (path);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "PropertyRWBeanWrapperPlugin::get "
                << path << ", path.countSegments = " << path->countSegments () << std::endl;
#endif

        Ptr <Reflection::Class> cls = getClass (bean, path);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << (unsigned long int)cls << std::endl;
#endif

        if (!cls) {
                error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "PropertyRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Nie udalo sie pobrac obiektu klasy (Class) dla nastepujacego type_info : " + std::string (bean.getTypeInfo ().name ()) + ")");
                return Variant ();
        }

        // Znajdz getter:
        std::string property = path->getFirstSegment ();
        Ptr <Reflection::Method> getter = ReflectionTools::findGetter (cls, property);

        if (!getter) {
                error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "PropertyRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Class '" + cls->getName () + "' does not have getter for property with name '" + property + "').");
                return Variant ();
        }

        path->cutFirstSegment ();

        try {
                return getter->invoke (bean);
        }
        catch (Core::Exception const &e) {
                error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "PropertyRWBeanWrapperPlugin (Path : '" +
                                path->toString () + "'). Exception from 'get' method has been thrown : " + e.what ());
                return Variant ();
        }
}

/****************************************************************************/

bool PropertyRWBeanWrapperPlugin::set (Core::Variant *bean,
                                       IPath *path,
                                       const Core::Variant &objectToSet,
                                       Context *ctx,
                                       Editor::IEditor *editor)
{
#if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "PropertyRWBeanWrapperPlugin::get "
                << path << ", path.countSegments = " << path->countSegments () << std::endl;
#endif

        assert (path);

        Ptr <Reflection::Class> cls = getClass (*bean, path);

        if (!cls) {
                error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "PropertyRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Nie udalo sie pobrac obiektu klasy (Class) dla nastepujacego type_info : " + std::string (bean->getTypeInfo ().name ()) + ")");
                return false;
        }

        // Znajdz getter:
        std::string property = path->getFirstSegment ();
        Ptr <Reflection::Method> setter = ReflectionTools::findSetter (cls, property);

        if (!setter) {
                error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "PropertyRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Class '" + cls->getName () + "' does not have setter for property with name '" + property + "').");
        	return false;
        }

        path->cutFirstSegment ();

        try {
                if (editor) {
                        Variant output;
                        output.setTypeInfo (setter->getType ());
                        editor->convert (objectToSet, &output, ctx);
                        setter->invoke (*bean, (!output.isNone () ? output : objectToSet));
                }
                else {
                        setter->invoke (*bean, objectToSet);
                }

                return true;
        }
        catch (Core::Exception const &e) {
                error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "PropertyRWBeanWrapperPlugin (Path : '" +
                                path->toString () + "'). Exception from 'set' method has been thrown : " + e.what ());
                return false;
        }

        return true;
}

} // namespace

