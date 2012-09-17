///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#include "MapPlugin.h"
//#include "common/path/ListPath.h"
//#include "BeanWrapperTool.h"
//#include "core/variant/Variant.h"
//#include "common/path/IPath.h"
//#include "Context.h"
//#include <cassert>
//
///****************************************************************************/
//
//using namespace Core;
//using namespace Reflection;
//using namespace Common;
//
///****************************************************************************/
//
//namespace Wrapper {
//
//Variant MapPlugin::get (const Variant &bean,
//		IPath *path,
//		Context *ctx) const
//{
//        assert (path);
//
//#       if 0
//        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << !path->countSegments () << std::endl;
//        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << bean.isNone () << std::endl;
//        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << !can_cast <const IMap *> (bean) << std::endl;
//        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << bean.isNull () << std::endl;
//#endif
//
//        if (!path->countSegments () ||
//                        bean.isNone () ||
//                        !ccast <const IMap *> (bean) ||
//                        bean.isNull ()) {
//
//                BeanWrapperTool::setContext (ctx, false, "MapPlugin (Path : '" + path->toString () + "'. Condition : !path->countSegments () ||bean.isNone () || !can_cast <const IMap *> (bean) || bean.isNull () failed.')");
//                return Variant ();
//        }
//
//        // Nie jest null, bo sprawdzenie wyzej
//        const IMap *map = vcast <const IMap *> (bean);
//
//        // Zdejmij token kiedy uda sie zwrocic (znalezc) wlasciwy obiekt.
//        Variant ret = map->get (vcast <Variant> (path->getFirstSegment ()));
//        BeanWrapperTool::setContext (ctx, true, "");
//        path->cutFirstSegment ();
//        return ret;
//}
//
///****************************************************************************/
//
//bool MapPlugin::set (Core::Variant *bean,
//                      IPath *path,
//                      const Core::Variant &objectToSet,
//                      Context *ctx)
//{
//        ASSERT (path, "Pusty parametr path.");
//        ASSERT (bean, "Pusty parametr bean. Ścieżka : " + path->toString ());
//
//        if (objectToSet.isNone ()) {
//                BeanWrapperTool::setContext (ctx, false, "MapPlugin (Path : '" + path->toString () + "'. objectToSet.isNone ())");
//                return false;
//        }
//
//        if (!path->countSegments () ||
//                        bean->isNone () ||
//                        !can_cast <const IMap *> (*bean) ||
//                        bean->isNull ()) {
//
//                BeanWrapperTool::setContext (ctx, false, "MapPlugin (Path : '" + path->toString () + "'. Condition : !path->countSegments () || bean->isNone () || !can_cast <const IMap *> (*bean) || bean->isNull () has failed)");
//                return false;
//        }
//
//        // Nie jest null, bo sprawdzenie wyzej
//        IMap *map = vcast <IMap *> (*bean);
//        map->set (vcast <Variant> (path->getFirstSegment ()), objectToSet);
//
//        // Zdejmij token kiedy uda sie zwrocic (znalezc) wlasciwy obiekt.
//        path->cutFirstSegment ();
//        BeanWrapperTool::setContext (ctx, true, "");
//        return true;
//}
//
//} // namespace

