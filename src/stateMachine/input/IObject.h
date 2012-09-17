/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IOBJECT_H_
#define IOBJECT_H_

#include <list>
#include "core/Pointer.h"
#include "core/ApiMacro.h"

namespace StateMachine {

/**
 * Używać całej nazwy (razem z namespace), bo mogą wyniknąć niejasności
 * o co chodzi i co to za Object.
 * \ingroup StateMachine
 */
struct TILIAE_API IObject {

        virtual ~IObject () {}

//        /**
//         * Zwraca sygnał, lub nic, jeżeli fizyczny obiekt nie spełnia
//         * zadanego kryterium.
//         */
//        virtual Core::VariantMap run () const = 0;
//
//        /**
//         * Każde pojedyncze wejście (virtual input) ma swoją nazwę. Ta
//         * nazwa będzie potem używana w maszynie stanów. Na przykład
//         * może być częścią sygnału dla maszyny jak coś w stylu NAME_EMPTY.
//         */
//        virtual Core::String getName () const = 0;

};

typedef std::list <Ptr <IObject> > ObjectList;

} // nam

#endif /* IOBJECT_H_ */
