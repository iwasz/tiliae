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
#include "../../common/Context.h"
#include "../../beanWrapper/IBeanWrapper.h"

/****************************************************************************/

namespace Wrapper {
using Reflection::Class;
using Reflection::Method;
using Reflection::Manager;
using Reflection::ClassList;
using Core::StringList;
using Core::Variant;
using Core::VariantVector;
using namespace Common;

/****************************************************************************/

Variant GetPutMethodRWBeanWrapperPlugin::get (const Variant &bean,
                                              IPath *path,
                                              Context *ctx,
                                              Editor::IEditor *editor) const
{
        assert (path);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << !path->countSegments () << std::endl;
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << bean.isNone () << std::endl;
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << can_cast <IPropertyAccessor *> (bean) << std::endl;
#endif

        // Sprawdz, czy bean w ogole cos zawiera. Moze nic nie zawierac, czyli ze w mapie map nie bylo obiektu glownego.
        if (!path->countSegments () || bean.isNone ()) {
                error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Condition : !path->countSegments () || bean.isNone () || can_cast <IPropertyAccessor *> (bean) failed.')");
                return Variant ();
        }

        // Kazdy nastepny element wymaga juz uzycia reflexji:
        Ptr <Reflection::Class> cls = Reflection::Manager::classForType (bean.getTypeInfo ());

        if (!cls) {
                error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Nie udalo sie pobrac obiektu klasy (Class) dla nastepujacego type_info : " + std::string (bean.getTypeInfo ().name ()) + ")");
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

                if (greedy) {
                        ret = method->invoke (bean, Core::Variant (path->toString ()));

                        if (!ret.isNone ()) {
                                path->clear ();
                        }
                }
                else {
                        ret = method->invoke (bean, Core::Variant (path->getFirstSegment ()));

                        if (!ret.isNone ()) {
                                // Zdejmij token kiedy uda sie zwrocic (znalezc) wlasciwy obiekt.
                                path->cutFirstSegment ();
                        }
                }


                return ret;
        }

        error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. )");
        return Variant ();
}

/****************************************************************************/

bool GetPutMethodRWBeanWrapperPlugin::set (Core::Variant *bean,
                                           IPath *path,
                                           const Core::Variant &objectToSet,
                                           Context *ctx,
                                           Editor::IEditor *editor)
{
        assert (path);
        assert (bean);

        // Sprawdz, czy bean w ogole cos zawiera. Moze nic nie zawierac, czyli ze w mapie map nie bylo obiektu glownego.
        if (!path->countSegments () || bean->isNone ()) {
                error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Condition : !path->countSegments () || bean->getType () == Core::NONE || can_cast <IPropertyAccessor *> (*bean) failed.')");
                return false;
        }

        // Kazdy nastepny element wymaga juz uzycia reflexji:
        Ptr <Reflection::Class> cls = Reflection::Manager::classForType (bean->getTypeInfo ());

        if (!cls) {
                error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Failed to get Class objest instance for type_info : " + std::string (bean->getTypeInfo ().name ()));
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

                // Zdejmij token kiedy uda sie zwrocic (znalezc) wlasciwy obiekt.
                path->cutFirstSegment ();

                if (editor) {
                        Variant output;
                        output.setTypeInfo (method->getType ());
                        editor->convert (objectToSet, &output, ctx);
                        params.push_back ((!output.isNone () ? output : objectToSet));
                }
                else {
                        params.push_back (objectToSet);
                }

                method->invoke (*bean, &params);
                return true;
        }

        error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Failed to get method 'set' for class '" + cls->getName () + "'");
        return false;
}

/****************************************************************************/

bool GetPutMethodRWBeanWrapperPlugin::add (Core::Variant *bean,
                                           IPath *path,
                                           const Core::Variant &objectToSet,
                                           Common::Context *ctx,
                                           Editor::IEditor *editor)
{
        assert (bean);
        assert (path);

        // Sprawdz, czy bean w ogole cos zawiera. Moze nic nie zawierac, czyli ze w mapie map nie bylo obiektu glownego.
        if (bean->isNone ()) {
                error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "GetPutMethodRWBeanWrapperPlugin::add : path : '" + path->toString () + "'. bean->isNone ()");
                return false;
        }

        if (path->countSegments () != 0) {
                error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "GetPutMethodRWBeanWrapperPlugin::add : path : '" + path->toString () + "'. path->countSegments () != 0");
                return false;
        }

        // Kazdy nastepny element wymaga juz uzycia reflexji:
        Ptr <Reflection::Class> cls = Reflection::Manager::classForType (bean->getTypeInfo ());

        if (!cls) {
                error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "GetPutMethodRWBeanWrapperPlugin (Path : '" + path->toString () + "'. Failed to get Class objest instance for type_info : " + std::string (bean->getTypeInfo ().name ()));
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
                        editor->convert (objectToSet, &output, ctx);
                        method->invoke (*bean, output);
                }
                else {
                        method->invoke (*bean, objectToSet);
                }

                return true;
        }

        error (ctx, BeanWrapperException, Common::UNDEFINED_ERROR, "GetPutMethodRWBeanWrapperPlugin::add (Path : '" + path->toString () + "'. Failed to get method 'add' for class '" + cls->getName () + "'");
        return false;
}

} // namespace

