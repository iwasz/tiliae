/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IACTION_H_
#define IACTION_H_

#include "context/MachineContext.h"
#include "../../reflection/reflectAnnotations/CollectionAnnotation.h"
#include "../../core/ApiMacro.h"

namespace Machine {

/**
 * Akcja maszyny stanów skończonych - może być składnikiem InputAction
 * TransitionAction, lub ustawiona jako samodzielna EntryAction lub ExitAction.
 * \ingroup StateMachine
 */
class TILIAE_API IAction : public Core::Object {
public:
        virtual ~IAction () {}
        virtual void run (MachineContext *context) = 0;
};

typedef std::list <Ptr <IAction> > ActionList;
_g (ActionList)

typedef std::map <std::string, Ptr <IAction> > ActionMap;
_g (ActionMap)

}

#endif /* IACTION_H_ */
