/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef XMLMETASERVICEFACTORY_H_
#define XMLMETASERVICEFACTORY_H_

#include <Machine.h>
#include "XmlMetaService.h"

namespace Container {

/**
 * Wyodrebniony kod do tworzenia maszyny : mózgu kontenera (no półkuli).
 * \ingroup Container
 */
struct XmlMetaServiceFactory {

        static Ptr <XmlMetaService> createXmlMetaServiceFactory ();

/*-- Tworzenie rzeczy od maszyny stanow ------------------------------------*/

        static Ptr <StateMachine::Machine> createMachine ();

};

}

#endif /* XMLMETASERVICEFACTORY_H_ */
