///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#include <Variant.h>
//#include <IIterable.h>
//
//#include "ChainEditor.h"
//
//using namespace Core;
//
//namespace Editor {
//
//void ChainEditor::edit (const Core::Variant &input, Core::Variant *output)
//{
//        ASSERT (editors, "");
//
//        Variant tmpIn = input;
//        Variant tmpOut;
//
//        for (Core::List <IEditor *>::iterator i = editors->begin (); i != editors->end (); i++) {
//                IEditor *editor = *i;
//                editor->convert (tmpIn, &tmpOut);
//
//                // TODO to jest zupelnie zle, ale chodzi o cos takiego wlasnie.
////                if (++i != editors->end ()) {
////                        tmpIn = tmpOut;
////                        tmpOut = Variant ();
////                }
////                else {
////                        tmpOut = *out;
////                }
//        }
//}
//
//}
