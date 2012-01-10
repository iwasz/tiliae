///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#include "MachineListener.h"
//#include "Machine.h"
//#include "../signal/Manager.h"
//#include "../core/Typedefs.h"
//
//namespace Machine {
//
//Core::Variant MachineListener::run (const Core::VariantVector &paramVector,
//                                    const Core::VariantMap &argsMap)
//{
//        machine->event (argsMap);
//        return Core::Variant ();
//}
//
///****************************************************************************/
//
//void MachineListener::setMachine (Machine *m)
//{
//        machine = m;
//        setOwnerObject (machine);
//        Signal::Manager::instance ().registerListener (this);
//
//        if (!path.empty ()) {
//                Signal::Manager::instance ().addListenerToScope (this, path);
//        }
//}
//
//} // nam
