///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#ifndef PROXY_EDITOR_H_
//#define PROXY_EDITOR_H_
//
//#include <Variant.h>
//#include <VariantMap.h>
//#include <Pointer.h>
//
//#include "IEditor.h"
//
//namespace Editor {
//
///**
// * Edytor, który przechowuje parametr wejściowy dla innego edytora i
// * podje go temu wewnętrznemu podczas wywołąnia convert, jeśli wejściowy
// * parametr do convert jest isNone.
// */
//class ProxyEditor : public IEditor {
//public:
//
//        ProxyEditor () {}
//        ProxyEditor (Ptr <IEditor> e, const Core::Variant &in) : editor (e), input (in) {}
//        virtual ~ProxyEditor () {}
//
//        /**
//         * Zgrabniejszy sposob tworzenia tej fabryki.
//         */
//        static Ptr <ProxyEditor> create (Ptr <IEditor> e, const Core::Variant &in)
//        {
//                return Ptr <ProxyEditor> (new ProxyEditor (e, in));
//        }
//
//        /**
//         * Jeśli in.isNone () == true, to podaje this->input. Jeśli nie,
//         * to podaje in.
//         */
//        virtual void convert (const Core::Variant &in, Core::Variant *output);
//
///*--------------------------------------------------------------------------*/
//
//        Ptr <IEditor> getEditor () const { return editor; }
//        void setEditor (Ptr <IEditor> editor) { this->editor = editor; }
//
//        Core::Variant getInput () const { return input; }
//        void setInput (const Core::Variant &input) { this->input = input; }
//
//private:
//
//        Ptr <IEditor> editor;
//        Core::Variant input;
//
//};
//
//}
//
//#endif /* PROXYEDITOR_H_ */
