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
#include "reflection/reflectAnnotations/CollectionAnnotation.h"
#include "core/ApiMacro.h"

namespace StateMachine {

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
REFLECTION_COLLECTION (ActionList)

typedef std::map <std::string, Ptr <IAction> > ActionMap;
REFLECTION_COLLECTION (ActionMap)

}

#endif /* IACTION_H_ */
