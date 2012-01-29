/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include "GetPutMethodRWBeanWrapperPlugin.h"
#include "IPropertyAccessor.h"
#include "path/Path.h"
#include "../../reflection/Manager.h"
#include "../../core/DebugContext.h"
#include "../../beanWrapper/IBeanWrapper.h"
#include "../beanWrapper/BeanWrapper.h"

/****************************************************************************/

namespace Wrapper {
using Reflection::Class;
using Reflection::Method;
using Reflection::Manager;
using Reflection::ClassList;
using Core::StringList;
using Core::Variant;
using Core::VariantVector;
using Core::DebugContext;
using namespace Common;

/****************************************************************************/

Variant GetPutMethodRWBeanWrapperPlugin::get (const Variant &bean,
                                              IPath *path,
                                              bool *error,
                                              DebugContext *ctx,
                                              Editor::IEditor *editor) const
{
        assert (path);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << !path->countSegments () << std::endl;
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << bean.isNone () << std::endl;
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << can_cast <IPropertyAccessor *> (bean) << std::endl;
#endif

        // Sprawdz, czy bean w ogole cos zawiera. Moze nic nie zawierac, czyli ze w mapie map nie bylo obiektu glownego.
        if (/*!path->countSegments () || */bean.isNone ()) {
                dcError (ctx, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Condition : !path->countSegments () || bean.isNone () || can_cast <IPropertyAccessor *> (bean) failed.')");
                setError (error);
                return Variant ();
        }

        // Kazdy nastepny element wymaga juz uzycia reflexji:
        Ptr <Reflection::Class> cls = Reflection::Manager::classForType (bean.getTypeInfo ());

        if (!cls) {
                dcError (ctx, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Nie udalo sie pobrac obiektu klasy (Class) dla nastepujacego type_info : " + std::string (bean.getTypeInfo ().name ()) + ")");
                setError (error);
                return Variant ();
        }

        // Pobiera domyślną metodę get - jeśli jest więcej niż jedna, to zachowanie jest niezdefiniowane.
        Ptr <Reflection::Method> method = cls->getMethod ("get");

#if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << *path << ", " <<
                bean.getTypeInfo ()->name () << ", " << cls->getName () << ", " << (unsigned int)method << std::endl;
#endif

        if (method) {

#if 0
                std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "Method get ()" << std::endl;
#endif

                Variant ret;

                try {
                        ret = method->invoke (bean, Core::Variant (path->getFirstSegment ()));
                }
                catch (Core::Exception const &e) {
                        dcError (ctx, "GetPutMethodRWBeanWrapperPlugin (Path : '" +
                                        path->toString () + "'). Exception from 'get' method has been thrown : " + e.what ());
                        setError (error);
                        return Variant ();
                }

                if (!ret.isNone ()) {
                        // Zdejmij token kiedy uda sie zwrocic (znalezc) wlasciwy obiekt.
                        path->cutFirstSegment ();
                }

                clearError (error);
                return ret;
        }

        dcError (ctx, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. )");
        setError (error);
        return Variant ();
}

/****************************************************************************/

Core::Variant GetPutMethodRWBeanWrapperPlugin::iterator (const Core::Variant &bean,
                                                         Common::IPath *path,
                                                         bool *error,
                                                         Core::DebugContext *ctx) const
{
        assert (path);

        if (path->countSegments ()) {
                dcError (ctx, "GetPutMethodRWBeanWrapperPlugin::iterator fatal. Path should be empty at this stage : (Path : '" + path->toString () + "'.");
                setError (error);
                return Variant ();
        }

        // Sprawdz, czy bean w ogole cos zawiera. Moze nic nie zawierac, czyli ze w mapie map nie bylo obiektu glownego.
        if (bean.isNone ()) {
                dcError (ctx, "GetPutMethodRWBeanWrapperPlugin::iterator (Path : '" + path->toString () + "'. bean is NONE.");
                setError (error);
                return Variant ();
        }

        // Kazdy nastepny element wymaga juz uzycia reflexji:
        Ptr <Reflection::Class> cls = Reflection::Manager::classForType (bean.getTypeInfo ());

        if (!cls) {
                dcError (ctx, "GetPutMethodRWBeanWrapperPlugin::iterator (Path : '" + path->toString () + "'. Nie udalo sie pobrac obiektu klasy (Class) dla nastepujacego type_info : " + std::string (bean.getTypeInfo ().name ()) + ")");
                setError (error);
                return Variant ();
        }

        // Pobiera domyślną metodę get - jeśli jest więcej niż jedna, to zachowanie jest niezdefiniowane.
        Ptr <Reflection::Method> method = cls->getMethod ("iterator");

        if (!method) {
                dcError (ctx, "GetPutMethodRWBeanWrapperPlugin::iterator. No 'iterator' method found (Path : '" + path->toString () + "'. )");
                setError (error);
                return Variant ();
        }

        try {
                clearError (error);
                return method->invoke (bean);
        }
        catch (std::exception const &e) {
                dcError (ctx, std::string ("GetPutMethodRWBeanWrapperPlugin::iterator. Exception during method call : ") + e.what ());
                setError (error);
        }

        return Core::Variant ();
}

/****************************************************************************/

bool GetPutMethodRWBeanWrapperPlugin::set (Core::Variant *bean,
                                           IPath *path,
                                           const Core::Variant &objectToSet,
                                           DebugContext *ctx,
                                           Editor::IEditor *editor)
{
        assert (path);
        assert (bean);

        // Sprawdz, czy bean w ogole cos zawiera. Moze nic nie zawierac, czyli ze w mapie map nie bylo obiektu glownego.
        if (/*!path->countSegments () || */bean->isNone ()) {
                dcError (ctx, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Condition : bean->getType () == Core::NONE || can_cast <IPropertyAccessor *> (*bean) failed.')");
                return false;
        }

        // Kazdy nastepny element wymaga juz uzycia reflexji:
        Ptr <Reflection::Class> cls = Reflection::Manager::classForType (bean->getTypeInfo ());

        if (!cls) {
                dcError (ctx, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Failed to get Class objest instance for type_info : " + std::string (bean->getTypeInfo ().name ()));
                return false;
        }

        // Znajdz metode set - domyślną. Jeśli jest więcej niż jedna, to zachowanie niezdefiniowane...
        Ptr <Reflection::Method> method = cls->getMethod ("set");

        if (method) {

                VariantVector params;
                params.push_back (Core::Variant (path->getFirstSegment ()));

#               if 0
                std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << path->getFirstSegment () << std::endl;
                std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << vcast <String> (objectToSet) << std::endl;
#endif

                // Uruchomienie metody, złapanie ewentualnych wyjątków, zalogowanie ich po cichu..
                try {
                        // Uruchomienie edytora.
                        if (editor) {
                                Variant output;
                                output.setTypeInfo (method->getType ());

                                if (!editor->convert (objectToSet, &output, ctx)) {
                                        dcError (ctx, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'). Editor failed.");
                                        return false;
                                }

                                params.push_back ((!output.isNone () ? output : objectToSet));
                        }
                        else {
                                params.push_back (objectToSet);
                        }

                        method->invoke (*bean, &params);
                }
                catch (Core::Exception const &e) {
                        dcError (ctx, "GetPutMethodRWBeanWrapperPlugin (Path : '" +
                                        path->toString () + "'). Exception from 'set' method has been thrown : " + e.what ());
                        return false;
                }

                // Zdejmij token kiedy uda sie zwrocic (znalezc) wlasciwy obiekt.
                path->cutFirstSegment ();

                return true;
        }

        dcError (ctx, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Failed to get method 'set' for class '" + cls->getName () + "'");
        return false;
}

/****************************************************************************/

bool GetPutMethodRWBeanWrapperPlugin::add (Core::Variant *bean,
                                           IPath *path,
                                           const Core::Variant &objectToSet,
                                           Core::DebugContext *ctx,
                                           Editor::IEditor *editor)
{
        assert (bean);
        assert (path);

        // Sprawdz, czy bean w ogole cos zawiera. Moze nic nie zawierac, czyli ze w mapie map nie bylo obiektu glownego.
        if (bean->isNone ()) {
                dcError (ctx, "GetPutMethodRWBeanWrapperPlugin::add : path : '" + path->toString () + "'. bean->isNone ()");
                return false;
        }

        if (path->countSegments () != 0) {
                dcError (ctx, "GetPutMethodRWBeanWrapperPlugin::add : path : '" + path->toString () + "'. path->countSegments () != 0");
                return false;
        }

        // Kazdy nastepny element wymaga juz uzycia reflexji:
        Ptr <Reflection::Class> cls = Reflection::Manager::classForType (bean->getTypeInfo ());

        if (!cls) {
                dcError (ctx, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Failed to get Class objest instance for type_info : " + std::string (bean->getTypeInfo ().name ()));
                return false;
        }

        // Znajdz metode add - domyślną. Jeśli jest więcej niż jedna, to zachowanie niezdefiniowane...
        Ptr <Reflection::Method> method = cls->getMethod ("add");

        if (method) {

#               if 0
                std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << path->getFirstSegment () << std::endl;
                std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << vcast <String> (objectToSet) << std::endl;
#endif

                if (editor) {
                        Variant output;
                        output.setTypeInfo (method->getType ());

                        if (!editor->convert (objectToSet, &output, ctx)) {
                                dcError (ctx, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'). Editor failed.");
                                return false;
                        }

                        method->invoke (*bean, output);
                }
                else {
                        method->invoke (*bean, objectToSet);
                }

                return true;
        }

        dcError (ctx, "GetPutMethodRWBeanWrapperPlugin::add (Path : '" + path->toString () + "'. Failed to get method 'add' for class '" + cls->getName () + "'");
        return false;
}

} // namespace

