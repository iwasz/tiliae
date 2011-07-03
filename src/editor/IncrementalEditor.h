///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#ifndef CHAINEDITOR_H_
//#define CHAINEDITOR_H_
//
//#include <List.h>
//#include "JEditor.h"
//
//namespace Editor {
//
///**
// * Wykonuje n konwersji przekazujac wynik jednej
// * do nastepnej. Ukrywa ten algorytm za zyklym
// * interfejsem IEditora.
// *
// * Uwaga wszystkie edytory prócz ostatniego musza
// * byc factoryEditorami lub czyms podobnym. Kazdy
// * edytor (procz ost.) dostaje pusty output i musi
// * go sobie stworzyc.
// */
//class ChainEditor : public JEditor {
//public:
//
//        virtual ~ChainEditor () {}
//        virtual void edit (const Core::Variant &input, Core::Variant *output);
//
//private:
//
//        Core::List <IEditor *> *editors;
//
//};
//
//}
//
//#endif /* CHAINEDITOR_H_ */
