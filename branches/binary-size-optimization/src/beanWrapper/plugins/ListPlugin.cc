///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#include <standardTypes/VariantList.h>
//#include <standardTypes/PairMap.h>
//#include <StringTools.h>
//#include <interfaces/IList.h>
//
//#include "ListPlugin.h"
//#include "path/Path.h"
//#include "BeanWrapperTool.h"
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
//Variant ListPlugin::get (const Variant &bean,
//		IPath *path,
//                Context *ctx) const
//{
//        ASSERT (path, "Pusty parametr path.");
//
//#       if 0
//        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << !path->countSegments () << std::endl;
//        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << bean.isNone () << std::endl;
//        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << !can_cast <const IList *> (bean) << std::endl;
//        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << bean.isNull () << std::endl;
//#endif
//
//        /*
//         * Sprawdz, czy bean w ogole cos zawiera. Moze nic nie zawierac,
//         * czyli ze w mapie map nie bylo obiektu glownego.
//         * TODO kiedy zwracac pusty wariant, a kiedy wyjatek? Nie moze
//         * byc tak, ze zwraca mi pusty wariant, a ja nie wiem czemu!
//         */
//        if (!path->countSegments () ||
//                        bean.isNone () ||
//                        !can_cast <const IList *> (bean) ||
//                        bean.isNull ()) {
//
//                BeanWrapperTool::setContext (ctx, false, "ListPlugin (Path : '" + path->toString () + "'. Condition : !path->countSegments () [" +
//                                             !path->countSegments () + "] || bean.isNone () [" + bean.isNone () + "] || !can_cast <const IList *> (bean) [" +
//                                             !can_cast <const IList *> (bean) + "] || bean.isNull () [" + bean.isNull () + "] failed.')");
//                return Variant ();
//        }
//
//        unsigned int index = 0;
//
//        try {
//                index = String::toUnsignedInt (path->getFirstSegment ());
//        }
//        catch (...) {
//                BeanWrapperTool::setContext (ctx, false, "ListPlugin (Path : '" + path->toString () + "'. Failed to convert string '" + path->getFirstSegment () + "' to integer.)");
//                return Variant ();
//        }
//
//        // Nie jest null, bo sprawdzenie wyzej
//        const IList *list = vcast <const IList *> (bean);
//
//        // Zdejmij token kiedy uda sie zwrocic (znalezc) wlasciwy obiekt.
//        path->cutFirstSegment ();
//        BeanWrapperTool::setContext (ctx, true, "");
//        return list->get (index);
//}
//
///****************************************************************************/
//
//bool ListPlugin::set (Core::Variant *bean,
//                      IPath *path,
//                      const Core::Variant &objectToSet,
//                      Context *ctx)
//{
//        ASSERT (path, "Pusty parametr path.");
//        ASSERT (bean, "Pusty parametr bean. Ścieżka : " + path->toString ());
//
//        if (objectToSet.isNone ()) {
//                BeanWrapperTool::setContext (ctx, false, "ListPlugin (Path : '" + path->toString () + "'. objectToSet.isNone ())");
//                return false;
//        }
//
//        if (!path->countSegments () ||
//                        bean->isNone () ||
//                        !can_cast <const IList *> (*bean) ||
//                        bean->isNull ()) {
//
//                BeanWrapperTool::setContext (ctx, false, "ListPlugin (Path : '" + path->toString () + "'. Condition : !path->countSegments () [" +
//                                             !path->countSegments () + "] || bean->isNone () [" + bean->isNone () + "] || !can_cast <const IList *> (*bean) [" +
//                                             !can_cast <const IList *> (*bean) + "] || bean->isNull () [" + bean->isNull () + "] failed.')");
//                return false;
//        }
//
//        unsigned int index = 0;
//
//        try {
//                index = String::toUnsignedInt (path->getFirstSegment ());
//        }
//        catch (...) { // TODO catch
//                BeanWrapperTool::setContext (ctx, false, "ListPlugin (Path : '" + path->toString () + "'. Failed to convert string '" + path->getFirstSegment () + "' to integer.)");
//                return false;
//        }
//
//        // Nie jest null, bo sprawdzenie wyzej
//        IList *list = vcast <IList *> (*bean);
//        list->set (index, objectToSet);
//
//        // Zdejmij token kiedy uda sie zwrocic (znalezc) wlasciwy obiekt.
//        path->cutFirstSegment ();
//        BeanWrapperTool::setContext (ctx, true, "");
//        return true;
//}
//
//} // namespace

