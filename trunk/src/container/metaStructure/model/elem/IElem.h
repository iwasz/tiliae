///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#ifndef IELEM_H_
//#define IELEM_H_
//
//#include <list>
//#include <map>
//#include "../../../../core/Pointer.h"
//#include "../../../../core/Typedefs.h"
//#include "../../../../core/string/String.h"
//#include "../../../../core/ApiMacro.h"
//
//namespace Container {
//
//class IData;
//class IElemVisitor;
//
///**
// * Element obiektów nieskalarnych (IMeta).
// * Odzwierciedla element obiektow nieskalarnych, czyli
// * przekladajac to na jezyk XML <prop>, <elem>, element
// * listy.
// * \ingroup Container
// */
//struct TILIAE_API IElem {
//        virtual ~IElem () {}
//
//        virtual Ptr <IData> getData () const = 0;
//
////        virtual Core::StringMap const &getAttributes () const = 0;
////        virtual std::string const &getAttribute (const std::string &key) const = 0;
//
//        virtual void accept (IElemVisitor *visitor) = 0;
//};
//
//typedef std::list <Ptr <IElem> > ElemList;
//typedef std::map <std::string, Ptr <IElem> > ElemMap;
//
//}
//
//#endif /* IELEM_H_ */
