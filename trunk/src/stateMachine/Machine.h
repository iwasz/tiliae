/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TTEE_MACHINE_H_
#define TTEE_MACHINE_H_

#include "Reflection.h"
#include "IMachinery.h"
#include "State.h"
#include "transition/Transition.h"
#include "extension/IMachineExtension.h"
#include "context/MachineContext.h"
#include "Exceptions.h"
#include "condition/K202Condition.h"
#include "MachineListener.h"
#include "../core/Typedefs.h"
#include "../core/string/String.h"
#include "../core/Pointer.h"
#include "../core/ApiMacro.h"

namespace Common {
        class ILogger;
}

namespace k202 {
        class K202;
        class CacheExtension;
}

namespace StateMachine {

class Transition;

/**
 * Maszyna stanów skończonych.
 * Dziedziczenie z interfejsu IMachinery mowi tyle, że jedna mszyna
 * może być połączona z inną, czyli że zrobi się chierarchia sub-maszyn.
 * Rodzaje połączeń mogą być też inne, czyli na nprzykład wyjście jednej
 * maszyny jest przekazywane o dobiektu klasy Output i podejmowane są
 * jakieś tam akcje.
 * \ingroup StateMachine
 */
class TILIAE_API Machine : public IMachinery {
public:
        __c (void)
        Machine () : running (true) {}

        __c (const Core::VariantMap &)
        Machine (const Core::VariantMap &mp);

        virtual ~Machine () {}

        static Ptr <Machine> create (const Core::VariantMap &mp = Core::VariantMap ());
        Ptr <K202Condition> createCondition (const std::string &sourceCode) { return Ptr <K202Condition> (new K202Condition (sourceCode, k202)); }

/*-- IMachinery ------------------------------------------------------------*/

        /**
         * Ta metoda jest zaimplementowana zgodnie z opisem dzialania
         * VFSM w ksiażce...
         */
        virtual void run (MachineContext *context);

        /**
         * Convenience method.
         */
        virtual void run (const Core::VariantMap &runScope = Core::VariantMap (),
                          const Core::VariantMap &transitionScope = Core::VariantMap ());

        /// Tylko dla ułatwienia stosowania w kontenerze.
        _m (runOnce) void runOnce () { run (); }

        std::string getCurrentStateName () const { return currentStateName; }

        std::string getInitialStateName () const { return initialStateName; }
        _m (setInitialStateName) void setInitialStateName (const std::string &initialStateName) { this->initialStateName = initialStateName; }

        MachineExtensionList getExtensionList () const { return extensionList; }
        void setExtensionList (const MachineExtensionList &extensionList) { this->extensionList = extensionList; }

        void reset ();

/*--------------------------------------------------------------------------*/

        StateMap getStates () const { return stateMap; }
        _m (setStates) void setStates (const StateList &states);
        void addState (Ptr <IState> state);
        void addStates (const StateList &states);
        void removeState (const std::string &stateName);

        /**
         * Przejścia. Jakie zostanie wykonane przejście, zależy od aktualnego stanu maszyny,
         * oraz wejść. Jeżeli maszyna znajdzie więcej niż jedno pasujące przejście, to wykonane
         * zostanie pierwsze przejście dodane do maszyny dla tych warunków (czyli kolejność
         * dodania przejść podczas konfigurowania maszyny ma znaczenie).
         */
        const TransitionActionContainer &getTransitionActions () const { return transitionActions; }
        void setTransitionActions (const TransitionActionContainer &a) { transitionActions = a; }
        void addTransitionAction (Ptr <TransitionAction> act) { transitionActions.add (act); }
        void addTransitionActions (const TransitionActionList &act);

        Ptr<Common::ILogger> getLogger () const { return logger; }
        void setLogger (Ptr<Common::ILogger> logger) { this->logger = logger; }

        Ptr <k202::K202> getK202 () const { return k202; }
        void setK202 (Ptr <k202::K202> k) { k202 = k; }

        Ptr <k202::CacheExtension> getCache () const { return cache; }
        void setCache (Ptr <k202::CacheExtension> c) { cache = c; }

        _m (setListener) void setListener (Ptr <MachineListener> l);
        _m (getListener) Ptr <MachineListener> getListener () const { return listener; }

private:

        void setCurrentStateName (const std::string &currentStateName) { this->currentStateName = currentStateName; }

        /**
         * Zwraca stan o zadanej nazwie lub jeśli nie ma
         * stanu o tej nazwie, to *zrzuca wyjątek*.
         */
        Ptr <IState> getState (const std::string &stateName) const;

        /**
         * Sprawdza, czy podana nazwa stanu już wystepuje w Maszynie. Sprawdza
         * takze nazwy specjalne, czyli w chwili obecnej  previousPlaceholder.
         */
        bool checkContainsStateName (const std::string &name) const;

        /**
         * Runs all actions from list.
         */
        void runActionList (MachineContext *context, const ActionList &list);

        // Delegate work to extensions.

        /**
         * Wyszukuje przejście dla zadanych wejść i
         * dla aktualnego stanu. Wyszukiwanie jest delegowane najpierw do
         * extensions i zwracane jest pierwsze znalezione. Jeśli za pomocą
         * extensions nie udało się znaleźć transition, to używany jest
         * wewnętrzny algorytm.
         */
        Ptr <Transition> findTransition (Ptr <IState> currentState, MachineContext *context) const;

        /**
         * W chwili obecnej zmiania tylko wystapienie previousPlaceholder
         * na wartość z getPreviousStateName. Pozostale nazwy bez zmian.
         */
        std::string translateName (const std::string &stateName) const;

        void beforeInputActions (MachineContext *context, Ptr <IState> currentState);
        void afterInputActions (MachineContext *context, Ptr <IState> currentState);
        void afterExitActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition);
        void afterTransitionActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition);
        void afterEntryActions (MachineContext *context, Ptr <IState> currentState, Ptr <IState> nextState, Ptr <Transition> transition);

private:

        StateMap stateMap;
        TransitionActionContainer transitionActions;
        std::string currentStateName;
        std::string initialStateName;
        Ptr <Common::ILogger> logger;
        MachineExtensionList extensionList;
        Core::VariantMap machineScope;
        MachineContext defaultContext;
        bool running;

        Ptr <k202::K202> k202;
        Ptr <k202::CacheExtension> cache;
        Ptr <MachineListener> listener;

        _e (Machine)
};


extern const char *SHUT_DOWN_PLACEHOLDER;
extern const char *RESET_PLACEHOLDER;

} //nmspc

#endif /* MACHINE_H_ */
