/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef INPUT_H_
#define INPUT_H_

#include "../IMachinery.h"
#include "IObject.h"
#include "../../core/Pointer.h"
#include "../../core/ApiMacro.h"

namespace StateMachine {

/**
 * Obiekty tej klasy są łącznikiem, który spaja świat zewnętrzny
 * (jego obiekty) z maszyną stanów. Maszynerię zestawia się razem
 * w łańcuch, gdzie wyjście jednej maszyny jest podłączone do
 * wejścia następnej.
 *
 * Input jest rodzajem IMachinery dlatego, zeby dało się go umieścić
 * w łańcuchu IMachinery przed Machine i przed Output. Virtualne
 * wejścia (czyli obiekty typu IObject) ustawia się co prawda za
 * pomocą metod występujących tylko w Input, ale można też podać
 * parametr do run i zostanie on przekazany dalej (czyli do maszyny,
 * albo do następnego Input, wzbogacającego wejście o nowe parametry).
 * \ingroup StateMachine
 */
class TILIAE_API Input : public IMachinery {
public:

        virtual ~Input () {}
        virtual void run (MachineContext *context);

        ObjectList getObjectList () const { return objectList; }
        void setObjectList (const ObjectList &objectList) { this->objectList = objectList; }

        virtual void addObject (Ptr <IObject> input) { objectList.push_back (input); }
//        virtual void addObjects (const ObjectList &input) { objectList.addAll (input); }
        virtual void removeObject (Ptr <IObject> input) { objectList.remove (input); }

private:

        ObjectList objectList;

};

} // nam

#endif /* INPUT_H_ */
