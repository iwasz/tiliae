/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STACKSTATEEXTENSION_H_
#define STACKSTATEEXTENSION_H_

#include "IMachineExtension.h"
#include "../../core/Typedefs.h"
#include <deque>
#include <string>
#include "../../core/ApiMacro.h"

namespace Common {
struct ILogger;
}

namespace StateMachine {

extern TILIAE_API const std::string STACK_STATE_PLACEHOLDER_NAME;
extern TILIAE_API const std::string DEFAULT_PREV_PREFIX;
extern TILIAE_API const int STACK_STATE_MAX_DEPTH;

/**
 * Prowadzi historię stanów. Każda zmiana stanu jest odnotowywana w
 * tym pluginie. Innymi słowy : każdy następny stan jest odkładany
 * na stosie, a każde przejście z powrotem powoduje zdjęcie wierzchołka
 * ze stosu. Czyli na przykład przejścia :
 *
 * stateA -> stateB -> stateC
 *
 * Spowodują, że stos będzie wyglądał tak:
 *
 * stateC
 * stateB
 * stateA
 *
 * Następnie przejście spowrotem do stanu stateB spowoduje usunięcie
 * stanu stateC z wierzchołka. Dzięki temu zawsze wiadomo jak wykonać
 * zmiany stanów w odwrotnej kolejności niż poprzednio.
 *
 * Istnieje specjalny placeholder, który umożliwia przejście do stanu
 * znajdującego się poniżej w stosie, bez znajomości nazwy tego stanu
 * (czyli de facto zdjęcie wierzchołka, czyli upraszczając wykonanie POP).
 *
 * Uwaga: ten plugin ma sens tylko w przypadku, gdy stany są ułożone w
 * strukturę drzewiastą ORAZ gdy cofając się w tym drzewie stanów używamy
 * placeholdera @back, a nie normalnej nazwy stanu. W przeciwnym przypadku,
 * historia stanów bedzie puchła i puchła. Jest wprowadzone ograniczenie
 * na ilość kolejnych stanów w historii, po ktorym zostanie zrzucony wyjątek
 * i domyślnie jest to 100.
 * \ingroup StateMachine
 */
class TILIAE_API StackStateExtension : public IMachineExtension {
public:

        StackStateExtension () :
                stackMaxDepth (STACK_STATE_MAX_DEPTH),
                placeholder (STACK_STATE_PLACEHOLDER_NAME),
                previousPrefix (DEFAULT_PREV_PREFIX)
        {}
        virtual ~StackStateExtension () {}

        virtual bool checkContainsStateName (const std::string &stateName) const;
        virtual std::string translateName (const std::string &stateName) const;

        virtual Ptr <Transition> findTransition (Ptr <IState> currentState, MachineContext *context) const;
        virtual void reset (MachineContext *context, Ptr <IState> initState);

        virtual void beforeInputActions (MachineContext *context, Ptr <IState> currentState);
        virtual void afterInputActions (MachineContext *context, Ptr <IState> currentState);
        virtual void afterExitActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition);
        virtual void afterTransitionActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition);
        virtual void afterEntryActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition);

/*--------------------------------------------------------------------------*/

        Ptr<Common::ILogger> getLogger () const { return logger; }
        void setLogger (Ptr<Common::ILogger> logger) { this->logger = logger; }

        unsigned int getStackMaxDepth () const { return stackMaxDepth; }
        void setStackMaxDepth (unsigned int stackMaxDepth) { this->stackMaxDepth = stackMaxDepth; }

        std::string getPlaceholder() const { return placeholder; }
        void setPlaceholder (const std::string &placeholder) { this->placeholder = placeholder; }

        std::string getPreviousPrefix() const { return previousPrefix; }
        void setPreviousPrefix(std::string previousPrefix) { this->previousPrefix = previousPrefix; }

private:

        std::string getPreviusStateName () const;
        void run (const std::string &stateName, MachineContext *context);

private:

        typedef std::deque <std::string> StringStack;
        StringStack history;
        Ptr <Common::ILogger> logger;

        unsigned int stackMaxDepth;
        std::string placeholder;
        std::string previousPrefix;

};

struct TILIAE_API TooDeepStateNestingException : public Core::Exception {};

}

#endif /* STACKSTATEEXTENSION_H_ */
